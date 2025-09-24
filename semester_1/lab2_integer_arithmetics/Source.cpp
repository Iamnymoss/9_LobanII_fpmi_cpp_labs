#include <iostream>
using namespace std;

int main()
{
    unsigned long long n;
    cout << "Vvod chisla: ";
    cin >> n;

    if (n == 0) {
        cout << "Minimalnaya cifra: 0" << endl;
        cout << "Resultat: 0";
        return 0;
    }

    unsigned long long temp = n;
    int min_cifra = 9;
    while (temp > 0) {
        int cifra = temp % 10;
        if (cifra < min_cifra) {
            min_cifra = cifra;
        }
        temp /= 10;
    }

    cout << "Minimalnaya cifra: " << min_cifra << endl;

    temp = n;
    unsigned long long result = 0;
    unsigned long long mnozhitel = 1;
    int count_min = 0;
    int total_cifr = 0;

    while (temp > 0) {
        int cifra = temp % 10;
        if (cifra == min_cifra) count_min++;
        total_cifr++;
        temp /= 10;
    }

    if (count_min == total_cifr) {
        result = n;
    }
    else {
        temp = n;
        while (temp > 0) {
            int cifra = temp % 10;
            if (cifra != min_cifra) {
                result += cifra * mnozhitel;
                mnozhitel *= 10;
            }
            temp /= 10;
        }
    }

    cout << "Resultat: " << result;

    return 0;
}