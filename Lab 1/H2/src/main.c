#include <stdio.h>
#include <stdlib.h>

#include "../include/functions.h"

int main(void) {
  int size;
  scanf("%d", &size);

  int num_is_valid = size >= 10 && size <= 50;
  if (!num_is_valid) {
    printf("Error, %d is not valid!", size);
    return 1;
  }

  int *arr = (int *)malloc(size * sizeof(int));
  if (arr == NULL) {
    printf("Error, could not allocate memory!");
    return 1;
  }

  FillArray(arr, size);
  int64_t sum = SumArray(arr, size);
  printf("%ld", sum);

  free(arr);

  return 0;
}
