#include<iostream>
using namespace std;

int high(int num, int m){
    return num / pow(10, m);
}

int low(int num, int m){
    return num % (int)pow(10, m);
}

// Karatsuba Multiplication
int multiplication(int x, int y){
    if(x<10 || y<10){
        return x*y;
    }
    int n = max(to_string(x).size(), to_string(y).size());
    int m = floor(n/2);
    int a = high(x, m);
    int b = low(x, m);
    int c = high(y, m);
    int d = low(y, m);

    cout << "a: " << a << ", b: " << b << ", c: " << c << ", d: " << d << endl;

    int p1 = multiplication(a, c);
    int p2 = multiplication(b, d);
    int p3 = multiplication(a+b, c+d);

    int result = p1 * pow(10, 2*m) + (p3 - p1 - p2) * pow(10, m) + p2;
    return result;
}

int main(){
    // Large integer multiplication: 
    int x, y;
    cout << "Enter two large integers: ";
    cin >> x >> y;
    int product = multiplication(x, y);
    cout << "Product: " << product << endl;
    return 0;
}