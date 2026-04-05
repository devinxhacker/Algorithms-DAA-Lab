#include <iostream>
#include <chrono>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;
using namespace std::chrono;

#include "quickSortReg.cpp"
#include "quickSortRand.cpp"

int main() {

    string files[10] = {
        "testcase0.txt", "testcase1.txt", "testcase2.txt", "testcase3.txt", "testcase4.txt",
        "testcase5.txt", "testcase6.txt", "testcase7.txt", "testcase8.txt", "testcase9.txt"
    };

    cout << "Test Case\tSize\tRandom Pivot Quick Sort (ns)\tFirst Pivot Quick Sort (ns)\n";

    cout << "--------------------------------------------------------------------------\n";

    for (int i = 0; i < 10; i++) {
        SortRandomPivot a(0);
        a.upload(files[i]);
        int size = a.getSize();

        auto start = high_resolution_clock::now();
        a.quickSort(0, a.getSize() - 1);
        auto end = high_resolution_clock::now();
        auto time1 = duration_cast<nanoseconds>(end - start);

        SortFirstPivot b(0);
        b.upload(files[i]);

        start = high_resolution_clock::now();
        b.quickSort(0, b.getSize() - 1);
        end = high_resolution_clock::now();
        auto time2 = duration_cast<nanoseconds>(end - start);

        string outFile = "output" + to_string(i) + ".txt";
        ofstream clearFile(outFile);
        clearFile.close();

        ofstream fout1(outFile, ios::app);
        fout1 << "First Pivot Output:\n";
        fout1.close();
        a.saveToFile(outFile);

        ofstream fout2(outFile, ios::app);
        fout2 << "Random Pivot Output:\n";
        fout2.close();
        b.saveToFile(outFile);

        cout << "Test Case " << i + 1 << "\t" << size << "\t" << time1.count() << "\t\t\t\t" << time2.count() << "\n";
    }

    return 0;
}
