#include <stdint.h>

void FillArray(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    arr[i] = i + 1;
  }
}

int64_t SumArray(int *arr, int size) {
  int64_t sum = 0;

  for (int i = 0; i < size; i++) {
    sum += arr[i];
  }

  return sum;
}
