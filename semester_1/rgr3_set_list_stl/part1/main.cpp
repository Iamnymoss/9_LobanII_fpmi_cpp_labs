#include <iostream>
#include <set>

bool IsPrime(int n) {
    if (n < 2) {
        return false;
    }
    for (int d = 2; d * d <= n; ++d) {
        if (n % d == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int N;

    std::cout << "Enter N (N >= 2): ";
    if (!(std::cin >> N)) {
        std::cerr << "Input error\n";
        return 1;
    }

    if (N < 2) {
        std::cout << "There are no prime numbers <= " << N << "\n";
        return 0;
    }

    std::set<int> numbers;
    for (int i = 2; i <= N; ++i) {
        numbers.insert(i);
    }

    for (int p = 2; p * p <= N; ++p) {
        if (!IsPrime(p)) {
            continue;
        }

        int multiple = 2 * p;
        while (multiple <= N) {
            numbers.erase(multiple);
            multiple += p;
        }
    }

    std::cout << "Prime numbers <= " << N << ":\n";
    for (std::set<int>::const_iterator it = numbers.begin();
         it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    return 0;
}
