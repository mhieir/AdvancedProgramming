#ifndef PEOPLE_INCLUDE
#define PEOPLE_INCLUDE

#include "Global.hpp"
#include "Entity.hpp"
#include "Major.hpp"
#include "Post.hpp"
#include "Time.hpp"
#include "CourseOffer.hpp"
#include "Cloud.hpp"


class People : public Entity {
public:
    People(string id, string name, Major* major, string password, PeopleType people_type);
    ~People() {};
    void addProfile(string new_profile_image);
    bool validCourseDate(string new_date);
    string getMajorId() {return major->getId();}
    string getPassword() {return password;}
    void addConnection(People* new_connection) {connections.push_back(new_connection);}
    bool inConnection(string new_id);
    bool isInPost(int post_id) {return cloud->isInPost(post_id);}
    bool isTAForm(int post_id) {return cloud->isTAForm(post_id);}
    void addPost(string title, string message, string image_address, string author, PostType post_type, string extra, int course_id) {cloud->addPost(title, message, image_address, author, post_type, extra, course_id);}
    void removePost(int post_id) {cloud->removePost(post_id);}
    virtual void personalPage(vector<string>& output) = 0;
    virtual void getPost(vector<string>& output, int post_id) = 0;
    bool validCourseTime(Time new_time);
    void addCourse(CourseOffer* course_offer) {course_offers.push_back(course_offer);}
    void removeCourse(int course_offer_id);
    PeopleType getPeopleType() {return people_type;}
    void showOnePost(vector<string>& output, int post_id) {cloud->showOnePost(output, post_id);}
    virtual int getSemester() {return 0;};
    virtual int getPre() {return 0;};
    bool hasCourseOfferById(int course_id);
    int numberOfCourses() {return (int) course_offers.size();}
    void showCourses(vector<string>& output, vector<People*> people);
    string getProfessorName(vector<People*> people, string prof_id);
    string getProfile() {return profile_image;}
    void showOfferCourses(vector<string>& output);
    void showPosts(vector<string>& output) {cloud->showPosts(output);}
    void shareNotification(string command);
    void addNotification(string notification_line);
    void printNotification(vector<string>& output);
    bool emptyNotification();
    int findCourseByPost(int index) {return cloud->findCourseByPost(index);}
protected:
    Major* major;
    string password;
    vector<People*> connections;
    vector<CourseOffer*> course_offers;
    Cloud* cloud;
    PeopleType people_type;
    vector<string> notifications;
    string profile_image;
private:
};

#endif