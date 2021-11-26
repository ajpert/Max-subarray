/***************************************************************
 ** Program: homework_1.cpp
 ** Author: Andy James
 ** Date: 10/9/2021
 ** Description: runs tasks for assignemnt 1
 ** Input: num_array_xxx.txt
 ** Output: none
 ***************************************************************/
#include <iostream>
#include <sstream> //needed to read text
#include <algorithm> //needed for max function
#include <limits> //needed for min int
#include <fstream> // needed to read text
#include <vector> // needed to store text
#include <time.h> // needed to time algo
#include <string>
#include <chrono> // needed to time algo

int INT_MIN = -2147483648;
using namespace std;

int max_subarray_enumeration(int* arr, int size);
int max_subarray_iteration(int* arr, int size);
int max_subarray_simplification_delegation(int* arr, int start, int end);
int max_subarray_recursion_inversion(int* arr, int size);

int main(int argc, char* argv[]) {
    auto begin = std::chrono::high_resolution_clock::now();
    auto stop =  std::chrono::high_resolution_clock::now();
    int* arr;
    int number;
    fstream f;
    vector<int>numbers;
    int answer;
    f.open(argv[1]);
    while(!f.eof()) {
        f >> number;
        numbers.push_back(number);
    }
    arr = new int[numbers.size()];
    for(int i = 0; i < numbers.size(); i++) {
        arr[i] = numbers[i];
    }


    
    begin = std::chrono::high_resolution_clock::now();
    answer = max_subarray_enumeration(arr,numbers.size());
    stop = std::chrono::high_resolution_clock::now();
    cout << "max_subarray_enumeration: " << (float)std::chrono::duration_cast<std::chrono::nanoseconds>(stop-begin).count()/1000000000 << "seconds | answer: " << answer << endl;
    begin = std::chrono::high_resolution_clock::now();
    answer = max_subarray_iteration(arr,numbers.size());
    stop = std::chrono::high_resolution_clock::now();
    cout << "max_subarray_iteration: " << (float)std::chrono::duration_cast<std::chrono::nanoseconds>(stop-begin).count()/1000000000<< " seconds | answer: " << answer << endl;
    begin = std::chrono::high_resolution_clock::now();
    answer = max_subarray_simplification_delegation(arr,0,numbers.size());
    stop = std::chrono::high_resolution_clock::now();
    cout << "max_subarray_simplification_delegation: " << (float)std::chrono::duration_cast<std::chrono::nanoseconds>(stop-begin).count()/1000000000<< " seconds | answer: " << answer << endl;
    begin = std::chrono::high_resolution_clock::now();
    answer = max_subarray_recursion_inversion(arr,numbers.size());
    stop = std::chrono::high_resolution_clock::now();
    cout << "max_subarray_recursion_inversion: " << (float)std::chrono::duration_cast<std::chrono::nanoseconds>(stop-begin).count()/1000000000 << " seconds | answer: " << answer << endl;



}

int max_subarray_enumeration(int* arr, int size) {   
    int check = 0;
    int max = INT_MIN;

    for(int i = 0; i < size; i++) {
        for(int j = size - 1; j >= i; j--) {
            for(int k = i; k <= j; k++) {
                check += arr[k];
            }
            if(check > max) {
                max = check;
            }
            check = 0;
        }
    }
    return max;
}

int max_subarray_iteration(int* arr, int size) {
    int check = 0;
    int max = INT_MIN;
    for(int i = 0; i < size; i++)  {
        for(int j = i; j < size; j++) {
            check += arr[j];
            if(check > max) {
                max = check;
            }
        }
        
        check = 0;
    }
    return max;
}

int max_subarray_simplification_delegation(int* arr, int start, int end) {
    if(start == end) {
        return arr[start];
    }
    int middle = (start+end)/2;
    int l_sum = INT_MIN;
    int r_sum = INT_MIN;
    int check = 0;
    for(int i = middle; i>= start; i--) {
        check += arr[i];
        if(check > l_sum) {
            l_sum = check;
        }
    }
    check = 0;
    for(int i = middle + 1; i <= end; i++) {
        check += arr[i];
        if(check > r_sum) {
            r_sum = check;
        }
    }
    int suf_sum = max(max_subarray_simplification_delegation(arr,start,middle),
    max_subarray_simplification_delegation(arr,middle+1,end));
    return max(suf_sum,l_sum+r_sum);
}


int max_subarray_recursion_inversion(int* arr, int size) {
    int max_sub = INT_MIN;
    int check = 0;
    for(int i = 0; i < size; i++) {
        check = max(0,check + arr[i]);
        if(check > max_sub) {
            max_sub = check;
        }
    }
    return max_sub;
}