// main_rec.cpp
// Оленчук Євгеній
// Лабораторна робота № 7.3.
// Опрацювання динамічних багатовимірних масивів рекурсивним способом.
// Варіант 10.

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

void CreateRow(int** Q, const int rowNo, const int n, const int Low, const int High, int colNo);
void CreateRows(int** Q, const int n, const int Low, const int High, int rowNo);
void PrintRow(int** Q, const int rowNo, const int n, int colNo);
void PrintRows(int** Q, const int n, int rowNo);
bool IsLocalMinInRow(int** Q, const int n, const int i, const int j, const int k, int l);
bool IsLocalMin(int** Q, const int n, const int i, const int j, int k);
void CountLocalMinInRow(int** Q, const int n, const int i, int& count, int j);
void CountLocalMin(int** Q, const int n, int& count, int i);
int SumAbsInRow(int** Q, const int n, const int i, int j);
int SumAbsAboveDiagonal(int** Q, const int n, int i);

int main()
{
    int Low, High, n, count, S, i;   // Low, High: діапазон значень; n: розмір матриці n x n; count: кількість локальних мінімумів; S: сума модулів; i: лічильник циклу
    int** Q;

    srand((unsigned)time(NULL));   // щоб числа були різними при кожному запуску

    Low = -9;
    High = 9;

    cout << "n = ";
    cin >> n;   // n: розмір квадратної матриці, вводить користувач

    Q = new int* [n];   // виділення пам'яті: масив вказівників на рядки
    for (i = 0; i < n; i++)
        Q[i] = new int[n];   // пам'ять під кожен рядок

    CreateRows(Q, n, Low, High, 0);
    cout << endl;
    PrintRows(Q, n, 0);

    count = 0;   // перед першим викликом лічильник дорівнює 0
    CountLocalMin(Q, n, count, 0);   // кількість повертається через параметр-посилання
    cout << "Local minima count = " << count << endl;

    S = SumAbsAboveDiagonal(Q, n, 0);   // сума повертається через return
    cout << "Sum of abs above main diagonal = " << S << endl;

    for (i = 0; i < n; i++)
        delete[] Q[i];   // звільнення пам'яті: спочатку рядки, потім масив вказівників
    delete[] Q;

    return 0;
}

// Рекурсивне заповнення одного рядка: один виклик заповнює один елемент
void CreateRow(int** Q, const int rowNo, const int n, const int Low, const int High, int colNo)
{
    Q[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < n - 1)
        CreateRow(Q, rowNo, n, Low, High, colNo + 1);
}

// Рекурсивне заповнення всіх рядків: один виклик заповнює один рядок
void CreateRows(int** Q, const int n, const int Low, const int High, int rowNo)
{
    CreateRow(Q, rowNo, n, Low, High, 0);
    if (rowNo < n - 1)
        CreateRows(Q, n, Low, High, rowNo + 1);
}

// Рекурсивне виведення одного рядка: один виклик виводить один елемент
void PrintRow(int** Q, const int rowNo, const int n, int colNo)
{
    cout << setw(5) << Q[rowNo][colNo];   // кожен елемент у полі шириною 5 символів
    if (colNo < n - 1)
        PrintRow(Q, rowNo, n, colNo + 1);
    else
        cout << endl;
}

// Рекурсивне виведення всіх рядків: один виклик виводить один рядок
void PrintRows(int** Q, const int n, int rowNo)
{
    PrintRow(Q, rowNo, n, 0);
    if (rowNo < n - 1)
        PrintRows(Q, n, rowNo + 1);
    else
        cout << endl;
}

// Чи Q[i][j] строго менший за сусідів у рядку k (рекурсією): l – поточний стовпець, виклик починається з j-1
bool IsLocalMinInRow(int** Q, const int n, const int i, const int j, const int k, int l)
{
    if (l > j + 1)   // база рекурсії: стовпці сусідів закінчились
        return true;

    if (l >= 0 && l < n && !(k == i && l == j) && Q[k][l] <= Q[i][j])   // сусід існує, це не сам елемент, і він не більший
        return false;

    return IsLocalMinInRow(Q, n, i, j, k, l + 1);
}

// Чи Q[i][j] строго менший за всіх сусідів (рекурсією): k – поточний рядок, виклик починається з i-1
bool IsLocalMin(int** Q, const int n, const int i, const int j, int k)
{
    if (k > i + 1)   // база рекурсії: рядки сусідів закінчились
        return true;

    if (k >= 0 && k < n && !IsLocalMinInRow(Q, n, i, j, k, j - 1))   // рядок існує, і в ньому є не більший сусід
        return false;

    return IsLocalMin(Q, n, i, j, k + 1);
}

// Підрахунок локальних мінімумів в рядку i (рекурсією): j – поточний стовпець, виклик починається з 0
void CountLocalMinInRow(int** Q, const int n, const int i, int& count, int j)
{
    if (IsLocalMin(Q, n, i, j, i - 1))
        count++;
    if (j < n - 1)
        CountLocalMinInRow(Q, n, i, count, j + 1);
}

// Підрахунок локальних мінімумів в усій матриці (рекурсією): i – поточний рядок, виклик починається з 0
void CountLocalMin(int** Q, const int n, int& count, int i)
{
    CountLocalMinInRow(Q, n, i, count, 0);
    if (i < n - 1)
        CountLocalMin(Q, n, count, i + 1);
}

// Сума модулів елементів рядка i правіше діагоналі (рекурсією): j – поточний стовпець, виклик починається з i+1
int SumAbsInRow(int** Q, const int n, const int i, int j)
{
    if (j >= n)   // база рекурсії: рядок закінчився
        return 0;

    return abs(Q[i][j]) + SumAbsInRow(Q, n, i, j + 1);
}

// Сума модулів елементів вище головної діагоналі (рекурсією): i – поточний рядок, виклик починається з 0
int SumAbsAboveDiagonal(int** Q, const int n, int i)
{
    if (i >= n - 1)   // база рекурсії: в останньому рядку елементів вище діагоналі немає
        return 0;

    return SumAbsInRow(Q, n, i, i + 1) + SumAbsAboveDiagonal(Q, n, i + 1);
}
