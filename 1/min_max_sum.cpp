#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <omp.h>
using namespace std;
using namespace std::chrono;

int findMinSeq(const vector<int>& arr) {
    int minVal = arr[0];
    for (int i = 1; i < arr.size(); i++)
        if (arr[i] < minVal) minVal = arr[i];
    return minVal;
}

int findMinPar(const vector<int>& arr) {
    int minVal = arr[0];
    #pragma omp parallel for reduction(min:minVal)
    for (int i = 0; i < arr.size(); i++)
        if (arr[i] < minVal) minVal = arr[i];
    return minVal;
}

int findMaxSeq(const vector<int>& arr) {
    int maxVal = arr[0];
    for (int i = 1; i < arr.size(); i++)
        if (arr[i] > maxVal) maxVal = arr[i];
    return maxVal;
}

int findMaxPar(const vector<int>& arr) {
    int maxVal = arr[0];
    #pragma omp parallel for reduction(max:maxVal)
    for (int i = 0; i < arr.size(); i++)
        if (arr[i] > maxVal) maxVal = arr[i];
    return maxVal;
}

long long findSumSeq(const vector<int>& arr) {
    long long sum = 0;
    for (int val : arr)
        sum += val;
    return sum;
}

long long findSumPar(const vector<int>& arr) {
    long long sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < arr.size(); i++)
        sum += arr[i];
    return sum;
}

float findAvg(long long sum, int n) {
    return static_cast<float>(sum) / n;
}

int main() {
    const int n = 100000000;
    vector<int> arr(n);
    srand(time(0));
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 10000;

    cout << "==== SEQUENTIAL ====\n";

    auto start = high_resolution_clock::now();
    int minSeq = findMinSeq(arr);
    auto end = high_resolution_clock::now();
    cout << "Min: " << minSeq << ", Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    int maxSeq = findMaxSeq(arr);
    end = high_resolution_clock::now();
    cout << "Max: " << maxSeq << ", Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    long long sumSeq = findSumSeq(arr);
    end = high_resolution_clock::now();
    cout << "Sum: " << sumSeq << ", Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    float avgSeq = findAvg(sumSeq, n);
    end = high_resolution_clock::now();
    cout << "Avg: " << avgSeq << ", Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";


    cout << "\n==== PARALLEL (OpenMP) ====\n";

    start = high_resolution_clock::now();
    int minPar = findMinPar(arr);
    end = high_resolution_clock::now();
    cout << "Min: " << minPar << ", Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    int maxPar = findMaxPar(arr);
    end = high_resolution_clock::now();
    cout << "Max: " << maxPar << ", Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    long long sumPar = findSumPar(arr);
    end = high_resolution_clock::now();
    cout << "Sum: " << sumPar << ", Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    float avgPar = findAvg(sumPar, n);
    end = high_resolution_clock::now();
    cout << "Avg: " << avgPar << ", Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    return 0;
}
