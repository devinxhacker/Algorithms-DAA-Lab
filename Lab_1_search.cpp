#include<iostream>
#include<chrono>
using namespace std;
using namespace std::chrono;

// Quick Sort
long partition(long arr[], long low, long high) {
	long pivot = arr[low];
	long i = low;
	long j = high;
	while (i < j) {
		while (arr[i] <= pivot && i < high) {
			i++;
		}
		while (arr[j] > pivot && j > low) {
			j--;
		}
		if (i < j) {
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[low], arr[j]);
	return j;
}

void quick_sort(long arr[], long low, long high) {
	if (low < high) {
		long pi = partition(arr, low, high);
		quick_sort(arr, low, pi - 1);
		quick_sort(arr, pi + 1, high);
	}
}
 
// Linear Search
long linear_search(long arr[], long n, long key){
	for(int i=0; i<n;i++){
		if(arr[i] == key){
			return i;
		}
	}
	return -1;
}
 
 
//binary search
long binary_search(long arr[], long n, long key, long s, long e){
	if(s>e) return -1;
	long mid = s+(e-s)/2;
	if(arr[mid] == key){
		return mid;
	}
	else if(arr[mid] > key){
		e = mid-1;
		return binary_search(arr, n, key, s, e);
	}
	else{
		s = mid+1;
		return binary_search(arr, n, key, s, e);
	}
}
long binary_search(long arr[], long n, long key ){
	long s = 0;
	long e = n-1;
	return binary_search(arr, n, key, s, e);
}
 
int main(){
	long n;
	cout << "Enter the length of the array: ";
	cin >> n;
	long arr[n];
	cout << "Enter the array: ";
	for(int i=0; i< n; i++){
		cin >> arr[i];
	}
	long key;
	cout << "Enter the key to search: ";
	cin >> key;

	// Linear Search with timing
	auto start_linear = high_resolution_clock::now();
	long linear_result = linear_search(arr, n, key);
	auto end_linear = high_resolution_clock::now();
	auto duration_linear = duration_cast<nanoseconds>(end_linear - start_linear);


	// Quick Sort
	auto start_quick_sort = high_resolution_clock::now();
	quick_sort(arr, 0, n - 1);
	auto end_quick_sort = high_resolution_clock::now();
	auto duration_quick_sort = duration_cast<nanoseconds>(end_quick_sort - start_quick_sort);
	cout << "\nTime taken by Quick Sort: " << duration_quick_sort.count() << " nanoseconds" << endl;
	
	// Sorted array: 
	cout << "\nSorted Array for Binary Search: ";
	for(int i=0; i<n; i++){
		cout << arr[i] << " ";
	}
	cout << "\n" << endl;
	
	// Binary Search with timing
	auto start_binary = high_resolution_clock::now();
	long binary_result = binary_search(arr, n, key);
	auto end_binary = high_resolution_clock::now();
	auto duration_binary = duration_cast<nanoseconds>(end_binary - start_binary);
	
	cout << "\nLinear Search Result: " << linear_result << endl;
	cout << "Time taken by Linear Search: " << duration_linear.count() << " nanoseconds" << endl;
	cout << "\nBinary Search Result: " << binary_result << endl;
	cout << "Time taken by Binary Search: " << duration_binary.count() << " nanoseconds" << endl;
	return 0;
}

// test array: length = 100 (1 to 100 numbers in random order)
// arr = 34 7 23 32 5 62 32 45 78 12 90 11 3 56 89 21 67 43 29 8 14 19 27 38 41 50 72 81 6 9 15 18 22 25 30 33 36 39 42 44 46 48 51 53 55 57 59 61 63 65 68 70 73 75 77 79 80 82 84 86 88 91 93 95 97 99 2 4 10 13 16 17 20 24 26 28 31 35 37 40 47 49 52 54 58 60 64 66 69 71 74 76 83 85 87 92 94 96 98 100
// key = 67