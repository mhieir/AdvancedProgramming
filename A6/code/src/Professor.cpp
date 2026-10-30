#include "Professor.hpp"

Professor::Professor(string id, string name, Major* major, string _string_position, string password):
People(id, name, major, password, _PROFESSOR) {
    if(_string_position == "instructor") {
        string_position = "Instructor";
    }
    else if(_string_position == "assistant professor") {
        string_position = "Assistant Professor";
    }
    else if(_string_position == "associate professor") {
        string_position = "Associate Professor";
    }
    else if(_string_position == "professor") {
        string_position = "Professor";
    }
}

void Professor::personalPage(vector<string>& output) {
    output.push_back(name);
    output.push_back(major->getName());
    output.push_back(string_position);
    People ::showOfferCourses(output);
    People ::showPosts(output);
}

void Professor::getPost(vector<string>& output, int post_id) {
    output.push_back(name + SPACE + major->getName() + SPACE + string_position + SPACE);
    People ::showOfferCourses(output);
    People ::showOnePost(output, post_id);
}