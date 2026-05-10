%%writefile vector_mul.cu

#include <iostream>
using namespace std;

__global__ void multiply(int *a, int *b, int *c, int n) {

    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if(i < n)
        c[i] = a[i] * b[i];
}

int main() {

    const int n = 6;

    int a[n] = {1,2,3,4,5,6};
    int b[n] = {6,5,4,3,2,1};
    int c[n];

    int *da, *db, *dc;

    int size = n * sizeof(int);

    cudaMalloc(&da, size);
    cudaMalloc(&db, size);
    cudaMalloc(&dc, size);

    cudaMemcpy(da, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(db, b, size, cudaMemcpyHostToDevice);

    multiply<<<1,n>>>(da, db, dc, n);

    

    cudaMemcpy(c, dc, size, cudaMemcpyDeviceToHost);

    for(int i=0; i<n; i++)
        cout << c[i] << " ";

    cout << endl;

    cudaFree(da);
    cudaFree(db);
    cudaFree(dc);

    return 0;
}               