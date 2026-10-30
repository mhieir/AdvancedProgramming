#include "University.hpp"
#include "Primary.hpp"

Major* University::getMajorById(int index) {
    return majors[index];
}

int University::findMajor(string id) {
    for(int i = 0; i < majors.size(); i++) {
        if(majors[i]->getId() == id) {
            return i;
        }
    }
}

void University::addMajor(string id, string name) {
    majors.push_back(new Major(id, name));
}

void University::addStudent(string id, string name, Major* major, int semester, string password) {
    people.push_back(new Student(id, name, major, semester, password));
}

void University::addCourse(string id, string name, int credit, int prerequisite, vector<string> majors_id) {
    courses.push_back(new Course(id, name, credit, prerequisite, majors_id));
}

void University::addProfessor(string id, string name, Major* major, string string_position, string password) {
    people.push_back(new Professor(id, name, major, string_position, password));
}

void University::makeMajorString(vector<string> major_string) {
    for(int i = 1; i < major_string.size(); i++) {
        vector<string> splitted = splitByInputSign(major_string[i], COMMA);
        addMajor(splitted[0], splitted[1]);
    }
}

void University::makeStudentString(vector<string> student_string) {
    for(int i = 1; i < student_string.size(); i++) {
        vector<string> splitted = splitByInputSign(student_string[i], COMMA);
        addStudent(splitted[0], splitted[1], getMajorById(findMajor(splitted[2])), stoi(splitted[3]), splitted[4]);
    }
}

void University::makeCourseString(vector<string> course_string) {
    for(int i = 1; i < course_string.size(); i++) {
        vector<string> splitted = splitByInputSign(course_string[i], COMMA);
        addCourse(splitted[0], splitted[1], stoi(splitted[2]), stoi(splitted[3]), splitByInputSign(splitted[4], SEMI_COLON));
    }
}

void University::makeProfessorString(vector<string> professor_string) {
    for(int i = 1; i < professor_string.size(); i++) {
        vector<string> splitted = splitByInputSign(professor_string[i], COMMA);
        addProfessor(splitted[0], splitted[1], getMajorById(findMajor(splitted[2])), splitted[3], splitted[4]);
    }
}

void University::makeDefaultConnections() {
    people.push_back(new UTAccount(ZERO_STRING, UT_ACCOUNT));
    for(int i = 0; i + 1 < people.size(); i++) {
        people[i]->addConnection(people.back());
        people.back()->addConnection(people[i]);
    }
}

University::University(char **argv) {
    user = nullptr;
    makeMajorString(read_csv(argv[1]));
    makeStudentString(read_csv(argv[2]));
    makeCourseString(read_csv(argv[3]));
    makeProfessorString(read_csv(argv[4]));
    course_offer_id = START_ID;
    current_course_offer = INVALID;
    extra_output.clear();
    makeDefaultConnections();
}

vector<string> University::getOutput(){
    vector<string> copy_output = output;
    cleanOutput();
    return copy_output;
}

void University::catchError(runtime_error& ex) {
    output.push_back(string(ex.what()) + END_LINE);
}

bool University::checkValidPassword(string id, string password) {
    for(int i = 0; i < people.size(); i++) {
        if(people[i]->getId() == id and people[i]->getPassword() == password) {
            return true;
        }
    }
    return false;
}

bool University::isStudent() {
    if(user->getPeopleType() == _STUDENT) {
        return true;
    }
    else {
        return false;
    }
}

bool University::checkLogin() {
    if(user != nullptr) {
        return true;
    }
    else {
        return false;
    }
}

bool University::checkValidId(string id) {
    for(int i = 0; i < people.size(); i++) {
        if(people[i]->getId() == id) {
            return true;
        }
    }
    return false;
}

bool University::checkValidCourse(string id) {
    for(int i = 0; i < courses.size(); i++) {
        if(courses[i]->getId() == id) {
            return true;
        }
    }
    return false;
}

bool University::isProfessor(string id) {
    for(int i = 0; i < people.size(); i++) {
        if(people[i]->getPeopleType() == _PROFESSOR and people[i]->getId() == id) {
            return true;
        }
    }
    return false;
}

int University::findPeopleIndexById(string id) {
    for(int i = 0; i < people.size(); i++) {
        if(people[i]->getId() == id) {
            return i;
        }
    }
}

bool University::inCommonTime(string professor_id, string time) {
    int professor_index = findPeopleIndexById(professor_id);
    Time new_time(time);
    if(people[professor_index]->validCourseTime(new_time)) {
        return false;
    }
    else {
        return true;
    }

}

int University::findCourseIndexById(string id) {
    for(int i = 0; i < courses.size(); i++) {
        if(courses[i]->getId() == id) {
            return i;
        }
    }
}

bool University::isPresentByProfessor(string professor_id, string course_id) {
    int professor_index = findPeopleIndexById(professor_id);
    int course_index = findCourseIndexById(course_id);
    return courses[course_index]->hasMajor(people[professor_index]->getMajorId());
}

void University::showOneCourseOffers(int index) {
    output.push_back(to_string(all_course_offers[index]->getCourseOfferId()) + SPACE);
    output.push_back(all_course_offers[index]->getName() + SPACE);
    output.push_back(to_string(all_course_offers[index]->getCapacity()) + SPACE);
    output.push_back(people[findPeopleIndexById(all_course_offers[index]->getProfessorId())]->getName() + SPACE);
    output.push_back(all_course_offers[index]->getTime()  + SPACE);
    output.push_back(all_course_offers[index]->getExamTime() + SPACE);
    output.push_back(to_string(all_course_offers[index]->getClassNumber()) + END_LINE);
}


void University::addNotificationCoursePost(int index, string notification_line) {
    for(int i = 0; i < all_course_offers[index]->getStudents().size(); i++) {
        people[findPeopleIndexById(all_course_offers[index]->getStudents()[i])]->addNotification(notification_line);
    }
    if(user->getPeopleType() != _PROFESSOR) {
        people[findPeopleIndexById(all_course_offers[index]->getProfessorId())]->addNotification(notification_line);
    }
    for(int i = 0; i < all_course_offers[index]->getTaIds().size(); i++) {
        if(user->getId() == all_course_offers[index]->getTaIds()[i]) {
            continue;
        }
        else {
            people[findPeopleIndexById(all_course_offers[index]->getTaIds()[i])]->addNotification(notification_line);
        }
    }
}

void University::showAllCourseOffers() {
    for(int i = 0; i < all_course_offers.size(); i++) {
        output.push_back(to_string(all_course_offers[i]->getCourseOfferId()));
        output.push_back(all_course_offers[i]->getName());
        output.push_back(to_string(all_course_offers[i]->getCapacity()));
        output.push_back(people[findPeopleIndexById(all_course_offers[i]->getProfessorId())]->getName());
    }
}



void University::makeExtraOutput(vector<string> requested_TAs, int index) {
    for(int i = 0; i < requested_TAs.size(); i++) {
        extra_output.push_back(requested_TAs[i] + SPACE + people[findPeopleIndexById(requested_TAs[i])]->getName() + SPACE + to_string(people[findPeopleIndexById(requested_TAs[i])]->getSemester()) + COLON + SPACE);
    }
    current_course_offer = index;
}

void University::askProfessorForTA(int index) {
    current_course_offer = index;
    output.push_back(TA_FORM_FIRST + to_string(all_course_offers[index]->getRequestedTA().size()) + SPACE + TA_FORM_SECOND + END_LINE);
    makeExtraOutput(all_course_offers[index]->getRequestedTA(), index);
}

void University::cleanCloseForm() {
    if(current_course_offer == INVALID) {
        return;
    }
    for(int i = 0; i < all_course_offers[current_course_offer]->getRequestedTA().size(); i++) {
        string ta_id = all_course_offers[current_course_offer]->getRequestedTA()[i];
        if(closeFormResult[i]) {
            all_course_offers[current_course_offer]->addTA(ta_id);
            people[findPeopleIndexById(ta_id)]->addNotification(to_string(current_course_offer + 1) + SPACE + all_course_offers[current_course_offer]->getName() + ACCEPT_NOTIFICAION + END_LINE);
        }
        else {
            people[findPeopleIndexById(ta_id)]->addNotification(to_string(current_course_offer + 1) + SPACE + all_course_offers[current_course_offer]->getName() + REJECT_NOTIFICAION + END_LINE);
        }
    }
    all_course_offers[current_course_offer]->cleanTARequested();
    current_course_offer = INVALID;
    closeFormResult.clear();
    extra_output.clear();
}

void University::runAddProfile(string address) {
    if(!checkLogin()) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(user->getId() == ZERO_STRING) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else {
        user->addProfile(address);
    }
}

void University::runGetCourseChannel(string id) {
    if(!checkLogin()) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(user->getId() == ZERO_STRING) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(!isNumber(id)) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(stoi(id) == 0) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(stoi(id) >= course_offer_id) {
        throw runtime_error(NOT_FOUND);
    }
    else if(!all_course_offers[stoi(id) - 1]->isInCourse(user->getId())) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else {
        showOneCourseOffers(stoi(id) - 1);
        all_course_offers[stoi(id) - 1]->showPostsCourseChannel(output);
    }
}

void University::runCoursePost(string id = DEFINE_STRING, string title = DEFINE_STRING, string message = DEFINE_STRING, string image_address = DEFINE_STRING) {
    if(!checkLogin()) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(id == DEFINE_STRING || title == DEFINE_STRING || message == DEFINE_STRING) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(!isNumber(id)) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(stoi(id) == ZERO) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(stoi(id) >= course_offer_id) {
        throw runtime_error(NOT_FOUND);
    }
    else if(user->getPeopleType() == _STUDENT and !all_course_offers[stoi(id) - 1]->isTA(user->getId())) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(user->getPeopleType() == _PROFESSOR and !all_course_offers[stoi(id) - 1]->isProfessor(user->getId())) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(input_line.size() == COURSE_POST_MODE_SIZE_SECOND and image_address == DEFINE_STRING) {
        throw runtime_error(BAD_REQUEST);
    }
    else {
        if(image_address == DEFINE_STRING) image_address = NULL_STRING;
        all_course_offers[stoi(id) - 1]->addPost(title, message, image_address, user->getName(), _NORMAL, NULL_STRING, ZERO);
        addNotificationCoursePost(stoi(id) - 1, id + SPACE + all_course_offers[stoi(id) - 1]->getName() + COLON + SPACE + NEW_COURSE_POST + END_LINE);
       throw runtime_error(OK);

    }
}

void University::runGetPostCourseChannel(string id = NULL_STRING, string post_id = NULL_STRING) {
    if(!checkLogin()) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(user->getId() == ZERO_STRING) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(!isNumber(id) || !isNumber(post_id)) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(stoi(post_id) == ZERO || stoi(id) == ZERO) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(stoi(id) >= course_offer_id) {
        throw runtime_error(NOT_FOUND);
    }
    else if(!all_course_offers[stoi(id) - 1]->isInPost(stoi(post_id))) {
        throw runtime_error(NOT_FOUND);
    }
    else if(!all_course_offers[stoi(id) - 1]->isInCourse(user->getId())) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else {
        showOneCourseOffers(stoi(id) - 1);
        all_course_offers[stoi(id) - 1]->showOnePostCourseChannel(output, stoi(post_id));
    }
}

void University::runDeleteCourse(string id) {
    if(!checkLogin() || !isStudent()) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(!isNumber(id)) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(stoi(id) == 0) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(stoi(id) >= course_offer_id) {
        throw runtime_error(NOT_FOUND);
    }
    else if(!user->hasCourseOfferById(stoi(id))) {
        throw runtime_error(NOT_FOUND);
    }
    else {
        user->removeCourse(all_course_offers[stoi(id) - 1]->getCourseOfferId());
        user->shareNotification(user->getId() + SPACE + user->getName() + COLON + SPACE + NEW_DELETE_COURSE + END_LINE);
        throw runtime_error(OK);
    }
}

void University::runGetCourse() {
    if(!checkLogin()) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(user->getId() == ZERO_STRING) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if((int) all_course_offers.size() == 0) {
        throw runtime_error(EMPTY);
    }
    else {
        showAllCourseOffers();
    }
}

void University::runGetCourseById(string id) {
    if(!checkLogin()) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(user->getId() == ZERO_STRING) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(!isNumber(id)) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(stoi(id) == 0) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(stoi(id) >= course_offer_id) {
        throw runtime_error(NOT_FOUND);
    }
    else {
        showOneCourseOffers(stoi(id) - 1);
    }
}


void University::runConnect(string id) {
    if(!checkLogin()) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(user->getId() == ZERO_STRING) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(!isNumber(id)) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(!checkValidId(id)) {
        throw runtime_error(NOT_FOUND);
    }
    else if(stoi(id) == 0) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(user->inConnection(id)) {
        throw runtime_error(BAD_REQUEST);
    }
    else {
        user->addConnection(people[findPeopleIndexById(id)]);
        people[findPeopleIndexById(id)]->addConnection(user);
        throw runtime_error(OK);
    }
}

void University::runCloseTAForm(string id) {
    if(!checkLogin() || !isProfessor(user->getId())) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(!isNumber(id)) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(stoi(id) == 0) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(!user->isTAForm(stoi(id))) {
        throw runtime_error(NOT_FOUND);
    }
    else if(!all_course_offers[user->findCourseByPost(stoi(id)) - 1]->getOpenForm()) {
        throw runtime_error(NOT_FOUND);
    }
    else {
        askProfessorForTA(user->findCourseByPost(stoi(id)) - 1);
        user->removePost(stoi(id));
    }
}

void University::runGetMyCourse() {
    if(!checkLogin() || !isStudent()) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(user->numberOfCourses() == 0) {
        throw runtime_error(EMPTY);
    }
    else {
        user->showCourses(output, people);
    }
}

void University::runPutCourse(string id) {
    if(!checkLogin() || !isStudent()) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(!isNumber(id)) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(stoi(id) == ZERO) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(stoi(id) >= course_offer_id) {
        throw runtime_error(NOT_FOUND);
    }
    else if(user->getSemester() < all_course_offers[stoi(id) - 1]->getPrerequisite()) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(!all_course_offers[stoi(id) - 1]->hasMajor(user->getMajorId())) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(!user->validCourseTime(all_course_offers[stoi(id) - 1]->getTime()) || !user->validCourseDate(all_course_offers[stoi(id) - 1]->getExamTime()) ) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else {
        user->addCourse(all_course_offers[stoi(id) - 1]);
        all_course_offers[stoi(id) - 1]->addStudent(user->getId());
        user->shareNotification(user->getId() + SPACE + user->getName() + COLON + SPACE + NEW_GET_COURSE + END_LINE);
        throw runtime_error(OK);
    }
}

void University::runGetPost(string id = NULL_STRING, string post_id = NULL_STRING) {
    if(!checkLogin()) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(user->getId() == ZERO_STRING) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(!isNumber(id) || !isNumber(post_id)) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(stoi(post_id) == ZERO) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(!checkValidId(id) || !people[findPeopleIndexById(id)]->isInPost(stoi(post_id))) {
        throw runtime_error(NOT_FOUND);
    }
    else {
        people[findPeopleIndexById(id)]->getPost(output, stoi(post_id));
    }
}

void University::runShareCourse(string course_id, string professor_id, string capacity, string time, string exam_date, string class_number) {
    if(!checkLogin()) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(user->getId() != ZERO_STRING) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(!isNumber(course_id) || !isNumber(professor_id) || !isNumber(capacity) || !isNumber(class_number)) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(stoi(course_id) == ZERO || stoi(professor_id) == ZERO || stoi(capacity) == ZERO || stoi(class_number) == ZERO) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(!checkValidId(professor_id) || !checkValidCourse(course_id)) {
        throw runtime_error(NOT_FOUND);
    }
    else if(!isProfessor(professor_id)) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(!isPresentByProfessor(professor_id, course_id)) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(inCommonTime(professor_id, time)) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else {
        int professor_index = findPeopleIndexById(professor_id);
        Time new_time(time);
        Date new_date(exam_date);
        int course_index = findCourseIndexById(course_id);
        CourseOffer* new_course = new CourseOffer(course_offer_id, course_id, professor_id, stoi(capacity),
         new_time, new_date, stoi(class_number), courses[course_index]->getName(), courses[course_index]->getCredit(),
         courses[course_index]->getPrerequisite(), courses[course_index]->getMajorsId());
        people[professor_index]->addCourse(new_course);
        user->shareNotification(people[professor_index]->getId() + SPACE + people[professor_index]->getName() + COLON + SPACE + NEW_COURSE_OFFER + END_LINE);
        all_course_offers.push_back(new_course);
        course_offer_id++;
        throw runtime_error(OK);
    }
}

void University::runSharePost(string title, string message, string image_address = DEFINE_STRING) {
    if(!checkLogin()) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else {
        if(image_address == DEFINE_STRING) image_address = NULL_STRING;
        user->addPost(title, message, image_address, NULL_STRING, _NORMAL, NULL_STRING, 0);
        user->shareNotification(user->getId() + SPACE + user->getName() + COLON + SPACE + NEW_POST + END_LINE);
    }
}

void University::runPostTAForm(string course_id = DEFINE_STRING, string message = DEFINE_STRING) {
    if(!checkLogin() || !isProfessor(user->getId())) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(course_id == DEFINE_STRING || message == DEFINE_STRING) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(!isNumber(course_id)) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(stoi(course_id) == 0) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(stoi(course_id) >= course_offer_id) {
        throw runtime_error(NOT_FOUND);
    }
    else if(!user->hasCourseOfferById(stoi(course_id))) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else {
        all_course_offers[stoi(course_id) - 1]->changeStatusTAForm();
        user->addPost(TA_FORM_FOR + all_course_offers[stoi(course_id) - 1]->getName() + SPACE_COURSE, message,
         NULL_STRING, user->getName(), _TA_FORM, course_id + SPACE + all_course_offers[stoi(course_id) - 1]->getName() + SPACE  +
         to_string(all_course_offers[stoi(course_id) - 1]->getCapacity()) + SPACE + user->getName() + SPACE + all_course_offers[stoi(course_id) - 1]->getTime() + SPACE +
         all_course_offers[stoi(course_id) - 1]->getExamTime() + SPACE + to_string(all_course_offers[stoi(course_id) - 1]->getClassNumber()), stoi(course_id));
        user->shareNotification(user->getId() + SPACE + user->getName() + COLON + SPACE + NEW_FORM + END_LINE);
        throw runtime_error(OK);
    }
}

void University::runTARequest(string professor_id = DEFINE_STRING, string form_id = DEFINE_STRING) {
    if(!checkLogin() || !isStudent()) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(professor_id == DEFINE_STRING || form_id == DEFINE_STRING) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(!isNumber(form_id)) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(!isProfessor(professor_id)) {
        throw runtime_error(NOT_FOUND);
    }
    else if(stoi(form_id) == 0) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(!people[findPeopleIndexById(professor_id)]->isInPost(stoi(form_id))){
        throw runtime_error(NOT_FOUND);
    }
    else if(!people[findPeopleIndexById(professor_id)]->isTAForm(stoi(form_id))){
        throw runtime_error(NOT_FOUND);
    }
    else if(user->getSemester() <= all_course_offers[people[findPeopleIndexById(professor_id)]->findCourseByPost(stoi(form_id)) - 1]->getPrerequisite()) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else {
        all_course_offers[people[findPeopleIndexById(professor_id)]->findCourseByPost(stoi(form_id)) - 1]->addRequestedTA(user->getId());
        throw runtime_error(OK);
    }
}

void University::runRemovePost(string id) {
    if(!checkLogin()) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(!isNumber(id)) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(stoi(id) == ZERO) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(!user->isInPost(stoi(id))) {
        throw runtime_error(NOT_FOUND);
    }
    else {
        user->removePost(stoi(id));
        throw runtime_error(OK);
    }
}

void University::runPersonalPage(string id) {
    if(!checkLogin()) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(user->getId() == ZERO_STRING) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(!isNumber(id)) {
        throw runtime_error(BAD_REQUEST);
    }
    else if(!checkValidId(id)) {
        exit(0);
        throw runtime_error(NOT_FOUND);
    }
    else {
        people[findPeopleIndexById(id)]->personalPage(output);
    }
}

void University::runNotification(){
    if(!checkLogin()) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(user->getId() == ZERO_STRING) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(user->emptyNotification()) {
        throw runtime_error(EMPTY);
    }
    else {
        user->printNotification(output);
    }
}

void University::runLogout() {
    if(!checkLogin()) {
        cout << "\n\n\n\n\n\n\n\n\n";
        throw runtime_error(PERMISSION_DENIED);
    }
    else {
        user = nullptr;
    }
}

void University::runLogin(string id, string password) {
    if(user != nullptr) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else if(!checkValidId(id)) {
        throw runtime_error(NOT_FOUND);
    }
    else if(!checkValidPassword(id, password)) {
        throw runtime_error(PERMISSION_DENIED);
    }
    else {
        user = people[findPeopleIndexById(id)];
    }
}