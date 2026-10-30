#pragma once
#ifndef PROFESSOR_INCLUDE
#define PROFESSOR_INCLUDE

#include "Global.hpp"
#include "People.hpp"
#include "Time.hpp"
#include "Major.hpp"

enum Position {
    INSTRUCTOR,
    ASSISTANT,
    ASSOCIATE,
    PROFESSSOR
};

class Professor : public People {
public:
    Professor(string id, string name, Major* major, string string_position, string password);
    ~Professor() {};
    Position getPosition() {return position;}
    void personalPage(vector<string>& output);
    void getPost(vector<string>& output, int post_id);
protected:
    string string_position;
    Position position;
private:
};

#endif