#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "vvedi chislo: ";

    while (!(cin >> n)) {
        cout << "Eto ne chislo! Vvedite chislo: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    int summa = 0;
    int proizv = 1;

    for (int i = 1; i <= n; i++)
    {
        if (i % 2 == 0)
            summa += i;
        else
            proizv = proizv * i;
    }

    cout << "summa chetnyh: " << summa << endl;
    cout << "proizvedenie nechetnyh: " << proizv << endl;

    return 0;
}
