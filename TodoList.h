//
// Created by Cristiano on 16/10/2024.
//

#ifndef TODOLIST_TODOLIST_H
#define TODOLIST_TODOLIST_H

#include <vector>
#include "Activity.h"

class TodoList{

private:
    vector<Activity> activityList;

public:

    void addActivity (const Activity& activity);

    void deleteActivity(int index);

    void changeActivityStatus(int index, bool done);

    void changeActivityDescription(int index, const string& newDescription);

    void sortByExpirationDate();

    void sortByPriority(bool ascending);

    void sortByState();

    void sortByStateAndPriority(bool ascending= true);

    void sortByStateAndExpirationDate();

    void stampAll();
};

#endif //TODOLIST_TODOLIST_H
