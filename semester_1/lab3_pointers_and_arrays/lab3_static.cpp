#include <iostream>
#include <random>
#include <limits>

const int MAX_SIZE = 100;

void inputArray(int arr[], int n) {
    std::cout << "������� " << n << " ��������� �������:\n";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
}

void fillRandomArray(int arr[], int n, int a, int b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(a, b);

    for (int i = 0; i < n; i++) {
        arr[i] = dist(gen);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int productBetweenLastMinMax(int arr[], int n) {
    if (n <= 1) return 0;

    int lastMinIndex = 0;
    int lastMaxIndex = 0;

    for (int i = 1; i < n; i++) {
        if (arr[i] <= arr[lastMinIndex]) {
            lastMinIndex = i;
        }
        if (arr[i] >= arr[lastMaxIndex]) {
            lastMaxIndex = i;
        }
    }

    int startIndex, endIndex;
    if (lastMinIndex < lastMaxIndex) {
        startIndex = lastMinIndex + 1;
        endIndex = lastMaxIndex - 1;
    }
    else {
        startIndex = lastMaxIndex + 1;
        endIndex = lastMinIndex - 1;
    }

    int product = 1;
    bool hasElements = false;

    for (int i = startIndex; i <= endIndex; i++) {
        product *= arr[i];
        hasElements = true;
    }

    return hasElements ? product : 0;
}

void sortArray(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int removeForStrictlyIncreasing(int arr[], int n) {
    if (n <= 1) return 0;

    int removedCount = 0;
    int currentIndex = 0;

    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[currentIndex]) {
            currentIndex++;
            arr[currentIndex] = arr[i];
        }
        else {
            removedCount++;
        }
    }

    return removedCount;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int arr[MAX_SIZE];
    int n;
    int choice;

    std::cout << "������� ���������� ��������� ������� (�� ����� " << MAX_SIZE << "): ";
    std::cin >> n;

    if (n <= 0 || n > MAX_SIZE) {
        std::cout << "������������ ������ �������!\n";
        return 1;
    }

    std::cout << "�������� ������ ���������� �������:\n";
    std::cout << "1 - ���� � ����������\n";
    std::cout << "2 - ���������� ���������� �������\n";
    std::cout << "��� �����: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
        inputArray(arr, n);
        break;
    case 2:
        int a, b;
        std::cout << "������� ������� ��������� [a, b]: ";
        std::cin >> a >> b;
        if (a > b) {
            std::cout << "������������ ������� ���������!\n";
            return 1;
        }
        fillRandomArray(arr, n, a, b);
        break;
    default:
        std::cout << "������������ �����!\n";
        return 1;
    }

    std::cout << "\n�������� ������:\n";
    printArray(arr, n);

    int product = productBetweenLastMinMax(arr, n);
    std::cout << "\n1. ������������ ��������� ����� ��������� ����������� � ��������� ������������: "
        << product << std::endl;

    sortArray(arr, n);
    std::cout << "\n2. ������ ����� ���������� �� �����������:\n";
    printArray(arr, n);

    int originalSize = n;
    int removedCount = removeForStrictlyIncreasing(arr, n);
    int newSize = n - removedCount;

    std::cout << "\n3. ��������� �������� " << removedCount << " ���������:\n";
    std::cout << "������ ������������ ������ (" << newSize << " ���������):\n";
    for (int i = 0; i < newSize; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}