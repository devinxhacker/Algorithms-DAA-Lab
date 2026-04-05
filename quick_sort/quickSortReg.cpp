#include<iostream>
#include<vector>
#include<cstdlib>
#include<fstream>
#include<chrono>
using namespace std;
using namespace std::chrono;

class SortFirstPivot {
    private:
        int n;
        vector<int> arr;
    public:
        SortFirstPivot(int size) {
            n = size;
            arr.resize(n);
        }
        void upload(string filename);
        void quickSort(int left, int right);
        void display();
        int getSize();
        void saveToFile(string filename);
};

void SortFirstPivot::upload(string filename) {
    freopen(filename.c_str(), "r", stdin);
    cin >> n;
    arr.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
}

void SortFirstPivot::quickSort(int left, int right){
    if(left < right) {
        // select the first element as pivot
        int pivotIndex = left;
        int pivotValue = arr[pivotIndex];
        
        // partition the array around the pivot
        int i = left, j = right;
        while(i <= j) {
            while(arr[i] < pivotValue) i++;
            while(arr[j] > pivotValue) j--;
            if(i <= j) {
                swap(arr[i], arr[j]);
                i++;
                j--;
            }
        }
        
        // recursively sort the partitions
        quickSort(left, j);
        quickSort(i, right);
    }
}
void SortFirstPivot::display() {
    for(int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int SortFirstPivot::getSize() {
    return n;
}

void SortFirstPivot::saveToFile(string filename) {
    ofstream fout(filename, ios::app);
    for(int i = 0; i < n; i++) {
        fout << arr[i] << " ";
    }
    fout << endl;
}

