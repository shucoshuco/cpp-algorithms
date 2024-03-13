#include "utils.h"
#include <algorithm>

int * init_vector(int size, int value) {
  int *vector = new int[size];
  std::fill_n(vector, size, value);
  return vector;
}

void change(int *list, int i, int j) {
  int tmp = list[j];
  list[j] = list[i];
  list[i] = tmp;
}

void c_quicksort(int *list, int start, int end) {
  if (end - start < 1) {
    return;
  }
  int pivot = list[start];
  int i = start + 1;
  int j = end;
  while (i < j) {
    if (list[i] < pivot) {
      i++;
    } else {
      change(list, i, j);
      j--;
    }
  }
  int pivot_pos = list[i] < pivot ? i : i - 1;
  change(list, pivot_pos, start);

  c_quicksort(list, start, pivot_pos - 1);
  c_quicksort(list, pivot_pos + 1, end);
}

void c_quicksort(int *list, int size) {
  c_quicksort(list, 0, size - 1);
}

std::string print_array(int *list, int size) {
  std::string result;
  for (int i = 0; i < size; i++) {
    result += std::to_string(list[i]);
    result += ", ";
  }
  return result;
}