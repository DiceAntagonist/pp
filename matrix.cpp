#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    int N;
    cout << "Enter the size of the matrix (N x N): ";
    cin >> N;

    int A[N][N], B[N][N], C[N][N];

    cout << "Enter elements of matrix A:\n";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> A[i][j];

    cout << "Enter elements of matrix B:\n";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> B[i][j];

    // Initialize C
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            C[i][j] = 0;

    double start_time = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }

    double end_time = omp_get_wtime();

    // Print result after parallel computation
    cout << "Resultant matrix C:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Time taken: " << (end_time - start_time) * 1000 << " ms\n";
    return 0;
}
