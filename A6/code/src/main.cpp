#include "Global.hpp"
#include "University.hpp"
#include "server.hpp"
#include "handlers.hpp"

void mapServerPaths(Server* server, University* university) {
    server->setNotFoundErrPage(STATIC_404);
    server->get(HOME_PAGE, new ShowPage(STATIC_HOME));
    server->get(HOME_PNG, new ShowImage(STATIC_HOME_PNG));
    server->get(HOME_1, new ShowImage(STATIC_1));
    server->get(LOGIN_PAGE, new ShowPage(STATIC_LOGIN));
    server->post(LOGIN_PAGE, new LoginHandler(university));
    server->post(LOGOUT_PAGE, new LogoutHandler(university));
    server->post(GET_COURSE_BY_ID_PAGE, new GetCourseByIdHandler(university));
    server->post(PUT_COURSE_PAGE, new PutCourseHandler(university));
    server->post(DELETE_COURSE_PAGE, new DeleteCourseHandler(university));
    server->post(ALL_COURSES_PAGE, new GetAllCoursesHandler(university));
    server->post(PERSONAL_PAGE_PAGE, new PersonalPageHandler(university));
    server->get(NOT_FOUND_PAGE, new ShowPage(STATIC_NOT_FOUND));
    server->get(BAD_REQUEST_PAGE, new ShowPage(STATIC_BAD_REQUEST));
    server->get(PERMISSION_DENIED_PAGE, new ShowPage(STATIC_PERMISSION_DENIED));
    server->get(EMPTY_PAGE, new ShowPage(STATIC_EMPTY));
    server->get(SHARE_POST_PAGE, new ShowPage(STATIC_SHARE_POST));
    server->post(SHARE_POST_PAGE, new SharePostHandler(university));
    server->get(CHANGE_PROFILE_PAGE, new ShowPage(STATIC_CHANGE_PROFILE));
    server->post(CHANGE_PROFILE_PAGE, new ChangeProfileHandler(university, server));
    server->post(MY_COURSE_PAGE, new MyCoursesHandler(university));
    server->post(COURSE_OFFER_PAGE, new CourseOfferHandler(university));
    server->get(OK_PAGE, new ShowPage(STATIC_OK));
    server->post(BACK_HOME_PAGE, new BackHomeHandler(university));
}

int main(int argc, char *argv[]){
    int port = 8080;
    Server* server = new Server(port);
    University* university = new University(argv);
    mapServerPaths(server, university);
    cout << SHOW_SERVER_PORT << port << endl;
    server->run();
}