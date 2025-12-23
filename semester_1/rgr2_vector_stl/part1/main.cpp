#include <iostream>
#include <vector>
#include <algorithm>

int Abs(int value) {
    return (value < 0) ? -value : value;
}

int main() {
    std::vector<int> numbers;
    int input_val;

    std::cout << "Enter numbers (Ctrl+D): ";
    while (std::cin >> input_val) {
        numbers.push_back(input_val);
    }
    
    std::cin.clear();

    if (numbers.empty()) return 0;

    long long sum = 0;
    for (int n : numbers) sum += n;
    std::cout << "\nSum: " << sum << "\nCount: " << numbers.size() << std::endl;

    int target = 5;
    int count_target = 0;
    for (int n : numbers) if (n == target) count_target++;
    std::cout << "Equals " << target << ": " << count_target << std::endl;

    int limit = 10;
    int count_greater = 0;
    for (int n : numbers) if (n > limit) count_greater++;
    std::cout << "Greater than " << limit << ": " << count_greater << std::endl;

    int average = static_cast<int>(sum / static_cast<long long>(numbers.size()));
    for (int& n : numbers) if (n == 0) n = average;

    if (numbers.size() >= 3) {
        int interval_sum = 0;
        for (size_t i = 0; i < 3; ++i) interval_sum += numbers[i];
        for (int& n : numbers) n += interval_sum;
    }

    int min_val = numbers[0];
    int max_val = numbers[0];
    for (int n : numbers) {
        if (n < min_val) min_val = n;
        if (n > max_val) max_val = n;
    }
    int diff = max_val - min_val;
    for (int& n : numbers) {
        if (Abs(n) % 2 == 0) n = diff;
    }

    std::vector<int> result;
    std::vector<int> seen_abs;
    for (int n : numbers) {
        int abs_val = Abs(n);
        bool found = false;
        for (int seen : seen_abs) {
            if (seen == abs_val) {
                found = true;
                break;
            }
        }
        if (!found) {
            seen_abs.push_back(abs_val);
            result.push_back(n);
        }
    }
    numbers = result;

    std::cout << "Result: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << std::endl;

    return 0;
}