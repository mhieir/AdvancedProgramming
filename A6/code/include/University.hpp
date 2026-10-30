#ifndef UNIVERSITY_INCLUDE
#define UNIVERSITY_INCLUDE

#include "Global.hpp"
#include "Entity.hpp"
#include "Course.hpp"
#include "Major.hpp"
#include "People.hpp"
#include "Student.hpp"
#include "Professor.hpp"
#include "UTAccount.hpp"
#include "CourseOffer.hpp"

class University {
public:
    University(char **argv);
    ~University() {};
    int findPeopleIndexById(string id);
    void addMajor(string id, string name);
    void addStudent(string id, string name, Major* major, int semester, string password);
    void addProfessor(string id, string name, Major* major, string string_position, string password);
    int findMajor(string id);
    Major* getMajorById(int index);
    void addCourse(string id, string name, int credit, int prerequisite, vector<string> majors_id);
    void cleanOutput() {output.clear();}
    vector<string> getExtraOutput() {return extra_output;}
    void cleanExtraOutput() {extra_output.clear();}
    void makeDefaultConnections();
    void getExtraInput(vector<bool> result) {closeFormResult = result;}
    void cleanCloseForm();
    void runLogin(string id, string password);
    void runLogout();
    void runGetCourseById(string id);
    void runPersonalPage(string id);
    void runGetCourse();
    void runShareCourse(string course_id, string professor_id, string capacity, string time, string exam_date, string class_number);

    void runDeleteCourse(string id);
    void runPutCourse(string id);
    bool checkLogin();
    void runSharePost(string title, string message, string image_address);
    void runAddProfile(string address);
    void runGetMyCourse();
    string getUserProfile() {return user->getProfile();}
    string getUserName() {return user->getName();}
    string getUserMajor() {return getMajorById(findMajor(user->getMajorId()))->getName();}
    string getUserId() {return user->getId();}
    PeopleType peopleStatus(string id) {return people[findPeopleIndexById(id)]->getPeopleType();}
    vector<string> getOutput();

protected:
private:
    void makeMajorString(vector<string> major_string);
    void makeStudentString(vector<string> student_string);
    void makeCourseString(vector<string> course_string);
    void makeProfessorString(vector<string> professor_string);
    vector<Major*> majors;
    vector<People*> people;
    vector<Course*> courses;
    vector<string> input_line;
    vector<CourseOffer*> all_course_offers;
    vector<string> output;
    vector<string> extra_output;
    vector<bool> closeFormResult;
    People* user;
    int course_offer_id;
    int current_course_offer;

    void runGetCourseChannel(string id);
    void makeExtraOutput(vector<string> requested_TAs, int index);
    void runCloseTAForm(string id);
    void runPostTAForm(string course_id, string message);

    void addNotificationCoursePost(int index, string notification_line);
    void runCoursePost(string id, string title, string message, string image_address);
    
    void runNotification();
    
    bool isStudent();
    void runGetPost(string id, string post_id);
    bool inCommonTime(string professor_id, string time);
    bool isPresentByProfessor(string professor_id, string course_id);
    int findCourseIndexById(string id);
    
    bool isProfessor(string id);
    bool checkValidCourse(string id);
    void runRemovePost(string id);
    bool checkValidPassword(string id, string password);
    bool checkValidId(string id);
    void runConnect(string id);
    void showAllCourseOffers();
    void showOneCourseOffers(int index);
    void catchError(runtime_error& ex);
    void askProfessorForTA(int index);
    void runTARequest(string professor_id, string form_id );
    void runGetPostCourseChannel(string id, string post_id);
};

#endif