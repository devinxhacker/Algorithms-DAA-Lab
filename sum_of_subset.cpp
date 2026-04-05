#include<iostream>

using namespace std;

int w[100];
bool subset[100];
int target;
int n;

void sumOfSubsets(int k, int current_sum, int remaining_sum){
    if(current_sum == target){
        cout << "Subset found: { ";
        for(int i=1; i<k; i++){
            if(subset[i]){
                cout << w[i] << " ";
            }
        }
        cout << "}" << endl;
        return;
    }

    if(k>n) return;

    if(current_sum + w[k] <= target){
        subset[k] = true;
        sumOfSubsets(k+1, current_sum + w[k], remaining_sum - w[k]);
    }

    if(current_sum + remaining_sum - w[k] >= target){
        subset[k] = false;
        sumOfSubsets(k+1, current_sum, remaining_sum - w[k]);
    }
}

int main(){
    int total_sum = 0;

    cout << "Enter number og elements: ";
    cin >> n;
    cout << "Enter the elements: ";
    for(int i=1; i<=n; i++){
        cin >> w[i];
        total_sum += w[i];
    }
    cout << "Enter target sum: ";
    cin >> target;

    cout << "\nResults: " << endl;
    sumOfSubsets(1, 0, total_sum);
}