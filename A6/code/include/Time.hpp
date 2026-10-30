#pragma once
#ifndef TIME_INCLUDE
#define TIME_INCLUDE

#include "Global.hpp"

class Time {
public:
    Time(string complete_time);
    ~Time() {};
    string getCompleteTime() {return complete_time;}
    string getWeekDay() {return weekday;}
    int getStart() {return start;}
    int getEnd() {return end;}
protected:
private:
    string complete_time, weekday;
    int start, end;
};

#endif