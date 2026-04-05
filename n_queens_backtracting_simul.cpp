#include<iostream>
#include<math.h>
using namespace std;

int x[10];
int stepNo = 0;

int place(int k, int i){
    for(int j=1; j<k; j++){
        if(x[j]==i || abs(x[j]-i)==abs(j-k)){
            return 0;
        }    
    }
    return 1;
}

void printBoard(int n){
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

void showStep(int n, const string &action, int row, int col){
    stepNo++;
    cout << "Step " << stepNo << ": " << action << " (row " << row << ", col " << col << ")" << endl;
    printBoard(n);
}

bool n_queens(int k, int n){
    for(int i=1; i<=n; i++){
        if(place(k, i)){
            x[k] = i;
            showStep(n, "Place queen", k, i);

            if(k==n){
                cout << "First solution found:" << endl;
                printBoard(n);
                return true;
            }
            else{
                if(n_queens(k+1, n)){
                    return true;
                }
            }

            showStep(n, "Backtrack from", k, i);
            x[k] = 0;
        }
    }

    return false;
}

int main(){
    int n;
    cout << "Enter the number of queens: ";
    cin >> n;

    if(!n_queens(1, n)){
        cout << "No solution exists for n = " << n << endl;
    }

    cout << "Simulation steps shown: " << stepNo << endl;
    return 0;
}