#pragma once
// in God we trust
#ifndef GLOBAL_INCLUDE
#define GLOBAL_INCLUDE

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <map>
#include <cstring>

using namespace std;

enum PostType {
    _NORMAL,
    _TA_FORM
};

enum PeopleType {
    _UTACCOUNT,
    _STUDENT,
    _PROFESSOR
};

const string COURSE_CHANNEL = "course_channel";
const string SHOW_SERVER_PORT = "Server running on port: ";
const string NULL_STRING = "";
const string CLOSE_TA_FORM = "close_ta_form";
const string DEFINE_STRING = "-1";
const string UT_ACCOUNT = "UT_account";
const string NEW_COURSE_POST = "New Course Post";
const string TA_FORM = "ta_form";
const string UT_ACCOUNT_PASSWORD = "UT_account";
const string OK = "OK";
const string EMPTY = "Empty";
const string QUESTION_MARK = "?";
const string GET = "GET";
const string POST = "POST";
const string DELETE = "DELETE";
const string PUT = "PUT";
const string LOGIN = "login";
const string ACCEPT = "accept";
const string REJECT = "reject";
const string LOGOUT = "logout";
const string ID = "id";
const string FILE_NAME = "file_name";
const string FILE_TITLE = "file";
const string PASSWORD = "password";
const string COURSES = "courses";
const string LITTLE_POST = "post";
const string SID = "SID";
const string USERNAME = "username";
const string TITLE = "title";
const string NEW_FORM = "New Form";
const string SPACE_COURSE = " course";
const string TA_FORM_FOR = "TA form for ";
const string MESSAGE = "message";
const string PERSONAL_PAGE = "personal_page";
const string POST_ID = "post_id";
const string CONNECT = "connect";
const string NOTIFICATION = "notification";
const string COURSE_OFFER = "course_offer";
const string COURSE_ID = "course_id";
const string PROFILE_PHOTO = "profile_photo";
const string PNG = ".png";
const string HOME_PAGE = "/";
const string LOGOUT_PAGE = "/logout";
const string BACK_HOME_PAGE = "/backHome";
const string GET_COURSE_BY_ID_PAGE = "/getCourseById";
const string PUT_COURSE_PAGE = "/putCourse";
const string DELETE_COURSE_PAGE = "/deleteCourse";
const string ALL_COURSES_PAGE = "/allCourses";
const string PERSONAL_PAGE_PAGE = "/personalPage";
const string SHARE_POST_PAGE = "/sharePost";
const string CHANGE_PROFILE_PAGE = "/changeProfile";
const string MY_COURSE_PAGE = "/myCourses";
const string COURSE_OFFER_PAGE = "/courseOffer";
const string STATIC_HOME = "static/home.html";
const string STATIC_404 = "static/404.html";
const string STATIC_1 = "static/1.png";
const string STATIC_HOME_PNG = "static/home.png";
const string STATIC_LOGIN = "static/logincss.html";
const string STATIC_NOT_FOUND = "static/notFound.html";
const string STATIC_BAD_REQUEST = "static/badRequest.html";
const string STATIC_PERMISSION_DENIED = "static/permissionDenied.html";
const string STATIC_EMPTY = "static/Empty.html";
const string STATIC_SHARE_POST = "static/sharePost.html";
const string STATIC_CHANGE_PROFILE = "static/changeProfile.html";
const string STATIC_OK = "static/ok.html";
const string HOME_PNG = "/home.png";
const string HOME_1 = "/1.png";
const string PROFESSOR_ID = "professor_id";
const string CAPACITY = "capacity";
const string TIME = "time";
const string EXAM_DATE = "exam_date";
const string CLASS_NUMBER = "class_number";
const string MY_COURSES = "my_courses";
const string NOT_FOUND = "Not Found";
const string BAD_REQUEST = "Bad Request";
const string PERMISSION_DENIED = "Permission Denied";
const string ZERO_STRING = "0";
const string NEW_POST = "New Post";
const string NEW_COURSE_OFFER = "New Course Offering";
const string NEW_GET_COURSE = "Get Course";
const string NEW_DELETE_COURSE = "Delete Course";
const string END_LINE = "\n";
const string IMAGE = "image";
const string PHOTO = "photo";
const string TA_FORM_FIRST = "We have received ";
const string TA_FORM_SECOND = "requests for the teaching assistant position";
const string FORM_ID = "form_id";
const string HTML_HEADER_FILE_FIRST = "Content-Type";
const string HTML_HEADER_FILE_SECOND = "text/html";
const string TA_REQUEST = "ta_request";
const string COURSE_POST = "course_post";
const string OK_PAGE = "/ok";
const string PERMISSION_DENIED_PAGE = "/permissionDenied";
const string BAD_REQUEST_PAGE = "/badRequest";
const string EMPTY_PAGE = "/empty";
const string NOT_FOUND_PAGE = "/notFound";
const string LOGIN_PAGE = "/login";
const string ACCEPT_NOTIFICAION = ": Your request to be a teaching assistant has been accepted.";
const string REJECT_NOTIFICAION = ": Your request to be a teaching assistant has been rejected.";
const char COMMA = ',';
const char DOT = '.';
const char SLASH = '/';
const char COLON = ':';
const char SEMI_COLON = ';';
const char SPACE = ' ';
const char DASH = '-';
const char QUOTION = '\"';
const int MAX_CHAR = 500;
const int LOGGED_OUT = -1;
const int INVALID = -1;
const int ZERO = 0;
const int MIN_INPUT_SIZE = 2;
const int LOGIN_MODE_SIZE = 7;
const int START_ID = 1;
const int LOGOUT_MODE_SIZE = 3;
const int CONNECT_MODE_SIZE = 5;
const int SHARE_POST_MODE_SIZE_FIRST = 7;
const int SHARE_POST_MODE_SIZE_SECOND = 9;
const int REMOVE_POST_MODE_SIZE = 5;
const int PERSONAL_PAGE_MODE_SIZE = 5;
const int GET_POST_MODE_SIZE = 7;
const int SHARE_COURSE_MODE_SIZE = 15;
const int GET_COURSE_MODE_SIZE_FIRST = 3;
const int GET_COURSE_MODE_SIZE_SECOND = 5;
const int COURSE_POST_MODE_SIZE_FIRST = 9;
const int COURSE_POST_MODE_SIZE_SECOND = 11;
const int PUT_COURSE_MODE_SIZE = 5;
const int GET_MY_COURSE_MODE_SIZE = 3;
const int ADD_PROFILE_MODE_SIZE = 5;
const int NOTIFICATION_MODE_SIZE = 3;
const int POST_TA_FORM_MODE_SIZE = 7;
const int CLOSE_TA_FORM_MODE_SIZE = 5;
const int TA_REQUEST_MODE_SIZE = 7;
const int GET_COURSE_CHANNEL_SIZE = 5;
const int GET_COURSE_POST_SIZE = 7;

#endif