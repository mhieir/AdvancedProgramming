#include "CourseOffer.hpp"
#include "Primary.hpp"

CourseOffer::CourseOffer(int courseOfferId, string id, string professor_id, int capacity, Time time, Date exam_time, int class_number, string name, int credit, int prerequisite, vector<string> majors_id) :
Course(id, name, credit, prerequisite, majors_id), capacity(capacity), courseOfferId(courseOfferId), time(time), exam_time(exam_time), professor_id(professor_id), class_number(class_number) {
    cloud = new Cloud;
    openForm = false;
}

void CourseOffer::addRequestedTA(string student_id) {
    requested_ta.push_back(student_id);
}

bool CourseOffer::inSameTime(Time new_time) {
    if(new_time.getWeekDay() == time.getWeekDay() and hasCommon(new_time.getStart(), new_time.getEnd(), time.getStart(), time.getEnd())) {
        return true;
    }
    else {
        return false;
    }
}

void CourseOffer::changeStatusTAForm(){
    if(openForm) {
        openForm = false;
    }
    else {
        openForm = true;
    }
}

bool CourseOffer::isTA(string ta_id) {
    for(int i = 0; i < (int) ta_ids.size(); i++) {
        if(ta_ids[i] == ta_id) {
            return true;
        }
    }
    return false;
}

bool CourseOffer::isProfessor(string request_professor_id) {
    if(professor_id == request_professor_id) {
        return true;
    }
    return false;
}

bool CourseOffer::isStudent(string request_student_id) {
    for(int i = 0; i < (int) students.size(); i++) {
        if(students[i] == request_student_id) {
            return true;
        }
    }
    return false;
}

bool CourseOffer::isInCourse(string id) {
    if(isStudent(id) or isProfessor(id) or isTA(id)) {
        return true;
    }
    return false;
}