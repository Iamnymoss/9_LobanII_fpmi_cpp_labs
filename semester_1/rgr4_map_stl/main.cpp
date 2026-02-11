#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

struct Mark {
    std::string subject_;
    size_t mark_;
};

struct StudentData {
    std::string name_;
    size_t number_;
    std::vector<Mark> marks_;
};

double AverageMark(const StudentData& s) {
    if (s.marks_.empty()) {
        return 0.0;
    }
    size_t sum = 0;
    for (size_t i = 0; i < s.marks_.size(); ++i) {
        sum += s.marks_[i].mark_;
    }
    return static_cast<double>(sum) / static_cast<double>(s.marks_.size());
}

size_t SumMarks(const StudentData& s) {
    size_t sum = 0;
    for (size_t i = 0; i < s.marks_.size(); ++i) {
        sum += s.marks_[i].mark_;
    }
    return sum;
}

void LoadFromFile(const std::string& filename,
    std::map<size_t, StudentData>& students) {
    std::ifstream in(filename.c_str());
    if (!in.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << "\n";
        return;
    }

    students.clear();

    while (true) {
        StudentData s;
        size_t marks_count;

        if (!(in >> s.number_)) {
            break;
        }
        in.ignore(1);

        std::getline(in, s.name_);

        if (!(in >> marks_count)) {
            break;
        }

        s.marks_.clear();
        for (size_t i = 0; i < marks_count; ++i) {
            Mark m;
            if (!(in >> m.subject_ >> m.mark_)) {
                break;
            }
            s.marks_.push_back(m);
        }

        students[s.number_] = s;
    }
}

void PrintByNumber(const std::map<size_t, StudentData>& students) {
    std::cout << "Студенты по номеру зачётки:\n";
    for (std::map<size_t, StudentData>::const_iterator it = students.begin();
        it != students.end(); ++it) {
        const StudentData& s = it->second;
        std::cout << "Номер зачётки: " << s.number_
            << ", ФИО: " << s.name_
            << ", средний балл: " << AverageMark(s) << "\n";
    }
}

struct StudentView {
    size_t index_;
    std::string name_;
    size_t number_;
    double average_;
};

void BuildStudentViews(const std::map<size_t, StudentData>& students,
    std::vector<StudentView>& views) {
    views.clear();
    size_t idx = 1;
    for (std::map<size_t, StudentData>::const_iterator it = students.begin();
        it != students.end(); ++it) {
        const StudentData& s = it->second;
        StudentView v;
        v.index_ = idx;
        v.name_ = s.name_;
        v.number_ = s.number_;
        v.average_ = AverageMark(s);
        views.push_back(v);
        ++idx;
    }
}

bool CompareByNameAndAverage(const StudentView& a,
    const StudentView& b) {
    if (a.name_ < b.name_) return true;
    if (a.name_ > b.name_) return false;
    return a.average_ > b.average_;
}

void PrintStudentsAlphabetically(const std::map<size_t, StudentData>& students) {
    std::vector<StudentView> views;
    BuildStudentViews(students, views);

    std::sort(views.begin(), views.end(), CompareByNameAndAverage);

    std::cout << "Студенты (№, ФИО, зачётка, средний балл) по алфавиту:\n";
    for (size_t i = 0; i < views.size(); ++i) {
        const StudentView& v = views[i];
        std::cout << v.index_ << ". " << v.name_
            << ", зачётка: " << v.number_
            << ", средний балл: " << v.average_ << "\n";
    }
}

bool InRange(double value, double left, double right) {
    return value >= left && value <= right;
}

bool CompareByAverageDesc(const StudentView& a,
    const StudentView& b) {
    if (a.average_ > b.average_) return true;
    if (a.average_ < b.average_) return false;
    return a.name_ < b.name_;
}

void PrintStudentsInRange(const std::map<size_t, StudentData>& students,
    double left, double right) {
    std::vector<StudentView> views;
    BuildStudentViews(students, views);

    std::vector<StudentView> filtered;
    for (size_t i = 0; i < views.size(); ++i) {
        if (InRange(views[i].average_, left, right)) {
            filtered.push_back(views[i]);
        }
    }

    std::sort(filtered.begin(), filtered.end(), CompareByAverageDesc);

    std::cout << "Студенты со средним баллом в диапазоне ["
        << left << "; " << right << "]:\n";
    for (size_t i = 0; i < filtered.size(); ++i) {
        const StudentView& v = filtered[i];
        std::cout << v.name_
            << ", зачётка: " << v.number_
            << ", средний балл: " << v.average_ << "\n";
    }
}

void PrintStudentsBySubject(const std::map<size_t, StudentData>& students,
    const std::string& subject) {
    std::cout << "Студенты, сдававшие предмет \"" << subject << "\":\n";
    for (std::map<size_t, StudentData>::const_iterator it = students.begin();
        it != students.end(); ++it) {
        const StudentData& s = it->second;
        bool has = false;
        for (size_t i = 0; i < s.marks_.size(); ++i) {
            if (s.marks_[i].subject_ == subject) {
                has = true;
                break;
            }
        }
        if (has) {
            std::cout << s.name_ << ", зачётка: " << s.number_ << "\n";
        }
    }
}

void CountStudentsPerSubject(const std::map<size_t, StudentData>& students) {
    std::map<std::string, size_t> counts;

    for (std::map<size_t, StudentData>::const_iterator it = students.begin();
        it != students.end(); ++it) {
        const StudentData& s = it->second;
        for (size_t i = 0; i < s.marks_.size(); ++i) {
            const std::string& subj = s.marks_[i].subject_;
            counts[subj] += 1;
        }
    }

    std::cout << "Количество студентов по каждому предмету:\n";
    for (std::map<std::string, size_t>::const_iterator it = counts.begin();
        it != counts.end(); ++it) {
        std::cout << it->first << ": " << it->second << "\n";
    }
}

struct SubjectStat {
    std::string subject_;
    double average_;
};

bool CompareSubjectStat(const SubjectStat& a, const SubjectStat& b) {
    if (a.average_ > b.average_) return true;
    if (a.average_ < b.average_) return false;
    return a.subject_ < b.subject_;
}

void AveragePerSubject(const std::map<size_t, StudentData>& students) {
    std::map<std::string, std::pair<size_t, size_t> > acc;

    for (std::map<size_t, StudentData>::const_iterator it = students.begin();
        it != students.end(); ++it) {
        const StudentData& s = it->second;
        for (size_t i = 0; i < s.marks_.size(); ++i) {
            const std::string& subj = s.marks_[i].subject_;
            size_t mark = s.marks_[i].mark_;
            std::pair<size_t, size_t>& p = acc[subj];
            p.first += mark;
            p.second += 1;
        }
    }

    std::vector<SubjectStat> stats;
    for (std::map<std::string, std::pair<size_t, size_t> >::const_iterator it = acc.begin();
        it != acc.end(); ++it) {
        SubjectStat st;
        st.subject_ = it->first;
        st.average_ = 0.0;
        if (it->second.second != 0) {
            st.average_ = static_cast<double>(it->second.first) /
                static_cast<double>(it->second.second);
        }
        stats.push_back(st);
    }

    std::sort(stats.begin(), stats.end(), CompareSubjectStat);

    std::cout << "Средний балл по предметам (по убыванию):\n";
    for (size_t i = 0; i < stats.size(); ++i) {
        std::cout << stats[i].subject_ << ": " << stats[i].average_ << "\n";
    }
}

void StudentsWithMaxTotal(const std::map<size_t, StudentData>& students) {
    size_t max_sum = 0;
    for (std::map<size_t, StudentData>::const_iterator it = students.begin();
        it != students.end(); ++it) {
        size_t sum = SumMarks(it->second);
        if (sum > max_sum) {
            max_sum = sum;
        }
    }

    std::cout << "Студенты с максимальной суммой баллов (" << max_sum << "):\n";
    for (std::map<size_t, StudentData>::const_iterator it = students.begin();
        it != students.end(); ++it) {
        if (SumMarks(it->second) == max_sum) {
            const StudentData& s = it->second;
            std::cout << s.name_ << ", зачётка: " << s.number_ << "\n";
        }
    }
}

bool HasBadMark(const StudentData& s) {
    for (size_t i = 0; i < s.marks_.size(); ++i) {
        size_t m = s.marks_[i].mark_;
        if (m == 1 || m == 2 || m == 3) {
            return true;
        }
    }
    return false;
}

void StudentsWithBadMarks(const std::map<size_t, StudentData>& students) {
    std::cout << "Студенты с неудовлетворительными оценками (1, 2, 3):\n";
    for (std::map<size_t, StudentData>::const_iterator it = students.begin();
        it != students.end(); ++it) {
        if (HasBadMark(it->second)) {
            const StudentData& s = it->second;
            std::cout << s.name_ << ", зачётка: " << s.number_ << "\n";
        }
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    std::map<size_t, StudentData> students;

    LoadFromFile("students.txt", students);

    PrintByNumber(students);
    PrintStudentsAlphabetically(students);
    PrintStudentsInRange(students, 6.0, 8.0);
    PrintStudentsBySubject(students, "Math");
    CountStudentsPerSubject(students);
    AveragePerSubject(students);
    StudentsWithMaxTotal(students);
    StudentsWithBadMarks(students);

    return 0;
}
