//
// Created by Cristiano on 08/11/2024.
//
#include <gtest/gtest.h>
#include "../../TODOLIST/TodoList.h"
#include <fstream>

// Test per l'aggiunta di attività
TEST(TodoListTest, AddActivity) {
    TodoList todoList;
    Activity activity("Test Activity", Priority::Medium, Date(15, 10, 2025));
    todoList.addActivity(activity);

    ASSERT_EQ(todoList.getSize(), 1);
    EXPECT_EQ(todoList.getActivityAt(0).getDescription(), "Test Activity");
    EXPECT_EQ(todoList.getActivityAt(0).getPriority(), Priority::Medium);
    EXPECT_EQ(todoList.getActivityAt(0).getExpirationDate().toString(), "15/10/2025");
}

// Test per la cancellazione di attività con indice valido e non valido
TEST(TodoListTest, DeleteActivity) {
    TodoList todoList;
    todoList.addActivity(Activity("Activity 1", Priority::Low));
    todoList.addActivity(Activity("Activity 2", Priority::High));

    todoList.deleteActivity(1);  // Elimina "Activity 2"
    ASSERT_EQ(todoList.getSize(), 1);
    EXPECT_EQ(todoList.getActivityAt(0).getDescription(), "Activity 1");

    int sizeBefore = todoList.getSize();
    todoList.deleteActivity(10);  // Indice non valido, dimensione invariata
    EXPECT_EQ(todoList.getSize(), sizeBefore);
}

// Test per il cambio di stato dell'attività
TEST(TodoListTest, ChangeActivityStatus) {
    TodoList todoList;
    todoList.addActivity(Activity("Activity 1", Priority::Low));
    todoList.modifyActivity(0, true);
    EXPECT_TRUE(todoList.getActivityAt(0).isDone());

    // Indice non valido, lo stato non deve cambiare
    bool doneBefore = todoList.getActivityAt(0).isDone();
    todoList.modifyActivity(10, false);
    EXPECT_EQ(todoList.getActivityAt(0).isDone(), doneBefore);
}

// Test per il cambio di descrizione dell'attività
TEST(TodoListTest, ChangeActivityDescription) {
    TodoList todoList;
    todoList.addActivity(Activity("Activity 1", Priority::Low));
    todoList.modifyActivity(0, "Updated Description");
    EXPECT_EQ(todoList.getActivityAt(0).getDescription(), "Updated Description");

    // Indice non valido, la descrizione non deve cambiare
    std::string descriptionBefore = todoList.getActivityAt(0).getDescription();
    todoList.modifyActivity(10, "Another Description");
    EXPECT_EQ(todoList.getActivityAt(0).getDescription(), descriptionBefore);
}

// Test per l'ordinamento per data di scadenza
TEST(TodoListTest, SortByExpirationDate) {
    TodoList todoList;
    todoList.addActivity(Activity("Activity with Date", Priority::Medium, Date(1, 1, 2025)));
    todoList.addActivity(Activity("Activity without Date", Priority::High));

    todoList.sortByExpirationDate();
    EXPECT_EQ(todoList.getActivityAt(0).getDescription(), "Activity with Date");
    EXPECT_EQ(todoList.getActivityAt(1).getDescription(), "Activity without Date");
}

// Test per l'ordinamento per priorità
TEST(TodoListTest, SortByPriority) {
    TodoList todoList;
    todoList.addActivity(Activity("Low Priority", Priority::Low));
    todoList.addActivity(Activity("High Priority", Priority::High));

    todoList.sortByPriority(true);  // Ordinamento crescente
    EXPECT_EQ(todoList.getActivityAt(0).getDescription(), "Low Priority");
    EXPECT_EQ(todoList.getActivityAt(1).getDescription(), "High Priority");

    todoList.sortByPriority(false);  // Ordinamento decrescente
    EXPECT_EQ(todoList.getActivityAt(0).getDescription(), "High Priority");
    EXPECT_EQ(todoList.getActivityAt(1).getDescription(), "Low Priority");
}

// Test per l'ordinamento per stato
TEST(TodoListTest, SortByState) {
    TodoList todoList;
    Activity doneActivity("Done Activity", Priority::Medium);
    doneActivity.setDone(true);
    Activity notDoneActivity("Not Done Activity", Priority::High);
    todoList.addActivity(doneActivity);
    todoList.addActivity(notDoneActivity);

    todoList.sortByState();
    EXPECT_EQ(todoList.getActivityAt(0).getDescription(), "Not Done Activity");
    EXPECT_EQ(todoList.getActivityAt(1).getDescription(), "Done Activity");
}

//test per ordinamento combinato stato e priorità
TEST(TodoListTest, SortByStateAndPriority) {
    TodoList list;

    Activity A("A", Priority::Low);
    A.setDone(true);
    Activity B("B", Priority::High);
    B.setDone(true);
    Activity C("C", Priority::Medium);
    Activity D("D", Priority::Low);
    Activity E("E", Priority::High);

    list.addActivity(A);
    list.addActivity(B);
    list.addActivity(C);
    list.addActivity(D);
    list.addActivity(E);

    list.sortByStateAndPriority(true);

    EXPECT_EQ(list.getActivityAt(0).getDescription(), "E");
    EXPECT_EQ(list.getActivityAt(1).getDescription(), "C");
    EXPECT_EQ(list.getActivityAt(2).getDescription(), "D");
    EXPECT_EQ(list.getActivityAt(3).getDescription(), "B");
    EXPECT_EQ(list.getActivityAt(4).getDescription(), "A");

    list.sortByStateAndPriority(false);

    EXPECT_EQ(list.getActivityAt(0).getDescription(), "D");
    EXPECT_EQ(list.getActivityAt(1).getDescription(), "C");
    EXPECT_EQ(list.getActivityAt(2).getDescription(), "E");
    EXPECT_EQ(list.getActivityAt(3).getDescription(), "A");
    EXPECT_EQ(list.getActivityAt(4).getDescription(), "B");

}


//test per non eliminare o modificare attività con indici non validi
TEST(TodoListTest, InvalidIndexHandling) {
    TodoList list;
    list.addActivity(Activity("Task A", Priority::High));

    // Tentativo di eliminare un'attività inesistente
    list.deleteActivity(10);
    EXPECT_EQ(list.getSize(), 1);

    // Tentativo di cambiare stato di un'attività inesistente
    list.modifyActivity(10, true);
    EXPECT_FALSE(list.getActivityAt(0).isDone());

    // Tentativo di cambiare descrizione con un indice non valido
    list.modifyActivity(-1, "Nuova descrizione");
    EXPECT_EQ(list.getActivityAt(0).getDescription(), "Task A");
}

//test per metodo ricerca er descrizione
TEST(TodoListTest, SearchByDescription) {
    TodoList list;
    list.addActivity(Activity("Comprare latte", Priority::High));
    list.addActivity(Activity("Allenamento palestra", Priority::Medium));
    list.addActivity(Activity("Comprare pane", Priority::High));

    auto results = list.searchByDescription("Comprare");

    EXPECT_EQ(results.size(), 2);
    EXPECT_EQ(results[0].second->getDescription(), "Comprare latte");
    EXPECT_EQ(results[1].second->getDescription(), "Comprare pane");
}

// Test per il salvataggio e caricamento da file
TEST(TodoListTest, SaveAndLoadFromFile) {
    TodoList list;
    Activity activity("Test file", Priority::High);
    list.addActivity(activity);

    EXPECT_TRUE(list.writeToFile("test.json"));

    TodoList newList;
    EXPECT_TRUE(newList.readFromFile("test.json"));
    ASSERT_EQ(newList.getSize(), 1);
    EXPECT_EQ(newList.getActivityAt(0).getDescription(), "Test file");
}

// test per il salvataggio auutomatico
TEST(TodoListTest, AutoSaveTriggered) {
    TodoList list;
    for (int i = 0; i < 5; ++i) {
        list.addActivity(Activity("Task " + std::to_string(i), Priority::High));
    }

    // Controlla se il contatore è stato azzerato dopo 5 modifiche
    EXPECT_EQ(list.getChangeCounter(), 0);

    // Verifica che il file sia stato scritto
    std::ifstream file("todo_list.json");
    EXPECT_TRUE(file.good());  // Controlla se il file esiste
}
