#include <iostream>
#include <vector>
#include<chrono>
using namespace std::chrono;
using namespace std;

int sum(vector<int> &freq, int i, int j) {
    int s = 0;
    for(int k = i; k <= j; k++){
        s += freq[k];
    }
    return s;
}

// Function to calculate minimum cost of a Binary Search Tree using DP (tabulation)
int minCost(vector<int> &keys, vector<int> &freq) {

    int n = keys.size();

    // Create a 2D DP table to store minimum costs for subarrays of keys
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Base case: cost of a single key is its frequency
    for (int i = 0; i < n; i++) {
        dp[i][i] = freq[i];
    }

    // Consider chains of length 2 to n
    for(int l = 2; l <= n; l++){
        for(int i = 0; i <= n - l; i++){
            // j is the ending index of the chain
            int j = i + l - 1;
            dp[i][j] = INT_MAX;

            // Total frequency sum of keys in current range
            int fsum = sum(freq, i, j);

            // Try each key in range [i..j] as root
            for (int r = i; r <= j; r++){
                // Cost when keys[r] is root:
                // cost of left subtree + cost of right subtree + sum of frequencies
                int c = ((r > i) ? dp[i][r - 1] : 0) + ((r < j) ? dp[r + 1][j] : 0) + fsum;

                // Update minimum cost
                if (c < dp[i][j]) {
                    dp[i][j] = c;
                }
            }
        }
    }

    // dp[0][n-1] stores minimum cost for all keys
    return dp[0][n - 1];
}
int main() {

    vector<int> keys;
    vector<int> freq;
    int n;
    cout << "Enter number of keys: ";
    cin >> n;

    cout << "Enter keys (sorted): ";
    for (int i = 0; i < n; i++) {
        int key;
        cin >> key;
        keys.push_back(key);
    }

    cout << "Enter frequency counts: ";
    for(int i=0; i<n; i++){
        int f;
        cin >> f;
        freq.push_back(f);
    }
    auto st = high_resolution_clock::now();
    cout << "The minimum Cost is: " << minCost(keys, freq);
    auto end = high_resolution_clock::now();
    auto execTime = duration_cast<microseconds>(end - st);
    cout << "\nExecution time: " << execTime.count() << " microseconds";
    return 0;
}

// Input: 
// 3
// 10 12 20
// 34 8 50