#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;

void generate(string filename, int n) {
    ofstream file(filename);
    file << n << endl;
    for(int i = 0; i < n; i++) {
        int num = rand() % 1000;
        file << num << " ";
    }
    file.close();
}

void generate(int t){
    for(int i = 0; i < t; i++) {
        string filename = "testcase" + to_string(i) + ".txt";
        int n = rand() % 901 + 100; // Generate a random size between 100 and 1000
        generate(filename, n);
    }
}

int main(){
    srand(time(0));
    int t;
    cout << "Enter number of test cases: ";
    cin >> t;
    generate(t);
    return 0;
}