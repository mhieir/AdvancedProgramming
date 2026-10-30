#pragma once
#ifndef HANDLERS_HPP_INCLUDE
#define HANDLERS_HPP_INCLUDE

#include "Global.hpp"
#include "server.hpp"
#include "University.hpp"

class LoginHandler : public RequestHandler {
public:
    LoginHandler(University *university);
    Response* callback(Request*) override;
private:
    University* university;
};

class LogoutHandler : public RequestHandler {
public:
    LogoutHandler(University *university);
    Response* callback(Request*) override;
private:
    University* university;
};

class PersonalPageHandler : public RequestHandler {
public:
    PersonalPageHandler(University *university);
    Response* callback(Request*) override;
private:
    University* university;
};

class GetCourseByIdHandler : public RequestHandler {
public:
    GetCourseByIdHandler(University *university);
    Response* callback(Request*) override;
private:
    University* university;
};

class GetAllCoursesHandler : public RequestHandler {
public:
    GetAllCoursesHandler(University *university);
    Response* callback(Request*) override;
private:
    University* university;
};

class PutCourseHandler : public RequestHandler {
public:
    PutCourseHandler(University *university);
    Response* callback(Request*) override;
private:
    University* university;
};

class DeleteCourseHandler : public RequestHandler {
public:
    DeleteCourseHandler(University *university);
    Response* callback(Request*) override;
private:
    University* university;
};

class SharePostHandler : public RequestHandler {
public:
    SharePostHandler(University *university);
    Response* callback(Request*) override;
private:
    University* university;
};

class ChangeProfileHandler : public RequestHandler {
public:
    ChangeProfileHandler(University *university, Server* server);
    Response* callback(Request*) override;
private:
    University* university;
    Server* server;
};

class MyCoursesHandler : public RequestHandler {
public:
    MyCoursesHandler(University *university);
    Response* callback(Request*) override;
private:
    University* university;
};

class CourseOfferHandler : public RequestHandler {
public:
    CourseOfferHandler(University *university);
    Response* callback(Request*) override;
private:
    University* university;
};

class BackHomeHandler : public RequestHandler {
public:
    BackHomeHandler(University *university);
    Response* callback(Request*) override;
private:
    University* university;
};


#endif // HANDLERS_HPP_INCLUDE

