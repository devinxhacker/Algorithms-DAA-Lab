#include<iostream>
using namespace std;

// Function to merge two sorted halves
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;  // Size of left half
    int n2 = right - mid;      // Size of right half
    
    // Create temporary arrays
    int leftArr[100], rightArr[100];
    
    // Copy data to temporary arrays
    for(int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for(int j = 0; j < n2; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }
    
    // Merge the two arrays back into arr[]
    int i = 0;      // Index for left array
    int j = 0;      // Index for right array
    int k = left;   // Index for merged array
    
    while(i < n1 && j < n2) {
        if(leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else{
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    
    // Copy remaining elements of left array
    while(i < n1){
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    
    // Copy remaining elements of right array
    while(j < n2){
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Recursive merge sort function
void mergeSort(int arr[], int left, int right){
    if(left < right) {
        // Find the middle point
        int mid = left + (right - left) / 2;
        
        // Sort first half
        mergeSort(arr, left, mid);
        
        // Sort second half
        mergeSort(arr, mid + 1, right);
        
        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Function to print array
void printArray(int arr[], int n){
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main(){
    int n;
    int arr[100];
    
    // Input array size
    cout << "Enter number of elements: ";
    cin >> n;
    
    // Input array elements
    cout << "Enter " << n << " elements: ";
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    
    cout << "\nOriginal array: ";
    printArray(arr, n);

    // Timing Merge Sort
    using namespace std::chrono;
    auto start_merge = high_resolution_clock::now();
    mergeSort(arr, 0, n - 1);
    auto end_merge = high_resolution_clock::now();
    auto duration_merge = duration_cast<nanoseconds>(end_merge - start_merge);

    cout << "Sorted array: ";
    printArray(arr, n);
    cout << "Time taken by Merge Sort: " << duration_merge.count() << " nanoseconds" << endl;

    return 0;
}

// O(n log n) time complexity
// O(n) space

// 6
// 38 27 43 3 9 82