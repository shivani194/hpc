#include <iostream> 
#include <vector> 
#include <omp.h> 
using namespace std; 

// 🔴 Parallel Odd-Even Bubble Sort
void bubble_sort_odd_even(vector<int>& arr) { 
    bool isSorted = false; 
    while (!isSorted) { 
        isSorted = true; 

        #pragma omp parallel for 
        for (int i = 0; i < arr.size() - 1; i += 2) { 
            if (arr[i] > arr[i + 1]) { 
                swap(arr[i], arr[i + 1]); 
                isSorted = false; 
            } 
        } 

        #pragma omp parallel for 
        for (int i = 1; i < arr.size() - 1; i += 2) { 
            if (arr[i] > arr[i + 1]) { 
                swap(arr[i], arr[i + 1]); 
                isSorted = false; 
            } 
        } 
    } 
} 

// 🔵 Sequential Bubble Sort
void bubble_sort_sequential(vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        for (int j = 0; j < arr.size() - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() { 
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n), arr_copy;

    cout << "Enter elements: ";
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    arr_copy = arr; // copy for sequential sorting

    double start, end;

    // 🔴 Parallel Sort
    start = omp_get_wtime();
    bubble_sort_odd_even(arr);
    end = omp_get_wtime();

    cout << "\nParallel Sorted Array: ";
    for(int x : arr) cout << x << " ";
    cout << "\nParallel Execution Time: " << end - start << endl;

    // 🔵 Sequential Sort
    start = omp_get_wtime();
    bubble_sort_sequential(arr_copy);
    end = omp_get_wtime();

    cout << "\nSequential Sorted Array: ";
    for(int x : arr_copy) cout << x << " ";
    cout << "\nSequential Execution Time: " << end - start << endl;
}