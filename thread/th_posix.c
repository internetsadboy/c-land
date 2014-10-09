#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>


#define BUFF_SIZE 80000 // max buffer size
#define N_THREADS 8     // number of threads


// word_count signature
static void *word_count (void *info);

// file content
char buffer[BUFF_SIZE];


// thread meta data
struct thread_info {
  int start;
  int end;
  int count;
};


/**
 * Word count implementation.
 *
 * @param {thread_info} info
 * @api {public}
 */
static void *word_count (void *info)
{
  struct thread_info *th_info;

  th_info = info;
  th_info->count = 0;

  int start, end;

  // partitioned buffer boundaries
  start = th_info->start;
  end = th_info->end;

  while (start < end)
  {
    // non-general case: traverse over non-alphanumeric characters
    while (!isalpha(buffer[start])) start++;

    // increment the count
    if (start < end) th_info->count++;

    // general case: traverse alphanumeric characters
    while (isalpha(buffer[start])) start++;
  }

  // terminate the calling thread
  pthread_exit(NULL);
}


int main (int argc, char *argv[])
{
  // record the current time
  struct timeval stop, start;
  gettimeofday(&start, NULL);

  // thread buffer
  pthread_t threads[(int) N_THREADS];

  // thread meta data buffer
  struct thread_info info[N_THREADS];

  // thread attributes
  pthread_attr_t attr;

  int sum, err;

  sum = 0;

  // initialize thread w/ default values
  err = pthread_attr_init(&attr);

  // if err equals anything other than zero => error
  if (err != 0)
  {
    printf("pthread_attr_init error number %d", err);
    return 1;
  }

  // read file, cli arg
  FILE *file = fopen(argv[1], "r");

  // compute size of file
  size_t file_size = fread(buffer, 1, BUFF_SIZE, file);

  // initialize first boundary (start)
  info[0].start = 0;

  // initialize first boundary (end)
  info[N_THREADS-1].end = file_size;

  int i, j;

  // calculate boundaries for each thread
  for (i = 0; i < (int) N_THREADS - 1; i++)
  {
    // general case, start borders previous end boundary
    if (i != 0) info[i].start = info[i - 1].end;

    // update the boundary
    j = (file_size / N_THREADS) * (i + 1);
    info[i].end = j;

    // add alphanumeric characters only
    while (isalpha(buffer[j]))
    {
      info[i].end++;
      j++;
    }
  }

  if (N_THREADS > 1) info[N_THREADS-1].start = info[N_THREADS - 2].end;

  for (i = 0; i < (int) N_THREADS; i++)
  {
    // create additional thread, do work (count words :P)
    err = pthread_create(&threads[i], &attr, word_count, &info[i]);

    // thread creation error handler
    if (err != 0) printf("pthread_create error number %d", err);
  }

  // destroy thread atttributes
  err = pthread_attr_destroy(&attr);

  // thread attr destroy error handler
  if (err != 0) printf("pthread_attr_destroy error %d", err);

  // join threads, aggregate thread word counts
  for (i = 0; i < (int) N_THREADS; i++)
  {
    err = pthread_join(threads[i], NULL);

    if (err != 0) printf("pthread_join error %d", err);

    // add current thread's count to total
    sum += info[i].count;
  }

  printf("%d threads\n", (int) N_THREADS);

  // end time
  gettimeofday(&stop, NULL);
  printf("%f ms\n", (double) (stop.tv_usec - start.tv_usec) / 1000); // convert from µs to ms

  // log total word count
  printf("%d words\n", sum);

  return 0;
}
