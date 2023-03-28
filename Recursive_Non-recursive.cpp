#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

vector<int> generateRandomArray(int n) {
    vector<int> arr(n);

    // Use the Mersenne Twister engine for random number generation
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, n); // Generate integers between 1 and n

    // Fill the array with random numbers
    for (int i = 0; i < n; i++) {
        arr[i] = dist(gen);
    }

    return arr;
}

void recursiveQuickSort(vector<int>& arr, int left, int right) {
    if (left >= right)
        return;

    int i = left, j = right;
    int pivot = arr[(left + right) / 2];

    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    recursiveQuickSort(arr, left, j);
    recursiveQuickSort(arr, i, right);
}

void iterativeQuickSort(vector<int>& arr, int left, int right) {
    vector<pair<int, int>> stk;
    stk.push_back({left, right});

    while (!stk.empty()) {
        int start = stk.back().first, end = stk.back().second;
        stk.pop_back();

        if (start < end) {
            int i = start, j = end;
            int pivot = arr[(start + end) / 2];

            while (i <= j) {
                while (arr[i] < pivot)
                    i++;
                while (arr[j] > pivot)
                    j--;
                if (i <= j) {
                    swap(arr[i], arr[j]);
                    i++;
                    j--;
                }
            }

            stk.push_back({start, j});
            stk.push_back({i, end});
        }
    }
}

int main() {
    for (int i=100; i<1000; i+=100){
        int n=i;
        vector<int> arr = generateRandomArray(n);
        
        //array size
        cout << "Array size: " << n << endl;
        
        // Recursive Quick Sort
        auto start = chrono::high_resolution_clock::now();
        recursiveQuickSort(arr, 0, n - 1);
        auto end = chrono::high_resolution_clock::now();
        auto recursiveDuration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    
        // Iterative Quick Sort
        start = chrono::high_resolution_clock::now();
        iterativeQuickSort(arr, 0, n - 1);
        end = chrono::high_resolution_clock::now();
        auto iterativeDuration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    
        cout << "Iterative Quick Sort time: " << recursiveDuration.count() << " nanoseconds" << endl;
        cout << "Recursive Quick Sort time: " << iterativeDuration.count() << " nanoseconds" << endl;
    }
    
    

    return 0;
}
