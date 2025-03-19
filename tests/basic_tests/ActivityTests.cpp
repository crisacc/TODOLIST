//
// Created by Cristiano on 08/11/2024.
//
#include <gtest/gtest.h>
#include "Activity.h"
#include "Date.h"

// Test del costruttore di default
TEST(ActivityTest, DefaultConstructor) {
    Activity activity;
    EXPECT_EQ(activity.getDescription(), "");
    EXPECT_EQ(activity.getPriority(), Priority::Unknown);
    EXPECT_FALSE(activity.isDone());
    EXPECT_FALSE(activity.hasExpirationDate());
}

//test del costruttore con parametri senza scadenza
TEST(ActivityTest, ParameterizedConstructorWithoutDate) {
    Activity activity("Test Activity", Priority::High);
    EXPECT_EQ(activity.getDescription(), "Test Activity");
    EXPECT_EQ(activity.getPriority(), Priority::High);
    EXPECT_FALSE(activity.isDone());
    EXPECT_FALSE(activity.hasExpirationDate());
}

// Test del costruttore con parametri con scadenza
TEST(ActivityTest, ParameterizedConstructor) {
    Date date(15, 10, 2024);
    Activity activity("Test", Priority::High, date);
    EXPECT_EQ(activity.getDescription(), "Test");
    EXPECT_EQ(activity.getPriority(), Priority::High);
    EXPECT_FALSE(activity.isDone());
    EXPECT_TRUE(activity.hasExpirationDate());
    EXPECT_EQ(activity.getExpirationDate().toString(), "15/10/2024");
}

// Test di set e get per description
TEST(ActivityTest, SetGetDescription) {
    Activity activity;
    activity.setDescription("New Description");
    EXPECT_EQ(activity.getDescription(), "New Description");
}

// Test di set e get per done
TEST(ActivityTest, SetGetDone) {
    Activity activity;
    activity.setDone(true);
    EXPECT_TRUE(activity.isDone());
    activity.setDone(false);
    EXPECT_FALSE(activity.isDone());
}

// Test di set e get per priority
TEST(ActivityTest, SetGetPriority) {
    Activity activity;
    activity.setPriority(Priority::Low);
    EXPECT_EQ(activity.getPriority(), Priority::Low);
}

// Test di set e get per expiration date
TEST(ActivityTest, SetGetExpirationDate) {
    Activity activity;
    Date date(20, 12, 2024);
    activity.setExpirationDate(date);
    EXPECT_TRUE(activity.hasExpirationDate());
    EXPECT_EQ(activity.getExpirationDate().toString(), "20/12/2024");
}

//test per eliminare la data di scadenza
TEST(ActivityTest, DeleteExpirationDate) {
    Activity activity;
    Date date(10, 11, 2024);
    activity.setExpirationDate(date);
    EXPECT_TRUE(activity.hasExpirationDate());
    activity.deleteExpirationDate();
    EXPECT_FALSE(activity.hasExpirationDate());
}

//test del metodo priority to string
TEST(ActivityTest, PriorityToString) {
    Activity activity;
    activity.setPriority(Priority::High);
    EXPECT_EQ(activity.priorityToString(), "High");

    activity.setPriority(Priority::Medium);
    EXPECT_EQ(activity.priorityToString(), "Medium");

    activity.setPriority(Priority::Low);
    EXPECT_EQ(activity.priorityToString(), "Low");

    activity.setPriority(Priority::Unknown);
    EXPECT_EQ(activity.priorityToString(), "Unknown");
}

// Test del metodo toJson
TEST(ActivityTest, ToJson) {
    Activity activity("Test Activity", Priority::Medium);
    json j = activity.toJson();
    EXPECT_EQ(j["description"], "Test Activity");
    EXPECT_EQ(j["priority"], "Medium");
    EXPECT_EQ(j["done"], false);
    EXPECT_TRUE(j["expirationDate"].is_null());
}

// Test del metodo fromJson con dati validi
TEST(ActivityTest, FromJsonValidData) {
    json j;
    j["description"] = "Loaded Activity";
    j["done"] = true;
    j["priority"] = "High";
    j["expirationDate"] = "01/01/2025";

    Activity activity;
    EXPECT_TRUE(activity.fromJson(j));
    EXPECT_EQ(activity.getDescription(), "Loaded Activity");
    EXPECT_TRUE(activity.isDone());
    EXPECT_EQ(activity.getPriority(), Priority::High);
    EXPECT_TRUE(activity.hasExpirationDate());
    EXPECT_EQ(activity.getExpirationDate().toString(), "01/01/2025");
}

// Test del metodo fromJson con dati mancanti o errati
TEST(ActivityTest, FromJsonInvalidData) {
    json j;
    j["description"] = "Partial Activity";
    j["priority"] = "Low";

    Activity activity;
    EXPECT_TRUE(activity.fromJson(j));
    EXPECT_EQ(activity.getDescription(), "Partial Activity");
    EXPECT_EQ(activity.getPriority(), Priority::Low);
    EXPECT_FALSE(activity.isDone());  // Valore di default
    EXPECT_FALSE(activity.hasExpirationDate());  // Nessuna data impostata

    // Test con dati errati
    json j_invalid;
    j_invalid["description"] = "Invalid Activity";
    j_invalid["priority"] = "Unknown";
    j_invalid["done"] = "not_a_boolean";  // Valore non valido

    EXPECT_FALSE(activity.fromJson(j_invalid));  // Deve fallire il parsing
}