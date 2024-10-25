//
// Created by Cristiano on 16/10/2024.
//

#ifndef TODOLIST_ACTIVITY_H
#define TODOLIST_ACTIVITY_H

#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

enum class Priority {
    High,
    Medium,
    Low,
    Unknown
};

class Activity{

private:
    string description;
    bool done;
    Priority priority;
    std::chrono::system_clock::time_point expirationDate;
    bool gotExpirationDate;

public:

    explicit Activity(const string &desc= "", Priority prior = Priority::Unknown) :
                description(desc), priority(prior), gotExpirationDate(false), done(false){}

    explicit Activity(const std::string& desc , Priority prior , const std::string& date)
            : description(desc), priority(prior), done(false) {
        if (!date.empty()) {
            if (setExpirationDate(date))
                gotExpirationDate = true;
            else
                gotExpirationDate = false;
        } else {
            gotExpirationDate = false;
        }
    };

    const string &getDescription() const;

    void setDescription(const string &description);

    bool isDone() const;

    void setDone(bool status);

    Priority getPriority() const;

    void setPriority(Priority priority);

    bool setExpirationDate(const std::string& stringDate, const std::string& format = "%d/%m/%Y");

    std::chrono::system_clock::time_point getExpirationDate() const;

    bool hasExpirationDate() const;

    void deleteExpirationDate();

    std::string expirationDateToString() const;

    string priorityToString() const;

    void stampActivity()const;

    json toJson() const;

    bool fromJson(const json &j);
};


void saveActivityToFile(const Activity& activity, const std::string& filename);

Activity loadActivityFromFile(const std::string& filename);


#endif //TODOLIST_ACTIVITY_H
