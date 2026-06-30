#include "sort_algorithm.h"

#include "../../trie_node.h"

// ==========================================
// 1. SORTING ALGORITHM
// ==========================================

// TODO 1: Students implement the sorting algorithm (QuickSort / MergeSort)
// Requirement: Sort the Match array prioritizing ascending 'start'.
// If 'start' are equal, prioritize descending 'end'.
// Strictly DO NOT use the <algorithm> library (std::sort).
void swapMatch(Match &a, Match &b) {
  Match temp = a;
  a = b;
  b = temp;
}
int partitionLomuto(Match *arr, int left, int right) {
  if (left >= right) {
    return left;
  }

  int mid = left + (right - left) / 2;
  swapMatch(arr[mid], arr[right]);
  Match pivot = arr[right];

  int i = left - 1;
  for (int j = left; j <= right - 1; j++) {
    if ((arr[j].start < pivot.start) ||
        (arr[j].start == pivot.start && arr[j].end > pivot.end)) {
      i++;
      swapMatch(arr[i], arr[j]);
    }
  }

  swapMatch(arr[i + 1], arr[right]);
  return i + 1;
}
void quickSort(Match *arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int p = partitionLomuto(arr, left, right);
  quickSort(arr, left, p - 1);
  quickSort(arr, p + 1, right);
}
void sortMatches(Match *arr, int count) { quickSort(arr, 0, count - 1); }
