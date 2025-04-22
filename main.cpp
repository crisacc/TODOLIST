#include <iostream>
#include "TODOLIST/TodoList.h"
#include "TODOLIST/Activity.h"
#include "TODOLIST/Date.h"

using namespace std;

void printMenu() {
    cout << "\n=== To-Do List Manager ===\n";
    cout << "1. Aggiungi attività\n";
    cout << "2. Elimina attività\n";
    cout << "3. Modifica stato attività\n";
    cout << "4. Modifica descrizione attività\n";
    cout << "5. Visualizza tutte le attività\n";
    cout << "6. Ordinamento per data di scadenza\n";
    cout << "7. Ordinamento per priorità\n";
    cout << "8. Ordinamento per stato\n";
    cout << "9. Ordinamento per stato e priorità\n";
    cout << "10. Ordinamento per stato e data di scadenza\n";
    cout << "11. Ricerca per descrizione e gestione risultati\n";
    cout << "0. Esci\n";
    cout << "Scelta: ";
}

// Funzione per aggiungere un'attività da CLI
void addActivityCLI(TodoList &list) {
    string description;
    int priorityInput;
    int sceltaData;

    cout << "Inserisci descrizione dell'attività: ";
    getline(cin, description);

    cout << "Inserisci priorità (0: Unknown, 1: Low, 2: Medium, 3: High): ";
    cin >> priorityInput;
    cin.ignore();  // Pulizia del buffer

    cout << "Vuoi impostare una data di scadenza? (1: Si, 0: No): ";
    cin >> sceltaData;
    cin.ignore();

    if (sceltaData == 1) {
        string dateStr;
        cout << "Inserisci data di scadenza (gg/mm/aaaa): ";
        getline(cin, dateStr);
        Date expiration;
        if (expiration.setDateFromString(dateStr, "%d/%m/%Y")) {
        Activity act(description, static_cast<Priority>(priorityInput), expiration);
        list.addActivity(act);
    } else {
        cout << "Data non valida. Creazione dell'attività senza data di scadenza." << endl;
        Activity act(description, static_cast<Priority>(priorityInput));
        list.addActivity(act);
        }
    }

    else {
    Activity act(description, static_cast<Priority>(priorityInput));
    list.addActivity(act);
        }
}

void printVector(const vector<pair<int , Activity*>> &results) {
    if (results.empty()) {
        cout << "Nessuna attività trovata.\n";
        return;
    }
    cout << "Attività trovate :\n";
    for (const auto& [index, activity] : results) {
        cout << index << ". ";
        activity->stampActivity();
    }
}

void manageSearchResults(TodoList& todo, const string& keyword) {
    vector<pair<int, Activity*>> results = todo.searchByDescription(keyword);
    printVector(results);

    if (results.empty()) return;

    cout << "Inserisci l'indice originale dell'attività da gestire (negativo per uscire): ";
    int index;
    cin >> index;

    vector<Activity>& activityList = todo.getActivityList();

    if (index < 0 || index >= static_cast<int>(activityList.size())) {
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

void printAll(const TodoList& todo) {
    const auto& activityList = todo.getActivityList();

    if (activityList.empty()) {
        cout << "La lista delle attività è vuota." << endl;
        return;
    }

    cout << "Elenco delle attività:\n";
    for (int i = 0; i < static_cast<int>(activityList.size()); ++i) {
        cout << "-----------------------------\n";
        cout << i + 1 << ".";
        activityList[i].stampActivity();
    }
    cout << "-----------------------------\n";
}




int main() {
    TodoList todoList;

    // Carica i dati salvati, se esistono
    if (todoList.readFromFile("todolist.json")) {
        cout << "Dati caricati con successo dal file todolist.json." << endl;
    } else {
        cout << "Nessun file di salvataggio trovato o errore nel caricamento. Verrà creato un nuovo file al salvataggio." << endl;
    }

    int choice;
    do {
        printMenu();

        cin >> choice;
        cin.ignore();  // Pulizia del buffer

        switch (choice) {
            case 1: { // Aggiungi attività
                addActivityCLI(todoList);
                break;
            }
            case 2: { // Elimina attività
                int index;
                cout << "Inserisci l'indice dell'attività da eliminare: ";
                cin >> index;
                cin.ignore();
                todoList.deleteActivity(index);
                break;
            }
            case 3: { // Modifica stato attività
                int index;
                int newState;
                cout << "Inserisci l'indice dell'attività: ";
                cin >> index;
                cout << "Inserisci il nuovo stato (0: Incompleta, 1: Completata): ";
                cin >> newState;
                cin.ignore();
                todoList.changeActivityStatus(index, newState);
                break;
            }
            case 4: { // Modifica descrizione attività
                int index;
                string newDesc;
                cout << "Inserisci l'indice dell'attività: ";
                cin >> index;
                cin.ignore();

                cout << "Inserisci la nuova descrizione: ";
                getline(cin, newDesc);
                todoList.changeActivityDescription(index, newDesc);
                break;
            }
            case 5: { // Visualizza tutte le attività
                printAll(todoList);
                break;
            }
            case 6: { // Ordina per data di scadenza
                todoList.sortByExpirationDate();
                printAll(todoList);
                break;
            }
            case 7: { // Ordina per priorità
                todoList.sortByPriority(true);
                printAll(todoList);
                break;
            }
            case 8: { // Ordina per stato
                todoList.sortByState();
                printAll(todoList);
                break;
            }
            case 9: { // Ordina per stato e priorità
                todoList.sortByStateAndPriority(true);
                printAll(todoList);
                break;
            }
            case 10: { // Ordina per stato e data di scadenza
                todoList.sortByStateAndExpirationDate();
                printAll(todoList);
                break;
            }
            case 11: { // Ricerca per descrizione e gestione risultati
                string keyword;
                cout << "Inserisci il termine da cercare: ";
                getline(cin, keyword);
                manageSearchResults(todoList, keyword);
                break;
            }
            case 0: { // Uscita: salvataggio finale
                cout << "Salvataggio finale in corso..." << endl;
                if (todoList.writeToFile("todolist.json")) {
                    cout << "File salvato con successo." << endl;
                } else {
                    cout << "Errore nel salvataggio finale." << endl;
                }
                break;
            }
            default:
                cout << "Scelta non valida! Riprova." << endl;
        }
    } while (choice != 0);

    return 0;
}

