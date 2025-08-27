#include "array_functions.h"

void swap(int *arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void sort_array(int *arr, int size) {
    for (int loop = 0; loop < size; loop++) {
        for (int i = 0; i < size - 1; i++) {
            int currentNum = arr[i];
            int nextNum = arr[i + 1];
            if (currentNum < nextNum) {
                continue;
            }

            swap(arr, i, i + 1);
        }
    }
}

double calculate_median(int *arr, int size) {
    if (size % 2 == 0) {
        int leftNum = arr[size / 2 - 1];
        int rightNum = arr[size / 2];
        return (double) (leftNum + rightNum) / 2;
    }

    return arr[size / 2];
}
