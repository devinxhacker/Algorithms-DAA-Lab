#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

long long solve(const vector<int> coins, int amount){
    int n = coins.size();
    int dp[n][amount+1];
    for(int i=0; i<=amount; i++){
        if(i%coins[0]==0){
            dp[0][i] = 1;
        }
        else dp[0][i] = 0;
    }
    for(int i=1; i<n; i++){
        for(int j=0; j<=amount; j++){
            if(coins[i] > j){
                dp[i][j] = dp[i-1][j];
            }
            else{
                dp[i][j] = dp[i-1][j] + dp[i][j-coins[i]];
            }
        }
    }
    cout << "\nDP table (rows = coins considered, cols = sum 0..V):\n";
    cout << "coins\\amount";
    for (int j = 0; j <= amount; j++) cout << "\t" << j;
    cout << '\n';

    for (int i = 0; i < n; i++) {
        cout << i << "(" << coins[i] << ")\t";
        for (int j = 0; j <= amount; j++) {
            cout << "\t" << dp[i][j];
        }
        cout << '\n';
    }
    return dp[n-1][amount];
}

int main() {
    int n, V;
    cout << "Enter number of coin types: ";
    if (!(cin >> n) || n <= 0) {
        cout << "Invalid number of coins." << endl;
        return 0;
    }

    vector<int> coins(n);
    cout << "Enter " << n << " coin denominations (positive integers): ";
    for (int i = 0; i < n; ++i) cin >> coins[i];

    cout << "Enter target amount V: ";
    cin >> V;
    if (V < 0) {
        cout << "Invalid target amount." << endl;
        return 0;
    }

    // Time the DP tabulation
    auto t0 = chrono::high_resolution_clock::now();
    long long ways = solve(coins, V);
    auto t1 = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();

    // Print results
    cout << "\nNumber of ways to make " << V << " = " << ways << "\n";
    cout << "DP computation time: " << duration << " microseconds\n";    

    return 0;
}

// Time Complexity: O(n*V) where n is number of coin types and V is target amount
// Space Complexity: O(n*V) for the DP table

// Sample Input:
// 4
// 2 5 3 6
// 10