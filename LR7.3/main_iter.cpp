// main_iter.cpp
// Оленчук Євгеній
// Лабораторна робота № 7.3.
// Опрацювання динамічних багатовимірних масивів ітераційним способом.
// Варіант 10.

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

void Create(int** Q, const int n, const int Low, const int High);
void Print(int** Q, const int n);
bool IsLocalMin(int** Q, const int n, const int i, const int j);
void CountLocalMin(int** Q, const int n, int& count);
int SumAbsAboveDiagonal(int** Q, const int n);

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

    Create(Q, n, Low, High);
    Print(Q, n);

    CountLocalMin(Q, n, count);   // кількість повертається через параметр-посилання
    cout << "Local minima count = " << count << endl;

    S = SumAbsAboveDiagonal(Q, n);   // сума повертається через return
    cout << "Sum of abs above main diagonal = " << S << endl;

    for (i = 0; i < n; i++)
        delete[] Q[i];   // звільнення пам'яті: спочатку рядки, потім масив вказівників
    delete[] Q;

    return 0;
}

// Заповнення матриці випадковими числами з діапазону [Low, High]
void Create(int** Q, const int n, const int Low, const int High)
{
    int i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            Q[i][j] = Low + rand() % (High - Low + 1);   // rand() % розмір_діапазону + нижня межа
}

// Виведення матриці у вигляді таблиці
void Print(int** Q, const int n)
{
    int i, j;

    cout << endl;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            cout << setw(5) << Q[i][j];   // кожен елемент у полі шириною 5 символів
        cout << endl;
    }
    cout << endl;
}

// Перевірка: чи елемент Q[i][j] строго менший за всіх своїх сусідів (ітерацією)
bool IsLocalMin(int** Q, const int n, const int i, const int j)
{
    int k, l;

    for (k = i - 1; k <= i + 1; k++)
        for (l = j - 1; l <= j + 1; l++)
        {
            if (k < 0 || k >= n || l < 0 || l >= n)   // сусіда за межами матриці немає
                continue;
            if (k == i && l == j)   // сам елемент не є своїм сусідом
                continue;
            if (Q[k][l] <= Q[i][j])   // сусід не більший: мінімум не строгий
                return false;
        }

    return true;
}

// Підрахунок кількості локальних мінімумів (ітерацією), результат у count
void CountLocalMin(int** Q, const int n, int& count)
{
    int i, j;

    count = 0;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (IsLocalMin(Q, n, i, j))
                count++;
}

// Сума модулів елементів вище головної діагоналі (ітерацією): j > i
int SumAbsAboveDiagonal(int** Q, const int n)
{
    int i, j, S;

    S = 0;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)   // стовпці правіше діагоналі
            S += abs(Q[i][j]);

    return S;
}
