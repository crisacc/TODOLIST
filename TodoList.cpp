//
// Created by Cristiano on 16/10/2024.
//

#include "TodoList.h"
#include <iostream>
#include <algorithm>
#include <fstream>
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
             if (a.hasExpirationDate() && b.hasExpirationDate()) {
                 return a.getExpirationDate() < b.getExpirationDate();
             }

             if (a.hasExpirationDate()) return true;
             if (b.hasExpirationDate()) return false;

             return false;
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

bool TodoList::readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Impossibile aprire il file per la lettura." << std::endl;
        return false;
    }

    json j;
    file >> j;
    file.close();

    try {
        activityList.clear();  // Pulisce la lista esistente prima di caricare nuove attività
        for (const auto& item : j) {
            Activity activity;
            if (activity.fromJson(item)) {
                activityList.push_back(activity);
            } else {
                std::cerr << "Errore nel parsing di un'attività dal file." << std::endl;
            }
        }
    } catch (const json::exception& e) {
        std::cerr << "Errore durante il parsing del file JSON: " << e.what() << std::endl;
        return false;
    }
    return true;
}

bool TodoList::writeToFile(const std::string& filename) const {
    // Nome del file temporaneo
    std::string tempFilename = filename + ".tmp";

    // Scrivi nel file temporaneo
    std::ofstream file(tempFilename);
    if (!file.is_open()) {
        std::cerr << "Impossibile aprire il file temporaneo per la scrittura." << std::endl;
        return false;
    }

    // Converte la lista di attività in un array JSON
    json j = json::array();
    for (const auto& activity : activityList) {
        j.push_back(activity.toJson());
    }

    // Scrivi l'oggetto JSON nel file temporaneo
    file << j.dump(4);  // Indentazione di 4 spazi per rendere il JSON leggibile
    file.close();

    // Controlla se il file temporaneo è stato scritto correttamente
    std::ifstream checkTempFile(tempFilename);
    if (!checkTempFile.is_open()) {
        std::cerr << "Errore: il file temporaneo non è stato creato correttamente." << std::endl;
        return false;
    }
    checkTempFile.close();

    // Rimuove il file originale prima di rinominare
    if (std::remove(filename.c_str()) != 0) {
        std::cerr << "Errore durante la rimozione del file originale." << std::endl;
        return false;
    }

    // Se la rimozione è andata a buon fine, rinomina il file temporaneo
    if (std::rename(tempFilename.c_str(), filename.c_str()) != 0) {
        std::cerr << "Errore durante la sostituzione del file originale." << std::endl;
        std::perror("std::rename");
        return false;
    }

    return true;
}

