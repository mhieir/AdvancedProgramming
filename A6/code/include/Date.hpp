#pragma once
#ifndef DATE_INCLUDE
#define DATE_INCLUDE

#include "Global.hpp"

class Date {
public:
    Date(string complete_date);
    ~Date() {};
    string getCompleteDate() {return complete_date;}
    int getYear() {return year;}
    int getMonth() {return month;}
    int getDay() {return day;}
protected:
private:
    string complete_date;
    int year, month, day;
};

#endif