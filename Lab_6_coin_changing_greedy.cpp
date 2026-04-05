#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;

long long greedy_solve(vector<int> coins, int amount){
    if(amount == 0) return 0;
    sort(coins.begin(), coins.end(), greater<int>());
    int n = coins.size();
    vector<int> used(n, 0);
    long long totalCoins = 0;
    int remaining = amount;

    for(int i = 0; i < n && remaining > 0; ++i){
        if(coins[i] <= 0) continue;
        if(coins[i] <= remaining){
            int take = remaining / coins[i];
            used[i] = take;
            totalCoins += take;
            remaining -= take * coins[i];
        }
    }

    if(remaining != 0) return -1; // not possible with greedy selection

    // print selection
    cout << "\nGreedy selection (coin:value -> count):\n";
    for(int i = 0; i < n; ++i){
        cout << coins[i] << " -> " << used[i] << "\n";
    }

    return totalCoins;
}

int main(){
    int n, V;
    cout << "Enter number of coin types: ";
    if(!(cin >> n) || n <= 0){
        cout << "Invalid number of coins." << endl;
        return 0;
    }

    vector<int> coins(n);
    cout << "Enter " << n << " coin denominations (positive integers): ";
    for(int i = 0; i < n; ++i) cin >> coins[i];

    cout << "Enter target amount V: ";
    cin >> V;
    if(V < 0){
        cout << "Invalid target amount." << endl;
        return 0;
    }

    auto t0 = chrono::high_resolution_clock::now();
    long long result = greedy_solve(coins, V);
    auto t1 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();

    if(result == -1){
        cout << "\nGreedy algorithm could not make amount " << V << " with given denominations." << "\n";
    }
    else{
        cout << "\nMinimum number of coins (greedy) to make " << V << " = " << result << "\n";
    }
    cout << "Greedy computation time: " << duration << " microseconds\n";

    return 0;
}
