#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main() {
    int n, max_value;
    cout << "Enter no of elements: ";
    cin >> n;
    cout << "Maximum value: ";
    cin >> max_value;

    vector<int> data(n);
    cout << "Enter elements:\n";
    for (int& num : data) {
        cin >> num;
    }

    vector<int> histogram(max_value + 1, 0);
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        #pragma omp atomic
        histogram[data[i]]++;
    }

    cout << "Sorted elements:\n";
    for (int value = 0; value <= max_value; value++) {
        for (int count = 0; count < histogram[value]; count++) {
            cout << value << " ";
        }
    }
    cout << endl;
    
    return 0;
}
