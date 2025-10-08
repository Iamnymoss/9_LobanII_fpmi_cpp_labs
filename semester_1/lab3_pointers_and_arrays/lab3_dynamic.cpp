#include <iostream>
#include <random>
#include <cmath>

void inputArray(double arr[], int n) {
    std::cout << "Введите " << n << " элементов массива:\n";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
}

void fillRandomArray(double arr[], int n, double a, double b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(a, b);

    for (int i = 0; i < n; i++) {
        arr[i] = dist(gen);
    }
}

void printArray(double arr[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

double sumBetweenFirstMaxAndLastMin(double arr[], int n) {
    if (n <= 1) return 0;

    int firstMaxIndex = 0;
    int lastMinIndex = 0;

    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[firstMaxIndex]) {
            firstMaxIndex = i;
        }
        if (arr[i] <= arr[lastMinIndex]) {
            lastMinIndex = i;
        }
    }

    int startIndex, endIndex;
    if (firstMaxIndex < lastMinIndex) {
        startIndex = firstMaxIndex + 1;
        endIndex = lastMinIndex - 1;
    }
    else {
        startIndex = lastMinIndex + 1;
        endIndex = firstMaxIndex - 1;
    }

    double sum = 0;
    bool hasElements = false;

    for (int i = startIndex; i <= endIndex; i++) {
        sum += arr[i];
        hasElements = true;
    }

    return hasElements ? sum : 0;
}

void swapMinAbsAndMaxAbs(double arr[], int n) {
    if (n <= 1) return;

    int minAbsIndex = 0;
    int maxAbsIndex = 0;

    for (int i = 1; i < n; i++) {
        if (std::abs(arr[i]) < std::abs(arr[minAbsIndex])) {
            minAbsIndex = i;
        }
        if (std::abs(arr[i]) > std::abs(arr[maxAbsIndex])) {
            maxAbsIndex = i;
        }
    }

    double temp = arr[minAbsIndex];
    arr[minAbsIndex] = arr[maxAbsIndex];
    arr[maxAbsIndex] = temp;
}

void sortArray(double arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int n;
    int choice;

    std::cout << "Введите количество элементов массива: ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Некорректный размер массива!\n";
        return 1;
    }

    double* arr = new double[n];

    std::cout << "Выберите способ заполнения массива:\n";
    std::cout << "1 - Ввод с клавиатуры\n";
    std::cout << "2 - Заполнение случайными числами\n";
    std::cout << "Ваш выбор: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
        inputArray(arr, n);
        break;
    case 2:
        double a, b;
        std::cout << "Введите границы интервала [a, b]: ";
        std::cin >> a >> b;
        if (a > b) {
            std::cout << "Некорректные границы интервала!\n";
            delete[] arr;
            return 1;
        }
        fillRandomArray(arr, n, a, b);
        break;
    default:
        std::cout << "Некорректный выбор!\n";
        delete[] arr;
        return 1;
    }

    std::cout << "\nИсходный массив:\n";
    printArray(arr, n);

    double sum = sumBetweenFirstMaxAndLastMin(arr, n);
    std::cout << "\n1. Сумма элементов между первым максимальным и последним минимальным: "
        << sum << std::endl;

    swapMinAbsAndMaxAbs(arr, n);
    std::cout << "\n2. Массив после перестановки минимального и максимального по модулю элементов:\n";
    printArray(arr, n);

    sortArray(arr, n);
    std::cout << "\n3. Массив после сортировки по возрастанию:\n";
    printArray(arr, n);

    delete[] arr;
    return 0;
}