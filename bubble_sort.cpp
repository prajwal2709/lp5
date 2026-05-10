%%writefile main.cpp

#include<iostream>
#include<omp.h>
using namespace std;

void bubbleSort(int arr[], int n){

    for(int i=0;i<n;i++){

        for(int j=0;j<n-i-1;j++){

            if(arr[j] > arr[j+1]){

                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void parallelBubbleSort(int arr[], int n){

    for(int i=0;i<n;i++){

        #pragma omp parallel for
        for(int j=0;j<n-1;j+=2){

            if(arr[j] > arr[j+1]){

                swap(arr[j], arr[j+1]);
            }
        }

        #pragma omp parallel for
        for(int j=1;j<n-1;j+=2){

            if(arr[j] > arr[j+1]){

                swap(arr[j], arr[j+1]);
            }
        }
    }
}

int main(){

    int n;
    cin >> n;

    int arr1[n], arr2[n];

    for(int i=0;i<n;i++){

        cin >> arr1[i];

        arr2[i] = arr1[i];
    }

    double start = omp_get_wtime();

    bubbleSort(arr1,n);

    double seqTime = omp_get_wtime() - start;

    start = omp_get_wtime();

    parallelBubbleSort(arr2,n);

    double parTime = omp_get_wtime() - start;

    cout << "Sequential Time = "
         << seqTime << endl;

    cout << "Parallel Time = "
         << parTime << endl;

    cout << "Speedup = "
         << seqTime/parTime << endl;

    cout << "Sorted Array : ";

    for(int i=0;i<n;i++){

        cout << arr2[i] << " ";
    }
}