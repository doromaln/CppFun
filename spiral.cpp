// How to print a spiral matrix.

#include <iostream>

using namespace std;

template <int N, int M>
void print_spiral(int (&matrix)[N][M]) {
    int start_n = 0, end_n = N;
    int start_m = 0, end_m = M;
    
    while ((start_n < end_n) && (start_m < end_m)) {
        // print top of box.
        for (int i = start_m; i < end_m; ++i) {
            cout << matrix[start_n][i] << " ";
        }
        // print right side.
        for (int i = (start_n + 1); i < (end_n - 1); ++i) {
            cout << matrix[i][end_m - 1] << " ";
        }
        // print bottom.
        if (start_n != (end_n - 1)) {
            for (int i = (end_m - 1); i >= start_m; --i) {
                cout << matrix[end_n - 1][i] << " ";
            }
        } 
        // print left side.
        if (start_m != (end_m - 1)) {
            for (int i = (end_n - 2); i > start_m; --i) {
                cout << matrix[i][start_n] << " ";
            }
        }

        start_n++;
        end_n--;
        start_m++;
        end_m--;
    }
}

template <int N, int M>
void do_test_case(int testno, int (&matrix)[N][M]) {
    cout << "\n-- Test case " << testno << " --\n";
    print_spiral(matrix);
    cout << "\n";
}

int main() {
    int arr1[3][4] = {{1, 2, 3, 4},
                     {5, 6, 7, 8},
                     {9, 8, 10, 11}};
    do_test_case(1, arr1);

    int arr2[1][1] = {{1}};
    do_test_case(2, arr2);

    int arr3[3][1] = {{1}, {2}, {3}};
    do_test_case(3, arr3);

    int arr4[1][3] = {{1, 2, 3}};
    do_test_case(4, arr4);

    int arr5[2][3] = {{1, 2, 3}, {4, 5, 6}};
    do_test_case(5, arr5);

    int arr6[3][2] = {{1, 2}, {2, 3}, {4, 5}};
    do_test_case(6, arr6);

    int arr7[5][5] = {{1, 2, 3, 4, 5},
                      {6, 7, 8, 9, 10},
                      {11, 12, 13, 14, 15},
                      {16, 17, 18, 19, 20},
                      {21, 22, 23, 24, 25}};
    do_test_case(7, arr7);

    return 1;
}

