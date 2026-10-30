#include "People.hpp"

People::People(string id, string name, Major* major, string password, PeopleType people_type) :
Entity(id, name), major(major), password(password), people_type(people_type) {
    profile_image = "home.png";
    cloud = new Cloud();
}

bool People::inConnection(string new_id) {
    for(int i = 0; i < connections.size(); i++) {
        if(new_id == connections[i]->getId()) return true;
    }
    return false;
}

void People::addProfile(string new_profile_image) {
    profile_image = new_profile_image;
}

bool People::validCourseTime(Time new_time) {
    for(int i = 0; i < course_offers.size(); i++) {
        if(course_offers[i]->inSameTime(new_time)) {
            return false;
        }
    }
    return true;
}

bool People::validCourseDate(string new_date) {
    for(int i = 0; i < course_offers.size(); i++) {
        if(course_offers[i]->getExamTime() == new_date) {
            return false;
        }
    }
    return true;
}

void People::removeCourse(int course_offer_id) {
    for(int i = 0; i < course_offers.size(); i++) {
        if(course_offers[i]->getCourseOfferId() == course_offer_id) {
            course_offers.erase(course_offers.begin() + i);
            return;
        }
    }
}

void People::showOfferCourses(vector<string>& output) {
    string answer = "";
    for(int i = 0; i + 1 < course_offers.size(); i++) {
        answer += course_offers[i]->getName() + COMMA;
       // output.push_back( course_offers[i]->getName() + COMMA);
    }
    if(!course_offers.empty()) {
        answer += course_offers.back()->getName();
       // output.push_back(course_offers.back()->getName());
    }
    output.push_back(answer);
}


bool People::hasCourseOfferById(int course_id) {
    for(int i = 0; i < course_offers.size(); i++) {
        if(course_offers[i]->getCourseOfferId() == course_id) {
            return true;
        }
    }
    return false;
 }

string People::getProfessorName(vector<People*> people, string prof_id) {
    for(int i = 0; i < people.size(); i++) {
        if(people[i]->getId() == prof_id) {
            return people[i]->getName();
        }
    }
}

void People::showCourses(vector<string>& output, vector<People*> people){
    for(int i = 0; i < course_offers.size(); i++) {
        output.push_back(to_string(course_offers[i]->getCourseOfferId()));
        output.push_back(course_offers[i]->getName());
        output.push_back(to_string(course_offers[i]->getCapacity()));
        output.push_back(getProfessorName(people, course_offers[i]->getProfessorId()));
        output.push_back(course_offers[i]->getTime());
        output.push_back(course_offers[i]->getExamTime());
        output.push_back(to_string(course_offers[i]->getClassNumber()));
    }
}

void People::addNotification(string notification_line) {
    notifications.push_back(notification_line);
}

bool People::emptyNotification() {
    if(notifications.size() == 0) {
        return true;
    }
    else {
        return false;
    }
}

void People::shareNotification(string command) {
    for(int i = 0; i < connections.size(); i++) {
        connections[i]->addNotification(command);
    }
}

void People::printNotification(vector<string>& output) {
    for(int i = (int) notifications.size() - 1; 0 <= i; i--) {
        output.push_back(notifications[i]);
    }
    notifications.clear();
}