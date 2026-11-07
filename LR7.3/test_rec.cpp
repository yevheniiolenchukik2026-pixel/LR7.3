// test_rec.cpp
// Оленчук Євгеній
// Unit-тест до лабораторної роботи № 7.3 (рекурсивний спосіб). Варіант 10.

#include <cstdio>
#include <iostream>

#define main program_main   // тимчасово перейменовуємо main з main.cpp, щоб не було двох main
#include "main_rec.cpp"
#undef main                 // повертаємо ім'я main для тесту

using namespace std;

// Порівнює очікуване і фактичне значення, виводить PASS або FAIL, повертає 0 або 1
int Check(const char* name, const int expected, const int actual)
{
    if (expected == actual)
    {
        cout << "PASS  " << name << ": expected " << expected << ", got " << actual << endl;
        return 0;
    }
    cout << "FAIL  " << name << ": expected " << expected << ", got " << actual << endl;
    return 1;
}

// Будує динамічну матрицю n x n зі звичайного масиву (функції працюють з int**)
int** MakeMatrix(const int n, const int* data)
{
    int i, j;
    int** Q;

    Q = new int* [n];
    for (i = 0; i < n; i++)
    {
        Q[i] = new int[n];
        for (j = 0; j < n; j++)
            Q[i][j] = data[i * n + j];
    }

    return Q;
}

// Звільняє пам'ять матриці
void FreeMatrix(int** Q, const int n)
{
    int i;

    for (i = 0; i < n; i++)
        delete[] Q[i];
    delete[] Q;
}

int main()
{
    int n, count, failed;
    int** Q;
    // data1: матриця 4 x 4, локальні мінімуми: 1 (1,1), 2 (0,3), 0 (2,3)
    int data1[4 * 4] = {
        5, 3, 8, 2,
        4, 1, 7, 9,
        6, 2, 5, 0,
        9, 8, 4, 3
    };
    // data2: матриця 3 x 3 з від'ємними та рівними числами, мінімум має бути строгим
    int data2[3 * 3] = {
        -1, -1,  4,
        -5,  2, -3,
         7,  0, -8
    };
    // data3: усі елементи рівні, строгих мінімумів немає
    int data3[2 * 2] = {
        3, 3,
        3, 3
    };

    failed = 0;

    n = 4;
    Q = MakeMatrix(n, data1);
    // 3 локальні мінімуми; сума модулів: 3+8+2+7+9+0 = 29
    count = 0;   // для рекурсивної функції лічильник обнуляємо перед викликом
    CountLocalMin(Q, n, count, 0);
    failed += Check("CountLocalMin, matrix 4 x 4", 3, count);
    failed += Check("SumAbsAboveDiagonal, matrix 4 x 4", 29, SumAbsAboveDiagonal(Q, n, 0));
    FreeMatrix(Q, n);

    n = 3;
    Q = MakeMatrix(n, data2);
    // 2 локальні мінімуми (-5 і -8); сума модулів: 1+4+3 = 8
    count = 0;   // для рекурсивної функції лічильник обнуляємо перед викликом
    CountLocalMin(Q, n, count, 0);
    failed += Check("CountLocalMin, negative matrix 3 x 3", 2, count);
    failed += Check("SumAbsAboveDiagonal, negative matrix 3 x 3", 8, SumAbsAboveDiagonal(Q, n, 0));
    FreeMatrix(Q, n);

    n = 2;
    Q = MakeMatrix(n, data3);
    // усі рівні: строгих мінімумів 0; сума модулів: 3
    count = 0;   // для рекурсивної функції лічильник обнуляємо перед викликом
    CountLocalMin(Q, n, count, 0);
    failed += Check("CountLocalMin, equal elements 2 x 2", 0, count);
    failed += Check("SumAbsAboveDiagonal, equal elements 2 x 2", 3, SumAbsAboveDiagonal(Q, n, 0));
    FreeMatrix(Q, n);

    if (failed == 0)
        cout << endl << "ALL TESTS PASSED" << endl;
    else
        cout << endl << "FAILED: " << failed << endl;

    return failed;
}
