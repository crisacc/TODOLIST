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
    const int saveThreshold=5;
    int changeCounter=0;
    void markAsModified();
    void saveChanges();

public:

    int getChangeCounter() const;

    const std::vector<Activity>& getActivityList() const{
        return activityList;
    }

    std::vector<Activity>& getActivityList()  {  //per la modifica
        return activityList;
    }


    ~TodoList() { // alla chiusura salva le modifiche
        saveChanges();
    }

    void addActivity (const Activity& activity);

    void deleteActivity(int index);//todo: gfare controllo outofrange

    void changeActivityStatus(int index, bool done); //todo: usare overloading per una sola

    void changeActivityDescription(int index, const string& newDescription);

    void sortByExpirationDate();

    void sortByPriority(bool ascending);

    void sortByState();

    void sortByStateAndPriority(bool ascending= true);

    void sortByStateAndExpirationDate();

    const vector<pair<int, Activity*>> searchByDescription (const string& keyword);

    bool readFromFile(const std::string& filename);

    bool writeToFile(const std::string& filename) const;
};

#endif //TODOLIST_TODOLIST_H
