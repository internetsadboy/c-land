#include <stdio.h>


int binary_search (int arr[], int key, int min, int max)
{
  if (max < min) {
    return -1;
  } else {

    int mid = (min + max) / 2;

    if (arr[mid] > key) {
      return binary_search(arr, key, min, mid - 1); // search lower half
    } else if (arr[mid] < key) {
      return binary_search(arr, key, mid + 1, max); // search upper half
    } else {
      return mid; // key found
    }

  }
}


int main (int argc, char *argv[])
{
  int arr[] = { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
  int key = 17;

  printf("%d \n", binary_search(arr, key, 0, 9));

  return 0;
}
