#include <iostream>
#include <omp.h>
using namespace std;

int main() {

    int arr[10] = {10, 20, 5, 40, 15, 25, 30, 50, 35, 45};

    int sum = 0;
    int min = arr[0];
    int max = arr[0];

    int n = 10;

    #pragma omp parallel for reduction(+:sum) reduction(min:min) reduction(max:max)

    for(int i = 0; i < n; i++) {

        sum += arr[i];

        if(arr[i] < min)
            min = arr[i];

        if(arr[i] > max)
            max = arr[i];
    }

    float avg = (float)sum / n;

    cout << "Sum = " << sum << endl;
    cout << "Minimum = " << min << endl;
    cout << "Maximum = " << max << endl;
    cout << "Average = " << avg << endl;

    return 0; 
}