#include "Date.hpp"
#include "Primary.hpp"

Date::Date(string complete_date) : complete_date(complete_date) {
    string result_year = NULL_STRING, result_month = NULL_STRING, result_day = NULL_STRING;
    bool flag_year = false, flag_month = false;
    for(char c : complete_date) {
        if(c == SLASH and !flag_year) {
            flag_year = true;
        }
        else if(c == SLASH and !flag_month) {
            flag_month = true;
        }
        else if(!flag_year) {
            result_year += c;
        }
        else if(!flag_month) {
            result_month += c;
        }
        else {
            result_day += c;
        }
    }
    year = stoi(result_year), month = stoi(result_month), day = stoi(result_day);
}