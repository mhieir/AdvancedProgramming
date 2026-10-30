#include "Course.hpp"

Course::Course(string id, string name, int credit, int prerequisite, vector<string> majors_id) :
Entity(id, name), credit(credit), prerequisite(prerequisite), majors_id(majors_id) {}

bool Course::hasMajor(string major_id) {
    for(int i = 0; i < (int) majors_id.size(); i++) {
        if(majors_id[i] == major_id) {
            return true;
        }
    }
    return false;
}