#include<iostream>
#include<chrono>
using namespace std;

// Fractional Knapsack Problem using Greedy Approach

// Sort items by profit/weight ratio in descending order
void insertion_sort(string name[], int weight[], int profit[], double pByw[], double x[], int n){
    for(int i=1; i < n; i++){
        string key_n = name[i];
        int key_w = weight[i];
        int key_p = profit[i];
        double key_pbw = pByw[i];
        double key_x = x[i];
        int j = i-1;
        while(j>=0 && pByw[j] < key_pbw){
            name[j+1] = name[j];
            weight[j+1] = weight[j];
            profit[j+1] = profit[j];
            pByw[j+1] = pByw[j];
            x[j+1] = x[j];
            j--;
        }
        name[j+1] = key_n;
        weight[j+1] = key_w;
        profit[j+1] = key_p;
        pByw[j+1] = key_pbw;
        x[j+1] = key_x;
    }
}

int main(){
    int n;
    cout << "Enter the number of weights: ";
    cin >> n;
    
    // Arrays to store item details
    string name[n];      // Item names
    int weight[n];       // Item weights
    int profit[n];       // Item profits
    double pByw[n];      // Profit/Weight ratio
    double x[n];         // Fraction of item taken (0 to 1)
    int bagSize;
    
    cout << "Enter the size of your bag: ";
    cin >> bagSize;
    
    // Input weights
    cout << "Enter the " << n << " weights: ";
    for(int i=0; i<n; i++){
        cin >> weight[i];
        name[i] = "w" + to_string(i);
        x[i] = 0;
    }
    
    // Input profits and calculate profit/weight ratio
    cout << "Enter the " << n << " profits: ";
    for(int i=0; i<n; i++){
        cin >> profit[i];
        pByw[i] = (double)profit[i] / weight[i];
    }
    
    // Display original items
    cout << "\n\nThe weights are:\n";
    cout << "Name\tWeight\tProfit\tProfit/Weight\tFraction Taken\n";
    for(int i=0; i<n; i++){
        cout << name[i] << "\t" << weight[i] << "\t" << profit[i] << "\t" << pByw[i] << "\t\t" << x[i] << "\n";
    }
    
    // Start timer
    auto start = chrono::high_resolution_clock::now();
    
    // Sort by profit/weight ratio (greedy choice)
    insertion_sort(name, weight, profit, pByw, x, n);
    
    // Fill knapsack greedily
    int currentBagSize = bagSize;
    for(int i=0; i<n; i++){
		if(currentBagSize > 0){
            // If item fits completely, take it fully
        	if(weight[i] <= currentBagSize){
           		x[i] = 1;
            	currentBagSize -= weight[i];
        	}
            // Else take fraction of item
        	else{
            	x[i] = (double)currentBagSize / weight[i];
            	break;
        	} 
		}
    }
    
    // Display selected items
    cout << "\n\n\nThe weights taken in the bag are:\n";
    cout << "Name\tWeight\tProfit\tProfit/Weight\tFraction Taken\n";
    // Calculate total profit
    double totalProfit = 0;
    for(int i=0; i<n; i++){
        cout << name[i] << "\t" << weight[i] << "\t" << profit[i] << "\t" << pByw[i] << "\t\t" << x[i] << "\n";
        totalProfit += profit[i] * x[i];
    }
    
    // Stop timer
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    
    // Display results
    cout << "\nTotal profit: " << totalProfit << "\n";
    cout << "Execution time: " << duration.count() << " microseconds\n";
}

// Time Complexity: O(n^2) due to insertion sort
// Can be improved to O(n log n) using merge/quick sort

/*
Sample Input:
15
750
70 73 77 80 82 87 90 94 98 106 110 113 115 118 120
135 139 149 150 156 163 173 184 192 201 210 214 221 229 240
*/