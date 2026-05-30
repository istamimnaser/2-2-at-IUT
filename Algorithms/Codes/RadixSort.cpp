#include<iostream>
#include<vector>
using namespace std;

void radixsort(int arr[],int n){
    int m = getmax(arr, n);
    for(int exp = 1; m/exp > 0; exp *= 10){
        countingsort(arr, n, exp);
    }
}

void countingsort(int arr[], int n, int exp){
    int output[n];
    int count[10] = {0};

    for(int i = 0; i < n; i++){
        count[(arr[i]/exp) % 10]++;
    }

    for(int i = 1; i < 10; i++){
        count[i] += count[i - 1];
    }

    for(int i = n - 1; i >= 0; i--){
        output[count[(arr[i]/exp) % 10] - 1] = arr[i];
        count[(arr[i]/exp) % 10]--;
    }

    for(int i = 0; i < n; i++){
        arr[i] = output[i];
    }
}