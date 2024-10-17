//
// Created by Cristiano on 16/10/2024.
//

#include "TodoList.h"
#include <iostream>
#include <algorithm>
using namespace std;

void TodoList::addActivity(const Activity &activity) {
    activityList.push_back(activity);
}

void TodoList::deleteActivity(int index) {

    if(index>=0 && index<activityList.size())
        activityList.erase(activityList.begin() + index);

    else
        cerr << "Invalid index!" << endl;
}

void TodoList::changeActivityStatus(int index, bool done) {

    if( index>=0 && index<activityList.size() )
        activityList[index].setDone(done);

    else
        cerr << "Invalid index!" << endl;
}

void TodoList::changeActivityDescription(int index, const string &newDescription) {

    if( index>=0 && index<activityList.size() )
        activityList[index].setDescription(newDescription);

    else
        cerr << "Invalid index!" << endl;
}

void TodoList::sortByExpirationDate() {
    sort(activityList.begin(), activityList.end(),
         [](const Activity&a, const Activity& b){   //a si trova prima di b?
                    if (!a.hasExpirationDate()  && !b.hasExpirationDate()) return false;
                    if (!a.hasExpirationDate()) return false;
                    if (!b.hasExpirationDate()) return true;
                    return a.getExpirationDate() < b.getExpirationDate();
    }
    );
}

void TodoList::sortByPriority(bool ascending ) {
    sort(activityList.begin(), activityList.end(),
         [ascending] (const Activity& a, const Activity& b ){
             return ascending ? a.getPriority() < b.getPriority() : a.getPriority() > b.getPriority();
         }
    );
}

void TodoList::sortByState() {
    sort(activityList.begin(), activityList.end(),
         [] (const Activity &a, const Activity& b){
            return a.isDone() < b.isDone();
         }
    );
}

void TodoList::sortByStateAndPriority(bool ascending) {
    sort(activityList.begin(), activityList.end(),
         [ascending] (const Activity &a, const Activity& b){
          if (a.isDone() != b.isDone())
              return a.isDone() < b.isDone();
          return ascending ? a.getPriority() < b.getPriority() : a.getPriority() > b.getPriority();
         }
    );
}



void TodoList::sortByStateAndExpirationDate() {
    sort(activityList.begin(), activityList.end(),
        [] (const Activity &a, const Activity& b) {
            if(a.isDone() != b.isDone())
                return a.isDone() < b.isDone();
            if (!a.hasExpirationDate()  && !b.hasExpirationDate()) return false;
            if (!a.hasExpirationDate()) return false;
            if (!b.hasExpirationDate()) return true;
            return a.getExpirationDate() < b.getExpirationDate();
        }
    );
}

void TodoList::stampAll() {

    for (int i = 0; i < activityList.size(); ++i) {
        cout << i+1 << ".";
        activityList[i].stampActivity();
    }

}
