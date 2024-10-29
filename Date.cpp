//
// Created by Cristiano on 25/10/2024.
//

#include "Date.h"
#include <sstream>
#include <iomanip>
#include <iostream>

Date::Date(int day, int month, int year) {
    if (!setDate(day, month, year)) {
        // Imposta una data di default se la data fornita è invalida
        this->day = 1;
        this->month = 1;
        this->year = 1970;
    }
}

bool Date::isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

bool Date::isValidDate(int d, int m, int y) {
    if (y < 1 || m < 1 || m > 12) return false;

    int daysInMonth[] = { 31, (isLeapYear(y) ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (d < 1 || d > daysInMonth[m - 1]) return false;
    return true;
}

bool Date::setDate(int d, int m, int y) {
    if (isValidDate(d, m, y)) {
        this ->day = d;
        this->month = m;
        this->year = y;
        return true;
    }
    return false;
}

bool Date::setDateFromString(const std::string& dateString, const std::string& format) {
    std::tm tm = {};
    std::istringstream ss(dateString);
    ss >> std::get_time(&tm, format.c_str());
    if (ss.fail()) {
        std::cerr << "Formato data non valido. Usa " << format << "." << std::endl;
        return false;
    }

    return setDate(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

std::string Date::toString(const std::string& format) const {
    std::tm tm = {};
    tm.tm_mday = day;
    tm.tm_mon = month - 1;
    tm.tm_year = year - 1900;

    std::ostringstream ss;
    ss << std::put_time(&tm, format.c_str());
    return ss.str();
}

bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

bool Date::operator==(const Date& other) const {
    return (year == other.year && month == other.month && day == other.day);
}

