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
    markAsModified();
}

void TodoList::deleteActivity(int index) {

    if(index>=0 && index<activityList.size()) {
        activityList.erase(activityList.begin() + index);
        markAsModified();
    }
    else
        cerr << "Invalid index!" << endl;
}

void TodoList::changeActivityStatus(int index, bool done) {

    if( index>=0 && index<activityList.size() ) {
        activityList[index].setDone(done);
        markAsModified();
    }

    else
        cerr << "Invalid index!" << endl;
}

void TodoList::changeActivityDescription(int index, const string &newDescription) {

    if( index>=0 && index<activityList.size() ){
        activityList[index].setDescription(newDescription);
        markAsModified();
    }

    else
        cerr << "Invalid index!" << endl;
}

void TodoList::markAsModified() {
    changeCounter++;

    if (changeCounter >= saveThreshold) {
        saveChanges();
    }
}

void TodoList::saveChanges() {
    writeToFile("todo_list.json");
    changeCounter = 0;
    cout << "Salvataggio automatico completato!" << endl;
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
    std::sort(activityList.begin(), activityList.end(),
              [ascending](const Activity &a, const Activity &b) {
                  if (a.isDone() != b.isDone()) {
                      return !a.isDone();  // Le attività non fatte vengono prima
                  }
                  return ascending ? (a.getPriority() > b.getPriority())
                                   : (a.getPriority() < b.getPriority());
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

const vector<pair<int,Activity*>> TodoList::searchByDescription(const std::string &keyword) {
    vector<pair<int,Activity*>> results;
    for (int i = 0; i < activityList.size(); i++) {
        if (activityList[i].getDescription().find(keyword) != string::npos) {
            results.emplace_back(i, &activityList[i]);
        }
    }
    return results;
}

bool TodoList::readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "File non trovato. Verrà creato un nuovo file al salvataggio." << std::endl;
        std::ofstream newFile(filename);
        if (!newFile.is_open()){
            std::cerr << "Errore nella creazione del file." << std::endl;
            return false;
        }
        return true;
    }

    // Controlla se il file è vuoto
    if (file.peek() == std::ifstream::traits_type::eof()) {
        // File vuoto: imposta la lista come vuota
        activityList.clear();
        return true;
    }

    json j;
    try {
        file >> j;
    } catch (json::parse_error& e) {
        std::cerr << "Errore nel parsing del file JSON: " << e.what() << std::endl;
        return false;
    }
    file.close();

    try {
        activityList.clear();
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
    // Nome del file di backup
    std::string backupFilename = filename + ".bak";

    if (std::ifstream(filename)){ // crea il backu solo se ul file originale esiste
        if (std::rename(filename.c_str(), backupFilename.c_str()) != 0  &&  errno != ENOENT){
            std::cerr<< "Errore nel creare il backup del file originale." << std::endl;
            return false; // se fallisce meglio non procedere
        }
    }

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

    //  rinomina il file temporaneo
    if (std::rename(tempFilename.c_str(), filename.c_str()) != 0) {
        std::cerr << "Errore durante la sostituzione del file originale." << std::endl;
        std::perror("std::rename");

        // Tenta di ripristinare il backup
        if (std::rename(backupFilename.c_str(), filename.c_str()) != 0) {
            std::cerr << "Errore nel ripristino del backup. Il file potrebbe essere corrotto." << std::endl;
        }

        return false;
    }

    std::remove(backupFilename.c_str()); // tutto è andato bene, rimosso backup

    return true;
}

int TodoList::getChangeCounter() const {
    return changeCounter;
}

int TodoList::getSize() const {
    return activityList.size();
}

const Activity& TodoList::getActivityAt(int index) const {
    if (index < 0 || index >= activityList.size()) {
        throw std::out_of_range("Indice non valido");
    }
    return activityList[index];
}