#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    if (n < 1000 || n > 9999) {
        cout << "ne 4 znaka" << endl;
        return 1;
    }

    int a = n / 1000;
    int b = n / 100 % 10;
    int c = n / 10 % 10;
    int d = n % 10;

    if (a == d && b == c) {
        cout << "da palindrom" << endl;
    }
    else {
        cout << "net ne palindrom" << endl;
    }

    return 0;
}
