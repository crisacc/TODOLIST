#include "Activity.h"
#include "TodoList.h"

int main() {
    TodoList lista;

    // Aggiungi attività con scadenza, priorità e stato diversi
    lista.addActivity(Activity("Comprare il latte", false, Priority::Low));
    lista.addActivity(Activity("Studiare per l'esame", false, Priority::High));
    lista.addActivity(Activity("Fare esercizio fisico", true, Priority::Medium));
    lista.addActivity(Activity("Riparare la macchina", false, Priority::Unknown));
    lista.addActivity(Activity("Andare dal dentista", true, Priority::High));

    // Imposta date di scadenza

    lista.sortByStateAndExpirationDate();

    // Stampa attività ordinate
    lista.stampAll();

    return 0;
}
