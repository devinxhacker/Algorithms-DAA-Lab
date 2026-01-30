#include<iostream>
using namespace std;

// Quick Sort with Median of Medians as Pivot (Simple Program)

// Swap two elements
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Insertion sort for small groups (used to find median of 5)
void insertionSort(int arr[], int left, int right){
    for(int i = left + 1; i <= right; i++){
        int key = arr[i];
        int j = i - 1;
        while(j >= left && arr[j] > key){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Find index of element in array
int findIndex(int arr[], int left, int right, int value) {
    for(int i = left; i <= right; i++) {
        if(arr[i] == value) {
            return i;
        }
    }
    return left;
}

// Partition array around pivot value
int partition(int arr[], int left, int right, int pivotValue) {
    // Move pivot to end
    int pivotIndex = findIndex(arr, left, right, pivotValue);
    swap(arr[pivotIndex], arr[right]);
    
    // Partition around pivot
    int i = left - 1;
    for(int j = left; j < right; j++) {
        if(arr[j] <= pivotValue) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]);
    return i + 1;
}


// Helper: Partition arr[left..right] into <pivot, ==pivot, >pivot, returns start and end of ==pivot
void threeWayPartition(int arr[], int left, int right, int pivot, int &start, int &end) {
    int i = left, lt = left, gt = right;
    while(i <= gt){
        if (arr[i] < pivot) {
            swap(arr[i], arr[lt]);
            i++; lt++;
        }
        else if (arr[i] > pivot) {
            swap(arr[i], arr[gt]);
            gt--;
        }
        else {
            i++;
        }
    }
    start = lt;
    end = gt;
}

// Median of Medians selection: finds the value at index r (0-based) in arr[left..right]
int medianOfMediansSelect(int arr[], int left, int right, int r) {
    int n = right - left + 1;
    if (n <= 5) {
        insertionSort(arr, left, right);
        return arr[left + r];
    }
    // Step 1: Divide into groups of 5 and find medians
    int numGroups = (n + 4) / 5;
    int medians[100];
    for (int i = 0; i < numGroups; i++) {
        int groupLeft = left + i * 5;
        int groupRight = min(groupLeft + 4, right);
        insertionSort(arr, groupLeft, groupRight);
        int groupSize = groupRight - groupLeft + 1;
        medians[i] = arr[groupLeft + groupSize / 2];
    }
    // Step 2: Find median of medians recursively
    int mom = medianOfMediansSelect(medians, 0, numGroups - 1, numGroups / 2);
    // Step 3: Partition arr around mom
    int start, end;
    threeWayPartition(arr, left, right, mom, start, end);
    int k = start - left; // number of elements < mom
    int m = end - left + 1; // number of elements <= mom
    if (r < k){
        // Desired index is in left part
        return medianOfMediansSelect(arr, left, start - 1, r);
    }
    else if (r < m){
        // Desired index is in ==mom part
        return mom;
    }
    else{
        // Desired index is in right part
        return medianOfMediansSelect(arr, end + 1, right, r - m);
    }
}

// Main function to get median of medians
int medianOfMedians(int arr[], int left, int right) {
    int n = right - left + 1;
    int r = n / 2; // 0-based median index
    return medianOfMediansSelect(arr, left, right, r);
}

// Quick Sort using Median of Medians as pivot
void quickSort(int arr[], int left, int right) {
    if(left < right) {
        // Step 4: Find median of medians and use as pivot
        int pivot = medianOfMedians(arr, left, right);
        
        // Partition the array around pivot
        int pivotIndex = partition(arr, left, right, pivot);
        
        // Step 5: Recursively sort left and right partitions
        quickSort(arr, left, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, right);
    }
}

// Function to print array
void printArray(int arr[], int n) {
    for(int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int n;
    int arr[100];
    
    // Input array size
    cout << "Enter number of elements: ";
    cin >> n;
    
    // Input array elements
    cout << "Enter " << n << " elements: ";
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    cout << "\nOriginal array: ";
    printArray(arr, n);

    // Timing Quick Sort (Median of Medians)
    using namespace std::chrono;
    auto start_quick = high_resolution_clock::now();
    quickSort(arr, 0, n - 1);
    auto end_quick = high_resolution_clock::now();
    auto duration_quick = duration_cast<nanoseconds>(end_quick - start_quick);

    cout << "Sorted array: ";
    printArray(arr, n);
    cout << "Time taken by Quick Sort (Median of Medians): " << duration_quick.count() << " nanoseconds" << endl;

    return 0;
}


// 10
// 24 8 42 75 29 77 38 57 13 91

// O(n log n) time complexity on average