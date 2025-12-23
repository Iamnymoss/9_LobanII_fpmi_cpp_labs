#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include "train.h"
#include "time_utility.h"

void RunPart2() {
    std::vector<Train> trains;
    std::ifstream file("trains.txt");
    if (!file.is_open()) {
        return;
    }

    size_t id;
    size_t type_int;
    size_t h;
    size_t m;
    std::string dest;
    long travel_sec;

    while (file >> id >> type_int >> dest >> h >> m >> travel_sec) {
        TrainType type = static_cast<TrainType>(type_int);
        std::time_t dispatch_time = time_utility::SetTime(h, m);
        std::time_t travelling_time = travel_sec;

        trains.push_back(Train(id, type, dest, dispatch_time, travelling_time));
    }

    file.close();

    if (trains.empty()) {
        return;
    }

    std::sort(trains.begin(), trains.end(),
              [](const Train& a, const Train& b) {
                  return a.GetDispatchTime() < b.GetDispatchTime();
              });

    std::cout << "--- All Trains ---" << std::endl;
    for (std::vector<Train>::const_iterator it = trains.cbegin();
         it != trains.cend(); ++it) {
        it->PrintInfo();
    }

    std::time_t start = time_utility::SetTime(10, 0);
    std::time_t end   = time_utility::SetTime(18, 0);

    std::cout << "\n--- 10:00 - 18:00 ---" << std::endl;
    for (std::vector<Train>::const_iterator it = trains.cbegin();
         it != trains.cend(); ++it) {
        if (it->GetDispatchTime() >= start &&
            it->GetDispatchTime() <= end) {
            it->PrintInfo();
        }
    }

    std::string target = "Moscow";
    std::cout << "\n--- Destination: " << target << " ---" << std::endl;
    for (std::vector<Train>::const_iterator it = trains.cbegin();
         it != trains.cend(); ++it) {
        if (it->GetDestination() == target) {
            it->PrintInfo();
        }
    }

    const Train* fastest = NULL;
    for (std::vector<Train>::const_iterator it = trains.cbegin();
         it != trains.cend(); ++it) {
        if (it->GetDestination() == target) {
            if (fastest == NULL ||
                it->GetTravellingTime() < fastest->GetTravellingTime()) {
                fastest = &(*it);
            }
        }
    }

    if (fastest != NULL) {
        std::cout << "\n--- Fastest to " << target << " ---" << std::endl;
        fastest->PrintInfo();
    }
}

int main() {
    try {
        RunPart2();
    } catch (...) {
        return 1;
    }
    return 0;
}
