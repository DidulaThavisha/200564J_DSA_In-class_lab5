
#include <iostream>
#include <vector>
#include <stack>
#include <chrono>
#include <random>
using namespace std;
using namespace std::chrono;

using namespace std;

int partition(vector<int>& arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    for(int j=low; j<=high-1; j++)
    {
        if(arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i+1;
}

void quickSort(vector<int>& arr, int low, int high)
{
    if(low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}

void quickSortNonRecursive(vector<int>& arr, int low, int high)
{
    stack<int> stk;
    stk.push(low);
    stk.push(high);

    while(!stk.empty())
    {
        int end = stk.top();
        stk.pop();
        int start = stk.top();
        stk.pop();

        if(start < end)
        {
            int pi = partition(arr, start, end);

            stk.push(start);
            stk.push(pi-1);

            stk.push(pi+1);
            stk.push(end);
        }
    }
}
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
int main()
{
    for (int k=100; k<=1000;k+=100){
        vector<int> arr = generateRandomArray(k);
        int n = arr.size();
    
        // Recursive Quick Sort
        auto start1 = high_resolution_clock::now();
        quickSort(arr, 0, n-1);
        auto end1 = high_resolution_clock::now();
        auto duration1 = duration_cast<microseconds>(end1 - start1);
    
        // Non-recursive Quick Sort
        auto start2 = high_resolution_clock::now();
        quickSortNonRecursive(arr, 0, n-1);
        auto end2 = high_resolution_clock::now();
        auto duration2 = duration_cast<microseconds>(end2 - start2);
        cout << "Array size"<< k << endl;
        cout << "Recursive Quick Sort: " << duration1.count() << " microseconds" << endl;
        cout << "Non-recursive Quick Sort: " << duration2.count() << " microseconds" << endl;
    
    
    }
    return 0;
}

