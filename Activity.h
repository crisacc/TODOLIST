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
#include "Date.h"
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
    Date expirationDate;
    bool gotExpirationDate;

public:

    explicit Activity(const string &desc= "", Priority prior = Priority::Unknown) :
                description(desc), priority(prior), gotExpirationDate(false), done(false){}

    explicit Activity(const std::string& desc , Priority prior , Date date)
            : description(desc), priority(prior), done(false) , expirationDate(date) , gotExpirationDate(true){};

    const string &getDescription() const;

    void setDescription(const string &description);

    bool isDone() const;

    void setDone(bool status);

    Priority getPriority() const;

    void setPriority(Priority priority);

    void setExpirationDate(Date date);

    Date getExpirationDate() const;

    bool hasExpirationDate() const;

    void deleteExpirationDate();

    string priorityToString() const;

    void stampActivity()const;

    json toJson() const;

    bool fromJson(const json &j);
};


#endif //TODOLIST_ACTIVITY_H
