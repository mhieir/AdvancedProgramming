#include "Time.hpp"
#include "Primary.hpp"

Time::Time(string complete_time) : complete_time(complete_time) {
    weekday = NULL_STRING;
    string result_start = NULL_STRING, result_end = NULL_STRING;
    bool flag_colon = false, flag_dash = false;
    for(char c : complete_time) {
        if(c == COLON) {
            flag_colon = true;
        }
        else if(c == DASH) {
            flag_dash = true;
        }
        else if(!flag_colon) {
            weekday += c;
        }
        else if(!flag_dash) {
            result_start += c;
        }
        else {
            result_end += c;
        }
    }
    start = stoi(result_start), end = stoi(result_end);
}