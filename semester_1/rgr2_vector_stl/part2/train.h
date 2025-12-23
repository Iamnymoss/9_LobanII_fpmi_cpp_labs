#pragma once

#include <string>
#include <iostream>
#include "time_utility.h"

using TrainId = size_t;
using namespace time_utility;

enum class TrainType { 
    PASSENGER, FREIGHT, HIGH_SPEED, SUBWAY, SPECIALIZED
};

class Train {
private:
    TrainId id_;
    TrainType type_;
    std::string destination_;
    std::time_t dispatch_time_;
    std::time_t travelling_time_;

public:
    Train(TrainId id, TrainType type, std::string dest, std::time_t disp, std::time_t trav)
        : id_(id), type_(type), destination_(dest), dispatch_time_(disp), travelling_time_(trav) {}

    TrainId GetId() const { return id_; }
    TrainType GetType() const { return type_; }
    std::string GetDestination() const { return destination_; }
    std::time_t GetDispatchTime() const { return dispatch_time_; }
    std::time_t GetTravellingTime() const { return travelling_time_; }

    void PrintInfo() const {
        std::cout << "ID: " << id_ << " | Dest: " << destination_ << " | Time: ";
        PrintTime(dispatch_time_);
    }
};