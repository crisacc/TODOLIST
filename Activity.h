//
// Created by Cristiano on 16/10/2024.
//

#ifndef TODOLIST_ACTIVITY_H
#define TODOLIST_ACTIVITY_H

#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
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

    explicit Activity(const string &desc= "", bool status= false, Priority prior = Priority::Unknown) :
                description(desc), done(status), priority(prior), gotExpirationDate(false){}

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
};

#endif //TODOLIST_ACTIVITY_H
