#include <iostream>
using namespace std;
#include <limits.h>
#include "include/merge_sort.h"


//MERGE SORTING ALGORITHM
//Taken from "https://www.programiz.com/dsa/merge-sort"


// Merge two subarrays L and M into arr
void merge(int indexes[], int arr[], int p, int q, int r) {
  
  // Create L ← A[p..q] and M ← A[q+1..r]
  int n1 = q - p + 1;
  int n2 = r - q;

  int L[n1], M[n2], X[n1], Y[n2];

  for (int i = 0; i < n1; i++)
  {
      L[i] = arr[p + i]; //lower 
      X[i] = indexes[p + i]; //lower
  }
    
  for (int j = 0; j < n2; j++)
  {
    M[j] = arr[q + 1 + j]; //upper
    Y[j] = indexes[q + 1 + j]; //upper
  }

  // Maintain current index of sub-arrays and main array
  int i, j, k;
  i = 0;
  j = 0;
  k = p;

  // Until we reach either end of either L or M, pick larger among
  // elements L and M and place them in the correct position at A[p..r]
  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      arr[k] = L[i]; //lower 
      indexes[k] = X[i];
      i++;
    } else {
      arr[k] = M[j];//upper
      indexes[k] = Y[j];
      j++;
    }
    k++;
  }

  // When we run out of elements in either L or M,
  // pick up the remaining elements and put in A[p..r]
  while (i < n1) {
    arr[k] = L[i]; //lower
    indexes[k] = X[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = M[j]; //upper
    indexes[k] = Y[j];
    j++;
    k++;
  }
}

// Divide the array into two subarrays, sort them and merge them
void mergeSort(int indexes[], int arr[], int l, int r) {
  if (l < r) {
    // m is the point where the array is divided into two subarrays
    int m = l + (r - l) / 2;

    mergeSort(indexes, arr, l, m);
    mergeSort(indexes, arr, m + 1, r);

    // Merge the sorted subarrays
    merge(indexes, arr, l, m, r);
  }
}