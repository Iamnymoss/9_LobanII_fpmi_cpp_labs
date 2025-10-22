#include <iostream>
#include <random>
#include <limits>
#include<Windows.h>

using namespace std;

void manualInput(int** matrix, int n) {
    cout << "Введите элементы матрицы " << n << "x" << n << ":\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "Элемент [" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
        }
    }
}

void randomFill(int** matrix, int n ,int a ,int b) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(a ,b);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = dist(gen);
        }
    }
}

void printMatrix(int** matrix ,int n) {
    cout << "Матрица:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void findMaxInColumnsWithoutPositives(int** matrix, int n) {
    cout << "\nМаксимальные элементы в столбцах без положительных элементов:\n";
    bool foundAny = false;

    for (int j = 0; j < n; j++) {
        bool hasPositive = false;

        for (int i = 0; i < n; i++) {
            if (matrix[i][j] > 0) {
                hasPositive = true;
                break;
            }
        }

        if (!hasPositive) {
            int maxElement = matrix[0][j];
            for (int i = 1; i < n; i++) {
                if (matrix[i][j] > maxElement) {
                    maxElement = matrix[i][j];
                }
            }
            cout << "Столбец " << j << ": максимальный элемент = " << maxElement << endl;
            foundAny = true;
        }
    }

    if (!foundAny) {
        cout << "Нет столбцов без положительных элементов\n";
    }
}

int countNegativesInLowerRightTriangle(int** matrix ,int n) {
    int count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = n - 1 - i; j < n; j++) {
            if (matrix[i][j] < 0) {
                count++;
            }
        }
    }

    return count;
}

int main() {
    setlocale(LC_ALL ,"Russian");
    system("color 0A");
    int n;
    cout << "Введите размер квадратной матрицы: ";
    cin >> n;

    if (n <= 0) {
        cout << "Неверный размер матрицы!\n";
        return 1;
    }

    int** matrix = new int* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }

    int choice;
    cout << "\nВыберите способ заполнения матрицы:\n";
    cout << "1 - Ручной ввод\n";
    cout << "2 - Заполнение случайными числами\n";
    cout << "Ваш выбор: ";
    cin >> choice;

    switch (choice) {
    case 1:
        manualInput(matrix, n);
        break;
    case 2:
        int a, b;
        cout << "Введите границы интервала [a b]: ";
        cin >> a >> b;
        randomFill(matrix ,n, a, b);
        break;
    default:
        cout << "Неверный выбор!\n";
        for (int i = 0; i < n; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        return 1;
    }

    printMatrix(matrix ,n);

    findMaxInColumnsWithoutPositives(matrix ,n);

    int negativeCount = countNegativesInLowerRightTriangle(matrix, n);
    cout << "\nКоличество отрицательных элементов в нижнем правом треугольнике: "
        << negativeCount << endl;

    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}