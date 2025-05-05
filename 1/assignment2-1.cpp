// #include <iostream>
// #include <vector>
// #include <cstdlib>
// #include <ctime>
// #include <chrono>
// #include <omp.h>
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

// Sequential Bubble Sort
void bubbleSortSequential(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
        }
    }
}

// Parallel Bubble Sort with OpenMP (Odd-Even Sort)
void bubbleSortParallel(vector<int>& arr) {
    int n = arr.size();
    bool isSorted = false;

    while (!isSorted) {
        isSorted = true;

        #pragma omp parallel for
        for (int i = 1; i < n - 1; i += 2) {
            if (arr[i] > arr[i+1]) {
                swap(arr[i], arr[i+1]);
                isSorted = false;
            }
        }

        #pragma omp parallel for
        for (int i = 0; i < n - 1; i += 2) {
            if (arr[i] > arr[i+1]) {
                swap(arr[i], arr[i+1]);
                isSorted = false;
            }
        }
    }
}

// Sequential Merge Sort
void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> left(arr.begin() + l, arr.begin() + m + 1);
    vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    while (i < left.size()) arr[k++] = left[i++];
    while (j < right.size()) arr[k++] = right[j++];
}

void mergeSortSequential(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortSequential(arr, l, m);
        mergeSortSequential(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

void mergeSortParallel(vector<int>& arr, int l, int r) {
  if (l < r) {
      int m = l + (r - l) / 2;

      #pragma omp parallel sections
      {
          #pragma omp section
          mergeSortParallel(arr, l, m);

          #pragma omp section
          mergeSortParallel(arr, m + 1, r);
      }

      merge(arr, l, m, r);
  }
}

int main() {
    int n;
    cout << "Enter array size: ";
    cin >> n;

    vector<int> original(n);
    srand(time(0));
    for (int i = 0; i < n; i++)
        original[i] = rand() % 100000;

    // BUBBLE SORT
    vector<int> bubbleSeq = original;
    auto start = high_resolution_clock::now();
    bubbleSortSequential(bubbleSeq);
    auto end = high_resolution_clock::now();
    cout << "\nSequential Bubble Sort Time: "
         << duration_cast<milliseconds>(end - start).count() << " ms";

    vector<int> bubblePar = original;
    start = high_resolution_clock::now();
    bubbleSortParallel(bubblePar);
    end = high_resolution_clock::now();
    cout << "\nParallel Bubble Sort Time: "
         << duration_cast<milliseconds>(end - start).count() << " ms";

    // MERGE SORT
    vector<int> mergeSeq = original;
    start = high_resolution_clock::now();
    mergeSortSequential(mergeSeq, 0, n-1);
    end = high_resolution_clock::now();
    cout << "\nSequential Merge Sort Time: "
         << duration_cast<milliseconds>(end - start).count() << " ms";

    vector<int> mergePar = original;
    start = high_resolution_clock::now();
    #pragma omp parallel
    {
        #pragma omp single
        mergeSortParallel(mergePar, 0, n-1);
    }
    end = high_resolution_clock::now();
    cout << "\nParallel Merge Sort Time: "
         << duration_cast<milliseconds>(end - start).count() << " ms\n";

    return 0;
}
