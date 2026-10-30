#ifndef COURSE_OFFER_INCLUDE
#define COURSE_OFFER_INCLUDE

#include "Global.hpp"
#include "Course.hpp"
#include "Time.hpp"
#include "Date.hpp"
#include "Cloud.hpp"


class CourseOffer : public Course {
public:
    CourseOffer(int courseOfferId, string id, string professor_id, int capacity, Time time, Date exam_time, int class_number,
    string name, int credit, int prerequisite, vector<string> majors_id);
    ~CourseOffer() {};
    int getCourseOfferId() {return courseOfferId;}
    int getClassNumber() {return class_number;}
    int getCapacity() {return capacity;}
    string getProfessorId() {return professor_id;}
    string getTime() {return time.getCompleteTime();}
    string getExamTime() {return exam_time.getCompleteDate();}
    void addTA(string ta_id) {ta_ids.push_back(ta_id);}
    void addStudent(string student_id) {students.push_back(student_id);}
    bool isTA(string ta_id);
    bool inSameTime(Time new_time);
    bool isProfessor(string request_professor_id);
    void showOnePost(vector<string>& output, int post_id) {cloud->showOnePost(output, post_id);}
    void showPosts(vector<string>& output) {cloud->showPosts(output);}
    void addPost(string title, string message, string image_address, string author, PostType post_type, string extra, int course_id) {cloud->addPost(title, message, image_address, author, post_type, extra, course_id);}
    void removePost(int post_id) {cloud->removePost(post_id);}
    bool isStudent(string request_student_id);
    bool isInPost(int post_id) {return cloud->isInPost(post_id);}
    void addRequestedTA(string student_id);
    bool getOpenForm() {return openForm;}
    void changeStatusTAForm();
    void showOnePostCourseChannel(vector<string>& output, int post_id) {cloud->showOnePostCourseChannel(output, post_id);}
    void showPostsCourseChannel(vector<string>& output) {cloud->showPostsCourseChannel(output);}
    bool isInCourse(string id);
    vector<string> getRequestedTA() {return requested_ta;}
    vector<string> getStudents() {return students;}
    vector<string> getTaIds() {return ta_ids;}
    void cleanTARequested() {requested_ta.clear();}
protected:
    bool openForm;
    string professor_id;
    vector<string> ta_ids;
    vector<string> students;
    vector<string> requested_ta;
    Time time;
    Date exam_time;
    int courseOfferId, class_number, capacity;
    Cloud* cloud;
private:
};

#endif