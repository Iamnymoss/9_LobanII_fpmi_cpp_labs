#include <iostream>
#include <string>
using namespace std;

int main()
{
    int n;
    cin >> n;

    if (n < 0) {
        cout << "ne naturalnoe" << endl;
        return 0;
    }

    string dvoichka = "";
    int x = n;

    do {
        dvoichka = to_string(x % 2) + dvoichka;
        x = x / 2;
    } while (x > 0);

    string shestnadcat = "";
    x = n;

    do {
        int ostatok = x % 16;
        char bukva;
        if (ostatok == 10) bukva = 'A';
        else if (ostatok == 11) bukva = 'B';
        else if (ostatok == 12) bukva = 'C';
        else if (ostatok == 13) bukva = 'D';
        else if (ostatok == 14) bukva = 'E';
        else if (ostatok == 15) bukva = 'F';
        else bukva = '0' + ostatok;

        shestnadcat = bukva + shestnadcat;
        x = x / 16;
    } while (x > 0);

    cout << dvoichka << endl;
    cout << shestnadcat << endl;

    return 0;
}
