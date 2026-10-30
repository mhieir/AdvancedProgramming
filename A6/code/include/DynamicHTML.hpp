#pragma once
#ifndef DYNAMIC_HTML_INCLUDE
#define DYNAMIC_HTML_INCLUDE

#include "Global.hpp"
#include "University.hpp"

string studentPage(string username, University* university);
string showOneCourse(vector<string> output);
string showAllCourse(vector<string> output);
string showPersonalPage(University* university, vector<string> output, PeopleType people_type);
string professorPage(string username, University* university);
string showMyCourse(vector<string> output);
string adminPage(string username, University* university);

#endif