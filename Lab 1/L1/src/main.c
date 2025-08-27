#include "array_functions.h"
#include <stdio.h>

void printArr(int *arr, int size);

int main(void) {
  int arr[] = {3, 2, 4, 6, 1, 5};
  printArr(arr, 6);
  sort_array(arr, 6);
  printArr(arr, 6);

  printf("Median is %f\n", calculate_median(arr, 6));
  /* printf("%d\n", 6 / 2 - 1); */
  /* printf("%d\n", 6 / 2); */

  return 1;
}

void printArr(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}
