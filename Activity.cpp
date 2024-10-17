//
// Created by Cristiano on 16/10/2024.
//

#include "Activity.h"
#include <string>
#include <iostream>

using namespace std;

const string &Activity::getDescription() const {
    return description;
}

void Activity::setDescription(const string &description) {
    Activity::description = description;
}

bool Activity::isDone() const {
    return done;
}

void Activity::setDone(bool status) {
    Activity::done = status;
}

Priority Activity::getPriority() const {
    return priority;
}

void Activity::setPriority(Priority priority) {
    Activity::priority = priority;
}

bool Activity::setExpirationDate(const string &stringDate, const string &format) {
    std::tm tm = {};
    std::istringstream ss(stringDate);
    ss >> std::get_time(&tm, format.c_str());
    if (ss.fail()) {
        std::cerr << "Unvalid date format. Use 'dd/mm/yyyy'" << std::endl;
        return false;
    }
    auto timeT = std::mktime(&tm);
    if (timeT == -1) {
        std::cerr << "\n"
                     "Error converting the date." << std::endl;
        return false;
    }
    expirationDate = std::chrono::system_clock::from_time_t(timeT);
    gotExpirationDate = true;
    return true;
}

std::chrono::system_clock::time_point Activity::getExpirationDate() const {
    return expirationDate;
}

bool Activity::hasExpirationDate() const {
    return gotExpirationDate;
}

void Activity::deleteExpirationDate() {
    gotExpirationDate= false;
}

std::string Activity::expirationDateToString() const {
    if (!gotExpirationDate) {
        return "Nessuna scadenza";
    }
    std::time_t time = std::chrono::system_clock::to_time_t(expirationDate);
    std::tm* tm_ptr = std::localtime(&time);
    std::ostringstream oss;
    oss << std::put_time(tm_ptr, "%Y-%m-%d");
    return oss.str();
}

string Activity::priorityToString() const {
    switch (priority) {
        case Priority::Low: return "Low";
        case Priority::Medium: return "Medium";
        case Priority::High: return "High";
        case Priority::Unknown: return "Unknown";
    }
}

void Activity::stampActivity()const{

    std::cout << "Activity: " << description;
    std::cout << " - Done: " << (done ? "Yes" : "No");
    std::cout << " - Priority: " << priorityToString();
    std::cout << " - Expiration Date: " << expirationDateToString()
              << std::endl;
}




