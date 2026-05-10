%%writefile main.cpp

#include <iostream>
#include <omp.h>

using namespace std;

// Merge Function
void merge(int arr[], int left, int mid, int right){

    int temp[right - left + 1];

    int i = left;
    int j = mid + 1;
    int k = 0;

    // Compare both halves
    while(i <= mid && j <= right){

        if(arr[i] < arr[j]){

            temp[k] = arr[i];
            i++;
        }

        else{

            temp[k] = arr[j];
            j++;
        }

        k++;
    }

    // Remaining left half
    while(i <= mid){

        temp[k] = arr[i];

        i++;
        k++;
    }

    // Remaining right half
    while(j <= right){

        temp[k] = arr[j];

        j++;
        k++;
    }

    // Copy back to original array
    for(i = 0; i < k; i++){

        arr[left + i] = temp[i];
    }
}

// Sequential Merge Sort
void mergeSort(int arr[], int left, int right){

    if(left < right){

        int mid = (left + right) / 2;

        mergeSort(arr, left, mid);

        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Parallel Merge Sort
void parallelMergeSort(int arr[], int left, int right){

    if(left < right){

        int mid = (left + right) / 2;

        #pragma omp parallel sections
        {

            #pragma omp section
            parallelMergeSort(arr, left, mid);

            #pragma omp section
            parallelMergeSort(arr, mid + 1, right);
        }

        merge(arr, left, mid, right);
    }
}

int main(){

    int n;

    cin >> n;

    int arr1[n], arr2[n];

    for(int i = 0; i < n; i++){

        cin >> arr1[i];

        arr2[i] = arr1[i];
    }

    // Sequential Time
    double start = omp_get_wtime();

    mergeSort(arr1, 0, n - 1);

    double seqTime = omp_get_wtime() - start;

    // Parallel Time
    start = omp_get_wtime();

    parallelMergeSort(arr2, 0, n - 1);

    double parTime = omp_get_wtime() - start;

    // Output
    cout << "Sequential Time = "
         << seqTime << endl;

    cout << "Parallel Time = "
         << parTime << endl;

    cout << "Speedup = "
         << seqTime / parTime << endl;

    cout << "Sorted Array : ";

    for(int i = 0; i < n; i++){

        cout << arr2[i] << " ";
    }

    return 0;
}