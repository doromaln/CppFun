#include <iostream>

using namespace std;

template <int N, int M>
void print_matrix(int (&matrix)[N][M]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    int arr[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 10, 11}};
    print_matrix(arr);

    return 1;
}

