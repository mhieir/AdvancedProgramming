#pragma once
#ifndef STUDENT_INCLUDE
#define STUDENT_INCLUDE

#include "Global.hpp"
#include "People.hpp"

class Student : public People {
public:
    Student(string id, string name, Major* major, int semester, string password);
    ~Student() {};
    int getSemester() {return semester;}
    void personalPage(vector<string>& output);
    void getPost(vector<string>& output, int post_id);
protected:
    int semester;
private:
};

#endif