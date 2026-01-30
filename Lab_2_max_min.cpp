#include <iostream>
using namespace std;

// Max-Min using Divide and Conquer Algorithm
// Returns a pair where first = max, second = min

pair<int, int> findMaxMin(int arr[], int low, int high) {
    pair<int, int> result, leftResult, rightResult;
    
    // Base case: Only one element
    if (low == high) {
        result.first = arr[low];   // max
        result.second = arr[low];  // min
        return result;
    }
    
    // Base case: Two elements
    if (high == low + 1) {
        if (arr[low] > arr[high]) {
            result.first = arr[low];   // max
            result.second = arr[high]; // min
        } else {
            result.first = arr[high];  // max
            result.second = arr[low];  // min
        }
        return result;
    }
    
    // Divide: Find mid point
    int mid = (low + high) / 2;
    
    // Conquer: Recursively find max-min in left and right halves
    leftResult = findMaxMin(arr, low, mid);
    rightResult = findMaxMin(arr, mid + 1, high);
    
    // Combine: Get overall max and min
    result.first = max(leftResult.first, rightResult.first);    // overall max
    result.second = min(leftResult.second, rightResult.second); // overall min
    
    return result;
}

int main() {
    int n;
    
    cout << "=== Max-Min using Divide and Conquer ===" << endl;
    cout << "Enter the number of elements: ";
    cin >> n;
    
    if (n <= 0) {
        cout << "Invalid input! Number of elements must be positive." << endl;
        return 1;
    }
    
    int arr[n];
    
    cout << "Enter " << n << " elements:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Element " << i + 1 << ": ";
        cin >> arr[i];
    }
    
    // Display the array
    cout << "\nArray: [ ";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << " ]" << endl;
    
    // Timing Max-Min using Divide and Conquer
    using namespace std::chrono;
    auto start_maxmin = high_resolution_clock::now();
    pair<int, int> result = findMaxMin(arr, 0, n - 1);
    auto end_maxmin = high_resolution_clock::now();
    auto duration_maxmin = duration_cast<nanoseconds>(end_maxmin - start_maxmin);

    cout << "\n--- Results ---" << endl;
    cout << "Maximum element: " << result.first << endl;
    cout << "Minimum element: " << result.second << endl;
    cout << "Time taken by Max-Min (Divide and Conquer): " << duration_maxmin.count() << " nanoseconds" << endl;
    cout << "Number of comparisons: 3n/2 - 2 (approximately)" << endl;
    cout << "Space Complexity: O(log n) for recursion stack" << endl;
    
    return 0;
}