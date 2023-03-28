#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

void print_median(double median) {
    cout << fixed << setprecision(1) << median << endl;
}

int main() {
    int n;
    cout<<"Enter the array size : ";
    cin >> n;
    cout<<"Enter the array  : ";
    priority_queue<int> max_heap; // stores the lower half of the list
    priority_queue<int, vector<int>, greater<int>> min_heap; // stores the upper half of the list

    double median = 0.0;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        if (max_heap.empty() || x <= max_heap.top()) {
            max_heap.push(x);
        } else {
            min_heap.push(x);
        }

        // Rebalance the heaps
        if (max_heap.size() > min_heap.size() + 1) {
            min_heap.push(max_heap.top());
            max_heap.pop();
        } else if (min_heap.size() > max_heap.size() + 1) {
            max_heap.push(min_heap.top());
            min_heap.pop();
        }

        // Update the median
        if (max_heap.size() == min_heap.size()) {
            median = (max_heap.top() + min_heap.top()) / 2.0;
        } else if (max_heap.size() > min_heap.size()) {
            median = max_heap.top();
        } else {
            median = min_heap.top();
        }

        print_median(median);
    }

    return 0;
}
