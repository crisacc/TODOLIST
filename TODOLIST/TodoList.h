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
    bool modified=false;
    const int saveThreshold=5;
    int changeCounter;
public:
    int getChangeCounter() const;

    void setChangeCounter(int changeCounter);

public:

    const std::vector<Activity>& getActivityList() const {
        return activityList;
    }

    ~TodoList() { // alla chiusura salva le modifiche
        saveChanges();
    }

    void addActivity (const Activity& activity);

    void deleteActivity(int index);

    void changeActivityStatus(int index, bool done);

    void changeActivityDescription(int index, const string& newDescription);

    void markAsModified();

    void saveChanges();

    void sortByExpirationDate();

    void sortByPriority(bool ascending);

    void sortByState();

    void sortByStateAndPriority(bool ascending= true);

    void sortByStateAndExpirationDate();

    vector<pair<int, Activity*>> searchByDescription (const string& keyword);

    void stampVector(const vector<pair<int , Activity*>> &results)const;

    void manageSearchResults(const string& keyword);

    void stampAll();

    bool readFromFile(const std::string& filename);

    bool writeToFile(const std::string& filename) const;
};

#endif //TODOLIST_TODOLIST_H
