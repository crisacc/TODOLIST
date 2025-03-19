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

vector<pair<int,Activity*>> TodoList::searchByDescription(const std::string &keyword) {
    vector<pair<int,Activity*>> results;
    for (int i = 0; i < activityList.size(); i++) {
        if (activityList[i].getDescription().find(keyword) != string::npos) {
            results.emplace_back(i, &activityList[i]);
        }
    }
    return results;
}

void TodoList::stampVector(const vector<pair<int , Activity*>> &results) const {
    if (results.empty()){
        cout << "Nessuna attività trovata.\n";
        return;
    }
    cout << "Attività trovate :\n";
    for (const auto& [index, activity] : results){
        cout << index << ". ";
        activity->stampActivity();
    }
}

void TodoList::manageSearchResults(const string& keyword) {
    vector<pair<int, Activity*>> results = searchByDescription(keyword);
    stampVector(results);

    if (results.empty()) return;

    cout << "Inserisci l'indice originale dell'attività da gestire (negativo per uscire): ";
    int index;
    cin >> index;

    if (index < 0 || index >= activityList.size()) {
        cout << "Indice non valido.\n";
        return;
    }

    cout << "Cosa vuoi fare? (1 = Modifica descrizione, 2 = Cambia stato, 3 = Cancella): ";
    int action;
    cin >> action;

    if (action == 1) {
        cout << "Nuova descrizione: ";
        string newDesc;
        cin.ignore();
        getline(cin, newDesc);
        activityList[index].setDescription(newDesc);
    }
    else if (action == 2) {
        activityList[index].setDone(!activityList[index].isDone());
        cout << "Stato aggiornato.\n";
    }
    else if (action == 3) {
        activityList.erase(activityList.begin() + index);
        cout << "Attività eliminata.\n";
    }
    else {
        cout << "Azione non valida.\n";
    }
}

void TodoList::stampAll() {

    if (activityList.empty()) {
        cout << "La lista delle attività è vuota." << endl;
        return;
    }

    cout << "Elenco delle attività:\n";
    for (int i = 0; i < activityList.size(); ++i) {
        cout << "-----------------------------\n";
        cout << i+1 << ".";
        activityList[i].stampActivity();
    }
    cout << "-----------------------------\n";

}

bool TodoList::readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "File non trovato. Creazione di un nuovo file vuoto: "<< std::endl;
        std::ofstream newFile(filename);
        if (!newFile.is_open()){
            std::cerr << "Errore nella creazione del file." << std::endl;
            return false;
        }
        return true;
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
    // Nome del file di backup
    std::string backupFilename = filename + ".bak";

    if (std::rename(filename.c_str(), backupFilename.c_str()) != 0  &&  errno != ENOENT){
        std::cerr<< "Errore nel creare il backup del file originale." << std::endl;
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
        return false;
    }

    return true;
}

