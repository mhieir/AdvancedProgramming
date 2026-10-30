#include "handlers.hpp"
#include "DynamicHTML.hpp"

LoginHandler::LoginHandler(University *university): university(university) {}
LogoutHandler::LogoutHandler(University *university): university(university) {}
PersonalPageHandler::PersonalPageHandler(University *university): university(university) {}
GetCourseByIdHandler::GetCourseByIdHandler(University *university): university(university) {}
GetAllCoursesHandler::GetAllCoursesHandler(University *university): university(university) {}
PutCourseHandler::PutCourseHandler(University *university): university(university) {}
DeleteCourseHandler::DeleteCourseHandler(University *university): university(university) {}
SharePostHandler::SharePostHandler(University *university): university(university) {}
ChangeProfileHandler::ChangeProfileHandler(University *university, Server* server): server(server), university(university) {}
MyCoursesHandler::MyCoursesHandler(University *university): university(university) {}
CourseOfferHandler::CourseOfferHandler(University *university): university(university) {}
BackHomeHandler::BackHomeHandler(University *university): university(university) {}

Response* catchError(exception& e) {
    if(e.what() == OK) {
        Response* res = Response::redirect(OK_PAGE);
        return res;
    }
    else if(e.what() == PERMISSION_DENIED) {
        Response* res = Response::redirect(PERMISSION_DENIED_PAGE);
        return res;
    }
    else if(e.what() == BAD_REQUEST) {
        Response* res = Response::redirect(BAD_REQUEST_PAGE);
        return res;
    }
    else if(e.what() == EMPTY) {
        Response* res = Response::redirect(EMPTY_PAGE);
        return res;
    }
    else {
        Response* res = Response::redirect(NOT_FOUND_PAGE);
        return res;
    }
}

Response* findPeopleType(University* university, string username) {
    PeopleType people_type = university->peopleStatus(username);
    if(people_type == _STUDENT) {
        string body = studentPage(username, university);
        Response* res = new Response();
        res->setHeader(HTML_HEADER_FILE_FIRST, HTML_HEADER_FILE_SECOND);
        res->setBody(body);
        if(!university->checkLogin()) res->setSessionId(SID);
        return res;
    }
    else if(people_type == _PROFESSOR) {
        string body = professorPage(username, university);
        Response* res = new Response();
        res->setHeader(HTML_HEADER_FILE_FIRST, HTML_HEADER_FILE_SECOND);
        res->setBody(body);
        if(!university->checkLogin()) res->setSessionId(SID);
        return res;
    }
    else {
        string body = adminPage(username, university);
        Response* res = new Response();
        res->setHeader(HTML_HEADER_FILE_FIRST, HTML_HEADER_FILE_SECOND);
        res->setBody(body);
        if(!university->checkLogin()) res->setSessionId(SID);
        return res;
    }
}

Response* LoginHandler::callback(Request* req) {
    try {
        string username = req->getBodyParam(USERNAME);
        string password = req->getBodyParam(PASSWORD);
        university->runLogin(username, password);
        return findPeopleType(university, username);
    }
    catch (runtime_error& e) {
        return catchError(e);
    }
}

Response* LogoutHandler::callback(Request* req) {
    try {
        university->runLogout();
        Response* res = Response::redirect(HOME_PAGE);
        return res;
    }
    catch (runtime_error& e) {
        return catchError(e);
    }
}

Response* PersonalPageHandler::callback(Request* req) {
    try {
        string username = req->getBodyParam(ID);
        university->runPersonalPage(username);
        vector<string> output = university->getOutput();
        string body = showPersonalPage(university, output, university->peopleStatus(username));
        Response* res = new Response();
        res->setHeader(HTML_HEADER_FILE_FIRST, HTML_HEADER_FILE_SECOND);
        res->setBody(body);
        return res;
    }
    catch (runtime_error& e) {
        return catchError(e);
    }
}

Response* GetCourseByIdHandler::callback(Request* req) {
    try {
        string id = req->getBodyParam(ID);
        university->runGetCourseById(id);
        vector<string> output = university->getOutput();
        string body = showOneCourse(output);
        Response* res = new Response();
        res->setHeader(HTML_HEADER_FILE_FIRST, HTML_HEADER_FILE_SECOND);
        res->setBody(body);
        return res;
    }
    catch (runtime_error& e) {
        return catchError(e);
    }
}

Response* GetAllCoursesHandler::callback(Request* req) {
    try {
        university->runGetCourse();
        vector<string> output = university->getOutput();
        string body = showAllCourse(output);
        Response* res = new Response();
        res->setHeader(HTML_HEADER_FILE_FIRST, HTML_HEADER_FILE_SECOND);
        res->setBody(body);
        return res;
    }
    catch (runtime_error& e) {
        return catchError(e);
    }
}

Response* PutCourseHandler::callback(Request* req) {
    try {
        string id = req->getBodyParam(ID);
        university->runPutCourse(id);
        Response* res = Response::redirect(OK_PAGE);
        return res;
    }
    catch (runtime_error& e) {
        return catchError(e);
    }
}

Response* DeleteCourseHandler::callback(Request* req) {
    try {
        string id = req->getBodyParam(ID);
        university->runDeleteCourse(id);
        Response* res = Response::redirect(OK_PAGE);
        return res;
    }
    catch (runtime_error& e) {
        return catchError(e);
    }
}

Response* SharePostHandler::callback(Request* req) {
    try {
        string title = req->getBodyParam(TITLE);
        string message = req->getBodyParam(MESSAGE);
        string file_name = req->getBodyParam(FILE_NAME);
        university->runSharePost(title, message, file_name + PNG);
        Response* res = Response::redirect(HOME_PAGE);
        return res;
    }
    catch (runtime_error& e) {
        return catchError(e);
    }
}

Response* ChangeProfileHandler::callback(Request* req) {
    try {
        string file_name = req->getBodyParam(FILE_NAME) + PNG;
        string file = req->getBodyParam(FILE_TITLE);
        utils::writeToFile(file, "./static/" + file_name);
        server->get("/" + file_name, new ShowImage("static/" + file_name));
        university->runAddProfile(file_name);
        Response* res = Response::redirect(HOME_PAGE);
        return res;
    }
    catch (runtime_error& e) {
        return catchError(e);
    }
}

Response* MyCoursesHandler::callback(Request* req) {
    try {
        university->runGetMyCourse();
        vector<string> output = university->getOutput();
        string body = showMyCourse(output);
        Response* res = new Response();
        res->setHeader(HTML_HEADER_FILE_FIRST, HTML_HEADER_FILE_SECOND);
        res->setBody(body);
        return res;
    }
    catch (runtime_error& e) {
        return catchError(e);
    }
}

Response* CourseOfferHandler::callback(Request* req) {
    try {
        string course_id = req->getBodyParam(COURSE_ID);
        string professor_id = req->getBodyParam(PROFESSOR_ID);
        string capacity = req->getBodyParam(CAPACITY);
        string time = req->getBodyParam(TIME);
        string exam_date = req->getBodyParam(EXAM_DATE);
        string class_number = req->getBodyParam(CLASS_NUMBER);
        university->runShareCourse(course_id, professor_id, capacity, time, exam_date, class_number);
        Response* res = Response::redirect(HOME_PAGE);
        return res;
    }
    catch (runtime_error& e) {
        return catchError(e);
    }
}

Response* BackHomeHandler::callback(Request* req) {
    if(university->checkLogin()) {
        return findPeopleType(university, university->getUserId());
    }
    else {
        Response* res = Response::redirect(LOGIN_PAGE);
        return res;
    }
}