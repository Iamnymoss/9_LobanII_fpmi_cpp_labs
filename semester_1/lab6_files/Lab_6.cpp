#include <iostream>
#include <fstream>
#include <string>

const int MAX_WORDS = 10000;

void sortChars(std::string& s) {
    int n = s.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            if (s[j] > s[j + 1]) {
                char tmp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = tmp;
            }
        }
    }
}

std::string uniqueChars(const std::string& s) {
    if (s.empty()) return "";
    std::string res;
    res += s[0];
    for (int i = 1; i < (int)s.size(); ++i) {
        if (s[i] != s[i - 1]) {
            res += s[i];
        }
    }
    return res;
}

void sortStrings(std::string arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::string tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

int countUnique(std::string arr[], int n) {
    if (n == 0) return 0;
    int cnt = 1;
    for (int i = 1; i < n; ++i) {
        if (arr[i] != arr[i - 1]) {
            cnt++;
        }
    }
    return cnt;
}

int main() {
    std::setlocale(LC_ALL, "RU");
    std::ifstream fin("input.txt");
    if (!fin) {
        std::cerr << "Не удалось открыть input.txt\n";
        return 1;
    }

    std::string words[MAX_WORDS];
    int n = 0;

    while (n < MAX_WORDS && std::getline(fin, words[n])) {
        if (!words[n].empty())
            n++;
    }

    std::string keys[MAX_WORDS];

    for (int i = 0; i < n; ++i) {
        std::string s = words[i];
        sortChars(s);
        keys[i] = uniqueChars(s);
    }

    sortStrings(keys, n);
    int groups = countUnique(keys, n);

    std::cout << groups << std::endl;
    return 0;
}

