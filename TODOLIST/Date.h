//
// Created by Cristiano on 25/10/2024.
//

#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
private:
    int day;
    int month;
    int year;

    static bool isLeapYear(int year);
    static bool isValidDate(int day, int month, int year) ;

public:
    explicit Date(int day = 1, int month = 1, int year = 1970);
    bool setDate(int day, int month, int year);
    bool setDateFromString(const std::string& dateString, const std::string& format = "%d/%m/%Y");
    std::string toString(const std::string& format = "%d/%m/%Y") const;

    // Metodi per confrontare le date
    bool operator<(const Date& other) const;
    bool operator==(const Date& other) const;
};

#endif // DATE_H

