#include<iostream>
#include<chrono>
using namespace std;
using namespace std::chrono;

// Insertion sort to sort activities based on finish time
void insertion_sort(string activities[], int start_time[], int finish_time[], int n){
    for(int i=1; i < n; i++){
        string key_a = activities[i];
        int key_s = start_time[i];
        int key_f = finish_time[i];
        int j = i-1;
        while(j>=0 && finish_time[j] > key_f){
            activities[j+1] = activities[j];
            start_time[j+1] = start_time[j];
            finish_time[j+1] = finish_time[j];
            j--;
        }
        activities[j+1] = key_a;
        start_time[j+1] = key_s;
        finish_time[j+1] = key_f;
    }
}

// Function to perform activity selection
int activity_selection(string activities[], int start_time[], int finish_time[], int n){
    insertion_sort(activities, start_time, finish_time, n);
    int count = 1;
    cout << "Selected Activities: " << activities[0] << " ";
    int last_finish_time = finish_time[0];
    for(int i=1; i<n; i++){
        if(start_time[i] >= last_finish_time){
            cout << activities[i] << " ";
            last_finish_time = finish_time[i];
            count++;
        }
    }
    cout << "(Count: " << count << ")" << endl;
    return count;
}

int main(){
    int n;
    cout << "Enter the no. of Activities: ";
    cin >> n;
    string activities[n];
    int start_time[n], finish_time[n];

    // input
    for(int i=0; i<n; i++){
        activities[i] = "A" + to_string(i);
        cout << "Enter the start time of activity - A" << i << ": ";
        cin >> start_time[i];
        cout << "Enter the finish time of actvity - A" << i << ": ";
        cin >> finish_time[i];
    }
    auto start = high_resolution_clock::now();
    activity_selection(activities, start_time, finish_time, n); // activity selection
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken: " << duration.count() << " microseconds" << endl;
    return 0;
}

// Time complexity: O(n^2) due to insertion sort, O(n) for activity selection, overall O(n^2)
// Space complexity: O(n) for storing activities, start and finish times.

// Sample Input:
/*
5
1 4
3 5
0 6
5 7
8 9
*/