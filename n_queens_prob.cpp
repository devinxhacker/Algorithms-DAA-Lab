#include<iostream>
#include<math.h>
#include<chrono>
using namespace std;
using namespace std::chrono;

int x[10]; // x[i] = column position of queen in row i
int cnt = 0; // Count of valid solutions

int place(int k, int i){
    for(int j=1; j<k; j++){
        if(x[j]==i || abs(x[j]-i)==abs(j-k)){ // same column or same diagonal check
            return 0;
        }    
    }
    return 1;
}

void print(int n){ //printing purpose
    cnt++;
    cout << "Solution " << cnt << ": " << endl;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(x[i] == j){
                cout << "Q ";
            }
            else{
                cout << "_ ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void n_queens(int k, int n){ // k = current row, n = total queens
    for(int i=1; i<=n; i++){
        if(place(k, i)){
            x[k] = i;
            if(k==n){
                print(n);
            }
            else{
                n_queens(k+1, n);
            }
        }
    }
}

int main(){
    int n;
    cout << "Enter the number of queens: ";
    cin >> n;
    auto start = high_resolution_clock::now();
    n_queens(1, n);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time taken: " << duration.count() << " microseconds" << endl;
    cout << "Total solutions: " << cnt << endl;
    return 0;
}