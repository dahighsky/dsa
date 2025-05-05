#include <iostream>
#include <cuda_runtime.h>
using namespace std;

__global__ void addVectors(int *A, int *B, int *C, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n)
        C[i] = A[i] + B[i];
}

int main() {
    int n = 1 << 20;  // 2^20 = 1048576 elements

    int *h_A = new int[n];
    int *h_B = new int[n];
    int *h_C = new int[n];

    // Fill A and B with values
    for (int i = 0; i < n; i++) {
        h_A[i] = i;
        h_B[i] = i;
    }

    int *d_A, *d_B, *d_C;
    size_t size = n * sizeof(int);

    // Allocate memory on GPU
    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);
    cudaMalloc(&d_C, size);

    // Copy data from CPU to GPU
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    // Launch the kernel
    int threadsPerBlock = 256;
    int blocksPerGrid = (n + threadsPerBlock - 1) / threadsPerBlock;

    addVectors<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, n);

    // Copy result from GPU to CPU
    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    // Print first 5 results
    for (int i = 0; i < 5; i++)
        cout << h_C[i] << " ";
    cout << endl;

    // Free memory
    delete[] h_A;
    delete[] h_B;
    delete[] h_C;
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}
