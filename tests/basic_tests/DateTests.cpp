#include <gtest/gtest.h>
#include "Date.h"


//  Test del Costruttore di Default
TEST(DateTest, DefaultConstructor) {
Date date;
EXPECT_EQ(date.toString(), "01/01/1970");
}

// 2. Test con date ai limiti del mese e dell’anno
TEST(DateTest, EdgeCases) {
Date startOfYear(1, 1, 2023);
Date endOfYear(31, 12, 2023);
EXPECT_EQ(startOfYear.toString(), "01/01/2023");
EXPECT_EQ(endOfYear.toString(), "31/12/2023");
}

// 3. Test con date estreme
TEST(DateTest, ExtremeYears) {
Date futureDate(1, 1, 9999);
Date ancientDate(1, 1, 1);
EXPECT_EQ(futureDate.toString(), "01/01/9999");
EXPECT_EQ(ancientDate.toString(), "01/01/0001");
}

// 4. Test con febbraio (28 e 29 giorni)
TEST(DateTest, FebruaryDaysHandling) {
Date feb28_2023(28, 2, 2023);  // Anno non bisestile
Date feb29_2024(29, 2, 2024);  // Anno bisestile
Date invalidFeb29_2023(29, 2, 2023);  // 2023 non è bisestile

EXPECT_EQ(feb28_2023.toString(), "28/02/2023");
EXPECT_EQ(feb29_2024.toString(), "29/02/2024");
EXPECT_EQ(invalidFeb29_2023.toString(), "01/01/1970");  // Data invalida → default
}

// Test con formati di input errati per setDateFromString
TEST(DateTest, SetDateFromStringInvalidFormats) {
Date date;

EXPECT_FALSE(date.setDateFromString("2023/12/25", "%d/%m/%Y"));  // Formato errato
EXPECT_FALSE(date.setDateFromString("12-25-2023", "%d/%m/%Y"));  // Formato errato
EXPECT_FALSE(date.setDateFromString("31/02/2023", "%d/%m/%Y"));  // Data inesistente
EXPECT_FALSE(date.setDateFromString("testo non valido", "%d/%m/%Y"));  // Stringa completamente errata

// La data deve rimanere la default dopo tentativi falliti
EXPECT_EQ(date.toString(), "01/01/1970");
}

// Test con vari formati di output per toString
TEST(DateTest, ToStringDifferentFormats) {
Date date(15, 10, 2024);
EXPECT_EQ(date.toString("%d/%m/%Y"), "15/10/2024");
EXPECT_EQ(date.toString("%Y-%m-%d"), "2024-10-15");
EXPECT_EQ(date.toString("%B %d, %Y"), "October 15, 2024");
}

// Test dell'operatore <
TEST(DateTest, LessThanOperator) {
    Date date1(15, 10, 2024);
    Date date2(16, 10, 2024);
    Date date3(15, 11, 2024);
    Date date4(15, 10, 2025);

    EXPECT_TRUE(date1 < date2);
    EXPECT_TRUE(date1 < date3);
    EXPECT_TRUE(date1 < date4);

    EXPECT_FALSE(date2 < date1);
    EXPECT_FALSE(date3 < date1);
    EXPECT_FALSE(date4 < date1);

    EXPECT_FALSE(date1 < date1);
}

// Test dell'operatore ==
TEST(DateTest, EqualityOperator) {
    Date date1(15, 10, 2024);
    Date date2(15, 10, 2024);
    Date date3(16, 10, 2024);
    Date date4(15, 11, 2024);
    Date date5(15, 10, 2025);

    EXPECT_TRUE(date1 == date2);  // Stessa data, devono essere uguali

    EXPECT_FALSE(date1 == date3); // Giorno diverso
    EXPECT_FALSE(date1 == date4); // Mese diverso
    EXPECT_FALSE(date1 == date5); // Anno diverso
}