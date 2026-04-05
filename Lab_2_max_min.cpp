#include <iostream>
#include <vector>
#include <utility>   // For std::pair
#include <algorithm> // For std::max, std::min
#include <chrono>    // For high_resolution_clock

using namespace std;
using namespace std::chrono;

/**
 * Recursive function to find Min and Max using Divide and Conquer.
 * arr - The input array pointer.
 * low - The starting index of the segment.
 * high - The ending index of the segment.
 * pair<int, int> -> first = maximum, second = minimum
 */
pair<int, int> findMaxMin(int arr[], int low, int high) {
    pair<int, int> result, leftResult, rightResult;
    
    // Case 1: Only one element in the array/segment
    if (low == high) {
        result.first = arr[low];   // Max
        result.second = arr[low];  // Min
        return result;
    }
    
    // Case 2: Two elements in the array/segment
    if (high == low + 1) {
        if (arr[low] > arr[high]) {
            result.first = arr[low];   // Max
            result.second = arr[high]; // Min
        } else {
            result.first = arr[high];  // Max
            result.second = arr[low];  // Min
        }
        return result;
    }
    
    // Case 3: More than two elements -> Divide and Conquer
    int mid = low + (high - low) / 2; // Avoid overflow
    
    // Recursively solve for left and right halves
    leftResult = findMaxMin(arr, low, mid);
    rightResult = findMaxMin(arr, mid + 1, high);
    
    // Combine the results
    result.first = max(leftResult.first, rightResult.first);    // Global Max
    result.second = min(leftResult.second, rightResult.second); // Global Min
    
    return result;
}

int main() {
    int n;
    
    cout << "=== Max-Min using Divide and Conquer ===" << endl;
    cout << "Enter the number of elements: ";
    if (!(cin >> n) || n <= 0) {
        cout << "Invalid input! Size must be positive." << endl;
        return 1;
    }
    
    // Dynamic allocation ensures stack safety for large 'n'
    int* arr = new int[n];
    
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    // Display the input array
    cout << "\nInput Array: [ ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << (i < n - 1 ? ", " : "");
    }
    cout << " ]" << endl;
    
    // Execution and Timing
    auto start_time = high_resolution_clock::now();
    pair<int, int> result = findMaxMin(arr, 0, n - 1);
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end_time - start_time);

    // Results
    cout << "\n--- Final Results ---" << endl;
    cout << "Maximum element: " << result.first << endl;
    cout << "Minimum element: " << result.second << endl;
    cout << "Time taken: " << duration.count() << " nanoseconds" << endl;
    cout << "Theoretical Comparisons: " << (3 * n / 2) - 2 << endl;
    
    delete[] arr; // Clean up memory
    return 0;
}