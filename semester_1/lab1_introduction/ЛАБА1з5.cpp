#include <iostream>
using namespace std;

int main() {
	int a, b;
	cin >> a;
	cin >> b;
	int x;
	if (a > b)x = b; else x = a;
	for (int i = 1; i <= x; i++) {
		if (a % i == 0)if (b % i == 0)cout << i << " ";
	}

	return 0;
}
