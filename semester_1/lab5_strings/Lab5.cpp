#include <iostream>
#include <string>
#include <vector>

bool isDigitChar(char c) {
    return c >= '0' && c <= '9';
}

bool isDelimiter(char c) {
    return c == ' ' || c == '\t' || c == '\n' ||
        c == ',' || c == '.' || c == ';' ||
        c == ':' || c == '!' || c == '?' ||
        c == '-' || c == '(' || c == ')' ||
        c == '"' || c == '\'';
}
int main() {
    setlocale(LC_ALL, "RU");
    std::string s;
    std::getline(std::cin, s);
    int n = static_cast<int>(s.size());
    std::vector<int> starts;
    std::vector<int> lens;

    int i = 0;
    while (i < n) {
        if (isDelimiter(s[i])) {
            ++i;
            continue;
        }

        int start = i;
        while (i < n && !isDelimiter(s[i])) {
            ++i;
        }
        int len = i - start;

        bool allDigits = true;
        for (int j = 0; j < len; ++j) {
            if (!isDigitChar(s[start + j])) {
                allDigits = false;
                break;
            }
        }

        if (allDigits) {
            starts.push_back(start);
            lens.push_back(len);
        }
    }

    if (starts.empty()) {
        std::cout << "Невозможно выполнить преобразование: нет слов-чисел\n";
        return 0;
    }

    
    int maxLen = lens[0], minLen = lens[0];
    int maxIdx = 0, minIdx = 0;

    for (int k = 1; k < (int)lens.size(); ++k) {
        int len = lens[k];
        if (len > maxLen) {
            maxLen = len;
            maxIdx = k;           
        }
        if (len < minLen) {
            minLen = len;
            minIdx = k;           
        }
        else if (len == minLen) {
            minIdx = k;           
        }
    }

    int maxPos = starts[maxIdx];
    int minPos = starts[minIdx];

    if (maxPos == minPos && maxLen == minLen) {
        std::cout << s << '\n';
        return 0;
    }

    int firstPos, firstLen, secondPos, secondLen;
    if (maxPos < minPos) {
        firstPos = maxPos;   firstLen = maxLen;
        secondPos = minPos;  secondLen = minLen;
    }
    else {
        firstPos = minPos;   firstLen = minLen;
        secondPos = maxPos;  secondLen = maxLen;
    }

    std::string firstWord = s.substr(firstPos, firstLen);
    std::string secondWord = s.substr(secondPos, secondLen);

    std::string result;
    result.reserve(n);

    result += s.substr(0, firstPos);
    result += secondWord;
    result += s.substr(firstPos + firstLen, secondPos - (firstPos + firstLen));
    result += firstWord;
    result += s.substr(secondPos + secondLen);

    std::cout << result << '\n';
    return 0;
}
