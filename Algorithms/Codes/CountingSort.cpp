#include<iostream>
#include<vector>
using namespace std;

vector<int> countingSort(vector<int>&arr){
    int n = arr.size();

  int maxval = 0;
    for(int i = 0; i < n; i++){
        maxval = max(maxval, arr[i]);
    }


    vector<int> count(maxval + 1, 0);

    for(int i = 0; i < n; i++){
        count[arr[i]]++;
    }

    for(int i = 1; i <= maxval; i++){
        count[i] += count[i - 1];
    }


    vector<int> output(n);
    for(int i = n - 1; i >= 0; i--){
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    return output;
}

// time complexity: O(n + k) where n is the number of elements in the input array and k is the range of the input values
// space complexity: O(n + k) where n is the number of elements in the input array and k is the range of the input values