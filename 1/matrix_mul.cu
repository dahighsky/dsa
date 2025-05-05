#include <bits/stdc++.h>
#include <cuda_runtime.h>
using namespace std;

__global__ void vectorMul(int *A, int *B, int *C, int n){
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	int j = blockIdx.y * blockDim.y + threadIdx.y;
	
	if(i<n and j<n){
		int sum = 0;
		for(int k=0;k<n;k++){
			sum+=A[i*n+k] * B[k*n+j];
		}
		C[i*n+j]=sum;
	}
}

int main(){
	int N;
	N = 512;
	
	int *h_A = new int[N*N];
	int *h_B = new int[N*N];
	int *h_C = new int[N*N];
	srand(time(0));
	for(int i=0;i<N*N;i++){
		h_A[i] = 1;
		h_B[i] = 1;
	}
	int *d_A, *d_B, *d_C;

	size_t size = N*N*sizeof(int);

	cudaMalloc(&d_A,size);
	cudaMalloc(&d_B,size);
	cudaMalloc(&d_C,size);

	cudaMemcpy(d_A,h_A,size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_B,h_B,size,cudaMemcpyHostToDevice);

	dim3 threadsperblock(16,16);
	dim3 blockspergrid((N+15)/16,(N+15)/16);

	vectorMul<<<blockspergrid,threadsperblock>>>(d_A,d_B,d_C,N);
	
	cudaMemcpy(h_C,d_C,size,cudaMemcpyDeviceToHost);
	
	 // Print a small part of result
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << h_C[i * N + j] << " ";
        }
        cout << endl;
    }
}