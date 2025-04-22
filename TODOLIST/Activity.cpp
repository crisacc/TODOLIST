//
// Created by Cristiano on 16/10/2024.
//

#include "Activity.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

const string &Activity::getDescription() const {
    return description;
}

void Activity::setDescription(const string &description) {
    Activity::description = description;
}

bool Activity::isDone() const {
    return done;
}

void Activity::setDone(bool status) {
    Activity::done = status;
}

Priority Activity::getPriority() const {
    return priority;
}

void Activity::setPriority(Priority priority) {
    Activity::priority = priority;
}

void Activity::setExpirationDate(Date date) {
    expirationDate = date;
    gotExpirationDate = true;
}

Date Activity::getExpirationDate() const {
    return expirationDate;
}

bool Activity::hasExpirationDate() const {
    return gotExpirationDate;
}

void Activity::deleteExpirationDate() {
    gotExpirationDate= false;
}

string Activity::priorityToString() const {
    switch (priority) {
        case Priority::Low: return "Low";
        case Priority::Medium: return "Medium";
        case Priority::High: return "High";
        case Priority::Unknown: return "Unknown";
    }
}

void Activity::stampActivity()const{

    std::cout << "Activity: " << description;
    std::cout << " - Done: " << (done ? "Yes" : "No");
    std::cout << " - Priority: " << priorityToString();
    std::cout << " - Expiration Date: " << expirationDate.toString()
              << std::endl;
}

json Activity::toJson() const {
    json j;
    j["description"] = description;
    j["done"] = done;
    j["priority"] = priorityToString();
    if (gotExpirationDate) {
        j["expirationDate"] = expirationDate.toString();
    } else {
        j["expirationDate"] = nullptr;
    }
    return j;
}

bool Activity::fromJson(const json& j) {
    try {
        if (j.contains("description")) description = j.at("description").get<std::string>();
        if (j.contains("done")) done = j.at("done").get<bool>();
        if (j.contains("priority")) {
            std::string prio = j.at("priority").get<std::string>();
            if (prio == "High") priority = Priority::High;
            else if (prio == "Medium") priority = Priority::Medium;
            else if (prio == "Low") priority = Priority::Low;
            else priority = Priority::Unknown;
        }
        if (j.contains("expirationDate") && !j.at("expirationDate").is_null()) {
            std::string dateStr = j.at("expirationDate").get<std::string>();
            Date date;
            if (date.setDateFromString(dateStr)) {
                expirationDate = date;
                gotExpirationDate = true;
            } else {
                std::cerr << "Data non valida nel JSON: " << dateStr << std::endl;
                gotExpirationDate = false;
            }
        } else {
            gotExpirationDate = false;
        }

        return true;
    } catch (json::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        return false;
    }
}

/*
void saveActivityToFile(const Activity& activity, const std::string& filename) {
    // Converte l'oggetto Activity in JSON
    json j = activity.toJson();

    // Salva l'oggetto JSON in un file
    std::ofstream file(filename);
    if (file.is_open()) {
        file << j.dump(4);  // Scrive il JSON con un'indentazione di 4 spazi per leggibilità
        file.close();
    } else {
        std::cerr << "Impossibile aprire il file per la scrittura." << std::endl;
    }
}


Activity loadActivityFromFile(const std::string& filename) {
    Activity activity;
    std::ifstream file(filename);

    if (file.is_open()) {
        json j;
        file >> j;  // Carica il contenuto del file in un oggetto JSON
        file.close();

        // Converte il JSON in un oggetto Activity
        if (!activity.fromJson(j)) {
            std::cerr << "Errore nel caricamento dell'attività da JSON." << std::endl;
        }
    } else {
        std::cerr << "Impossibile aprire il file per la lettura." << std::endl;
    }

    return activity;
}
*/