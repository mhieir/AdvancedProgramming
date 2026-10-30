#include "Global.hpp"
#include "University.hpp"

string studentPage(string username, University* university) {
    string body;
    body += "<!DOCTYPE html>";
    body += "<html lang='en'>";
    body += "<head>";
    body += "<meta charset='UTF-8'>";
    body += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    body += "<title>Logout Page</title>";
	body += "<style>";
	body += "body{background-color: rgba(215, 238, 236, 0.934);font-family: fantasy;text-align: center;padding: 0;border: 0;}";
    body += ".info{margin-top: 30px;display: flex;width: 100%;}";
    body += ".Uni_pic{width: 60%;height: 250px;border-style:solid;border-width: 5px;border-color: rgb(97, 82, 58);}";
    body += ".image_part{width: 40%;}";
    body += ".info_part {width: 70%;font-size: 28px;height: 60px;}";
    body += ".info_part_object {width: 80%;margin-left: 10%;background-color: rgba(241, 204, 149, 0.804);margin-bottom: 25px;text-align: left;padding-left: 15px;border-style:solid;border-width: 1px;border-color: rgb(97, 82, 58);}";
    body += "#title_info_part{font-style:italic;font-weight: bold;}";
    body += "hr.new4 {margin-top: 30px;border: 2px solid rgb(97, 82, 58);}";
    body += "hr.new5 {margin-top: 6px;border: 2px solid rgb(97, 82, 58);}";
    body += ".options_in_student{display: flex;}";
    body += ".object_in_options_student{width: 41%;margin-top: 30px;height: 60px;font-size: 25px;padding-top: 20px;margin-left: 6%;background-color: rgb(97, 82, 58);color: aliceblue;}";
    body += ".object_in_options_student_last{width: 41%;margin-top: 30px;height: 60px;font-size: 25px;padding-top: 20px;margin-left: 29.5%;background-color: rgb(97, 82, 58);color: aliceblue;}";
    body += ".submit_class{width: 100%;height: 100px;}";
    body += ".logout_key{height: 40px;border: none;font-family: fantasy;font-size: 25px;color: aliceblue;background-color: rgb(97, 82, 58);}";
    body += ".submit_class{width: 10%;margin-left: 45%;margin-right: 45%;margin-top: 5px;height: 30px;}";
    body += "#show_course {display:none;height: 70px;width: 100%;padding: 10px;margin-top: 10px;text-align: center;background-color: rgba(241, 204, 149, 0.804);}";
    body += "#put_id {display:none;height: 70px;width: 100%;padding: 10px;margin-top: 10px;text-align: center;background-color: rgba(241, 204, 149, 0.804);}";
    body += "#delete_id {display:none;height: 70px;width: 100%;padding: 10px;margin-top: 10px;text-align: center;background-color: rgba(241, 204, 149, 0.804);}";
    body += "#personal_id {display:none;height: 70px;width: 100%;padding: 10px;margin-top: 10px;text-align: center;background-color: rgba(241, 204, 149, 0.804);}";
    body += ".options_class{width: 20%;margin-left: 40%;margin-right: 40%;height: 20px;margin-top: 7px;}";
    body += "</style>";
    body += "</head>";
    body += "<body>";
    body += "<div class='info'><div class='image_part'><img src='" + university->getUserProfile() + "' class='Uni_pic' alt='Home Logo'></div><div class='info_part'><div id='title_info_part'>information</div><div class='info_part_object'>Name : " + university->getUserName() + "</div><div class='info_part_object'>Id : " + university->getUserId() + "</div><div class='info_part_object'>Major : " +  university->getUserMajor() + "</div></div></div>";
    body += "<hr class='new4'><hr class='new5'><hr class='new5'>";
    body += "<div class='options_in_student'><div class='object_in_options_student'><button class='logout_key' onclick='showFunction()'>Show course by id</button></div><form class='object_in_options_student' action='/allCourses' method='post' ><input type='submit' class='logout_key' value='Show all courses'></form></div>";
    body += "<div id='show_course'><section class='login_form'><form action='/getCourseById' method='post'><input name='id' type='text' placeholder='Id' class='options_class'><input type='submit' class='submit_class' value='click'></form></section></div>";
    body += "<div class='options_in_student'><div class='object_in_options_student'><button class='logout_key' onclick='putFunction()'>Put course</button></div><div class='object_in_options_student'><button class='logout_key' onclick='deleteFunction()'>Delete course</button></div></div>";
    body += "<div id='put_id'><section class='login_form'><form action='/putCourse' method='post'><input name='id' type='text' placeholder='Id' class='options_class'><input type='submit' class='submit_class' value='click'></form></section></div>";
    body += "<div id='delete_id'><section class='login_form'><form action='/deleteCourse' method='post'><input name='id' type='text' placeholder='Id' class='options_class'><input type='submit' class='submit_class' value='click'></form></section></div>";
    body += "<div class='options_in_student'><div class='object_in_options_student'><a href='changeProfile'>Change profile</a></div><div class='object_in_options_student'><button class='logout_key' onclick='personalFunction()'>Show personal page</button></div></div>";
    body += "<div id='personal_id'><section class='login_form'><form action='/personalPage' method='post'><input name='id' type='text' placeholder='Id' class='options_class'><input type='submit' class='submit_class' value='click'></form></section></div>";
    body += "<div class='options_in_student'><div class='object_in_options_student'><a href='sharePost'>Share post</a></div><form class='object_in_options_student' action='/myCourses' method='post' ><input type='submit' class='logout_key' value='Show my courses'></form></div>";
    body += "<div class='options_in_student'><form class='object_in_options_student_last' action='/logout' method='post' ><input type='submit' class='logout_key' value='Logout'></form></div>";
    body += "<script>";
    body += "function showFunction() {var x = document.getElementById('show_course');if (x.style.display === 'none') {x.style.display = 'block';} else {x.style.display = 'none';}}";
    body += "function putFunction() {var x = document.getElementById('put_id');if (x.style.display === 'none') {x.style.display = 'block';} else {x.style.display = 'none';}}";
    body += "function deleteFunction() {var x = document.getElementById('delete_id');if (x.style.display === 'none') {x.style.display = 'block';} else {x.style.display = 'none';}}";
    body += "function personalFunction() {var x = document.getElementById('personal_id');if (x.style.display === 'none') {x.style.display = 'block';} else {x.style.display = 'none';}}";

    body += "</script>";

    body += "</body>";
    body += "</html>";

    return body;
}

string professorPage(string username, University* university) {
    string body;
    body += "<!DOCTYPE html>";
    body += "<html lang='en'>";
    body += "<head>";
    body += "<meta charset='UTF-8'>";
    body += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    body += "<title>Logout Page</title>";
	body += "<style>";
	body += "body{background-color: rgba(215, 238, 236, 0.934);font-family: fantasy;text-align: center;padding: 0;border: 0;}";
    body += ".info{margin-top: 30px;display: flex;width: 100%;}";
    body += ".Uni_pic{width: 60%;height: 250px;border-style:solid;border-width: 5px;border-color: rgb(97, 82, 58);}";
    body += ".image_part{width: 40%;}";
    body += ".info_part {width: 70%;font-size: 28px;height: 60px;}";
    body += ".info_part_object {width: 80%;margin-left: 10%;background-color: rgba(241, 204, 149, 0.804);margin-bottom: 25px;text-align: left;padding-left: 15px;border-style:solid;border-width: 1px;border-color: rgb(97, 82, 58);}";
    body += "#title_info_part{font-style:italic;font-weight: bold;}";
    body += "hr.new4 {margin-top: 30px;border: 2px solid rgb(97, 82, 58);}";
    body += "hr.new5 {margin-top: 6px;border: 2px solid rgb(97, 82, 58);}";
    body += ".options_in_student{display: flex;}";
    body += ".object_in_options_student{width: 41%;margin-top: 30px;height: 60px;font-size: 25px;padding-top: 20px;margin-left: 6%;background-color: rgb(97, 82, 58);color: aliceblue;}";
    body += ".submit_class{width: 100%;height: 100px;}";
    body += ".logout_key{height: 40px;border: none;font-family: fantasy;font-size: 25px;color: aliceblue;background-color: rgb(97, 82, 58);}";
    body += ".submit_class{width: 10%;margin-left: 45%;margin-right: 45%;margin-top: 5px;height: 30px;}";
    body += "#show_course {display:none;height: 70px;width: 100%;padding: 10px;margin-top: 10px;text-align: center;background-color: rgba(241, 204, 149, 0.804);}";
    body += "#personal_id {display:none;height: 700px;width: 100%;padding: 10px;margin-top: 10px;text-align: center;background-color: rgba(241, 204, 149, 0.804);}";
    body += ".options_class{width: 20%;margin-left: 40%;margin-right: 40%;height: 20px;margin-top: 7px;}";
    body += "</style>";
    body += "</head>";
    body += "<body>";
    body += "<div class='info'><div class='image_part'><img src='" + university->getUserProfile() + "' class='Uni_pic' alt='Home Logo'></div><div class='info_part'><div id='title_info_part'>information</div><div class='info_part_object'>Name : " + university->getUserName() + "</div><div class='info_part_object'>Id : " + university->getUserId() + "</div><div class='info_part_object'>Major : " +  university->getUserMajor() + "</div></div></div>";
    body += "<hr class='new4'><hr class='new5'><hr class='new5'>";
    body += "<div class='options_in_student'><div class='object_in_options_student'><button class='logout_key' onclick='showFunction()'>Show course by id</button></div><form class='object_in_options_student' action='/allCourses' method='post' ><input type='submit' class='logout_key' value='Show all courses'></form></div>";
    body += "<div id='show_course'><section class='login_form'><form action='/getCourseById' method='post'><input name='id' type='text' placeholder='Id' class='options_class'><input type='submit' class='submit_class' value='click'></form></section></div>";
    body += "<div class='options_in_student'><div class='object_in_options_student'><a href='changeProfile'>Change profile</a></div><div class='object_in_options_student'><button class='logout_key' onclick='personalFunction()'>Show personal page</button></div></div>";
    body += "<div id='personal_id'><section class='login_form'><form action='/personalPage' method='post'><input name='id' type='text' placeholder='Id' class='options_class'><input type='submit' class='submit_class' value='click'></form></section></div>";
    body += "<div class='options_in_student'><div class='object_in_options_student'><a href='sharePost'>Share post</a></div><form class='object_in_options_student' action='/logout' method='post' ><input type='submit' class='logout_key' value='Logout'></form></div>";

    body += "<script>";
    body += "function showFunction() {var x = document.getElementById('show_course');if (x.style.display === 'none') {x.style.display = 'block';} else {x.style.display = 'none';}}";
    body += "function personalFunction() {var x = document.getElementById('personal_id');if (x.style.display === 'none') {x.style.display = 'block';} else {x.style.display = 'none';}}";

    body += "</script>";

    body += "</body>";
    body += "</html>";

    return body;
}


string showOneCourse(vector<string> output) {
    string body;
    body += "<!DOCTYPE html>";
    body += "<html lang='en'>";
    body += "<head>";
    body += "<meta charset='UTF-8'>";
    body += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    body += "<title>Show Course By Id</title>";
    body += "<style>";
    body += "body{background-color: rgba(215, 238, 236, 0.934);font-family: fantasy;text-align: center;padding: 0;border: 0;}";
    body += ".top_of_page{width: 100%;height: 100px;}";
    body += ".course_info_text{width: 50%;margin-left: 25%;height: 70px;margin-top: 30px;font-size: 35px;padding-top: 20px;background-color:  rgba(215, 238, 236, 0.934);border-style: solid;border-color: rgb(97, 82, 58);border-width: 7px;}";
    body += "hr.new4 {margin-top: 30px;border: 2px solid rgb(97, 82, 58);}";
    body += ".class_info {display: flex;width: 100%;height: 100px;}";
    body += ".info_name{width: 20%;height: 50px;background-color: rgb(97, 82, 58);color:aliceblue;padding-top: 20px;font-size: 20px;margin-top: 20px;margin-left: 3%;}";
    body += ".info_value{width: 70%;height: 50px;margin-left: 5%;background-color: rgb(97, 82, 58);color:aliceblue;padding-top: 20px;font-size: 20px;margin-top: 20px;}";
    body += "</style>";
    body += "</head>";
    body += "<body>";
    body += "<div class='top_of_page'><div class='course_info_text'>Course information</div></div>";
    body += "<hr class='new4'>";
    body += "<div class='class_info'><div class='info_name'>Id </div><div class='info_value'>" + output[0] + "</div></div>";
    body += "<div class='class_info'><div class='info_name'>Name </div><div class='info_value'>"+ output[1] +"</div></div>";
    body += "<div class='class_info'><div class='info_name'>Capacity </div><div class='info_value'>" + output[2] + "</div></div>";
    body += "<div class='class_info'><div class='info_name'>Professor </div><div class='info_value'>" + output[3] + "</div></div>";
    body += "<div class='class_info'><div class='info_name'>Time </div><div class='info_value'>" + output[4] + "</div></div>";
    body += "<div class='class_info'><div class='info_name'>Exam date </div><div class='info_value'>" + output[5] + "</div></div>";
    body += "<div class='class_info'><div class='info_name'>Class number </div><div class='info_value'>" + output[6] + "</div></div>";
    body += "</body>";
    body += "</html>";

    return body;
}

string showAllCourse(vector<string> output) {
    string body;
    body += "<!DOCTYPE html>";
    body += "<html lang='en'>";
    body += "<head>";
    body += "<meta charset='UTF-8'>";
    body += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    body += "<title>Show Course By Id</title>";
    body += "<style>";
    body += "body{background-color: rgba(215, 238, 236, 0.934);font-family: fantasy;text-align: center;padding: 0;border: 0;}";
    body += ".top_of_page{width: 100%;height: 100px;}";
    body += ".course_info_text{width: 50%;margin-left: 25%;height: 70px;margin-top: 30px;font-size: 35px;padding-top: 20px;background-color:  rgba(215, 238, 236, 0.934);border-style: solid;border-color: rgb(97, 82, 58);border-width: 7px;}";
    body += "hr.new4 {margin-top: 30px;border: 2px solid rgb(97, 82, 58);}";
    body += ".class_info {display: flex;width: 100%;height: 100px;}";
    body += ".info_name{width: 20%;height: 50px;background-color: rgb(97, 82, 58);color:aliceblue;padding-top: 20px;font-size: 20px;margin-top: 20px;margin-left: 3%;}";
    body += ".info_value{width: 70%;height: 50px;margin-left: 5%;background-color: rgb(97, 82, 58);color:aliceblue;padding-top: 20px;font-size: 20px;margin-top: 20px;}";
    body += "</style>";
    body += "</head>";
    body += "<body>";
    body += "<div class='top_of_page'><div class='course_info_text'>All courses information</div></div>";
    body += "<hr class='new4'>";
    for(int i = 0; i < output.size(); i += 4) {
        body += "<div class='class_info'><div class='info_name'>Id </div><div class='info_value'>" + output[i] + "</div></div>";
        body += "<div class='class_info'><div class='info_name'>Name </div><div class='info_value'>"+ output[i + 1] +"</div></div>";
        body += "<div class='class_info'><div class='info_name'>Capacity </div><div class='info_value'>" + output[i + 2] + "</div></div>";
        body += "<div class='class_info'><div class='info_name'>Professor </div><div class='info_value'>" + output[i + 3] + "</div></div>";
        body += "<hr class='new4'>";
        body += "<hr class='new4'>";
        body += "<hr class='new4'>";
    }

    body += "</body>";
    body += "</html>";

    return body;
}

string showPersonalPage(University* university, vector<string> output, PeopleType people_type) {
    string body;
    body += "<!DOCTYPE html>";
    body += "<html lang='en'>";
    body += "<head>";
    body += "<meta charset='UTF-8'>";
    body += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    body += "<title>Show Course By Id</title>";
    body += "<style>";
    body += "body{background-color: rgba(241, 204, 149, 0.804);font-family: fantasy;text-align: center;padding: 0;border: 0;}";
    body += ".top_page{width:100%;height:60px;}";
    body += "hr.new4 {margin-top: 30px;border: 2px solid rgb(97, 82, 58);}";
    body += "hr.new5 {margin-top: 6px;border: 2px solid rgb(97, 82, 58);}";
    body += ".person_info{display:flex; width:100%; height:100px;}";
    body += ".objects{width:24%; margin-left:7%; height:60px; background-color:rgba(215, 238, 236, 0.934); margin-top:20px; font-size:25px; padding-top: 30px;}";
    body += ".course_title{width:20%; margin-left:7%;height:60px; background-color:rgb(97, 82, 58);margin-top:20px; font-size:25px; padding-top: 30px;color:aliceblue;}";
    body += ".all_courses{width:59%; margin-left:7%;height:60px; background-color:rgb(97, 82, 58);margin-top:20px; font-size:25px; padding-top: 30px;color:aliceblue;}";
    body += ".ut_title{width:40%; margin-left:30%; height:60px; background-color:rgba(215, 238, 236, 0.934); margin-top:20px; font-size:25px; padding-top: 30px;}";
    body += "</style>";
    body += "</head>";

    int counter = 0;
    if(people_type == _UTACCOUNT) {
        body += "<div class='top_page'><div class='ut_title'>UT Admin</div></div>";
        body += "<hr class='new4'><hr class='new5'>";
        counter = 1;
    }
    else {
        body += "<div class='person_info'><div class='objects'>" + output[0] + "</div><div class='objects'>" + output[1] + "</div><div class='objects'>" + output[2] + "</div></div>";
        body += "<hr class='new4'><hr class='new5'>";
        body += "<div class='person_info'><div class='course_title'>Courses</div><div class='all_courses'>" + output[3] + "</div></div>";
        body += "<hr class='new4'><hr class='new5'>";
        counter = 4;
    }

    for(int i = counter; i < output.size(); i += 2) {
        body += "<div class='person_info'><div class='course_title'>" + output[i] + "</div><div class='all_courses'>" + output[i + 1] + "</div></div>";
        body += "<hr class='new4'>";
    }

    body += "</body>";
    body += "</html>";

    return body;
}


string showMyCourse(vector<string> output) {
    string body;
    body += "<!DOCTYPE html>";
    body += "<html lang='en'>";
    body += "<head>";
    body += "<meta charset='UTF-8'>";
    body += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    body += "<title>Show Course By Id</title>";
    body += "<style>";
    body += "body{background-color: rgba(215, 238, 236, 0.934);font-family: fantasy;text-align: center;padding: 0;border: 0;}";
    body += ".top_of_page{width: 100%;height: 100px;}";
    body += ".course_info_text{width: 50%;margin-left: 25%;height: 70px;margin-top: 30px;font-size: 35px;padding-top: 20px;background-color:  rgba(215, 238, 236, 0.934);border-style: solid;border-color: rgb(97, 82, 58);border-width: 7px;}";
    body += "hr.new4 {margin-top: 30px;border: 2px solid rgb(97, 82, 58);}";
    body += ".class_info {display: flex;width: 100%;height: 100px;}";
    body += ".info_name{width: 20%;height: 50px;background-color: rgb(97, 82, 58);color:aliceblue;padding-top: 20px;font-size: 20px;margin-top: 20px;margin-left: 3%;}";
    body += ".info_value{width: 70%;height: 50px;margin-left: 5%;background-color: rgb(97, 82, 58);color:aliceblue;padding-top: 20px;font-size: 20px;margin-top: 20px;}";
    body += "</style>";
    body += "</head>";
    body += "<body>";
    body += "<div class='top_of_page'><div class='course_info_text'>My courses information</div></div>";
    body += "<hr class='new4'>";
    for(int i = 0; i < output.size(); i += 7) {
        body += "<div class='class_info'><div class='info_name'>Id </div><div class='info_value'>" + output[i] + "</div></div>";
        body += "<div class='class_info'><div class='info_name'>Name </div><div class='info_value'>"+ output[i + 1] +"</div></div>";
        body += "<div class='class_info'><div class='info_name'>Capacity </div><div class='info_value'>" + output[i + 2] + "</div></div>";
        body += "<div class='class_info'><div class='info_name'>Professor </div><div class='info_value'>" + output[i + 3] + "</div></div>";
        body += "<div class='class_info'><div class='info_name'>Time </div><div class='info_value'>"+ output[i + 4] +"</div></div>";
        body += "<div class='class_info'><div class='info_name'>Exam date </div><div class='info_value'>" + output[i + 5] + "</div></div>";
        body += "<div class='class_info'><div class='info_name'>Class number </div><div class='info_value'>" + output[i + 6] + "</div></div>";
        body += "<hr class='new4'>";
        body += "<hr class='new4'>";
        body += "<hr class='new4'>";
    }

    body += "</body>";
    body += "</html>";

    return body;
}


string adminPage(string username, University* university) {
    string body;
    body += "<!DOCTYPE html>";
    body += "<html lang='en'>";
    body += "<head>";
    body += "<meta charset='UTF-8'>";
    body += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    body += "<title>Logout Page</title>";
	body += "<style>";
    body += ".object_in_options_student_last{width: 41%;margin-top: 30px;height: 60px;font-size: 25px;padding-top: 20px;margin-left: 29.5%;background-color: rgb(97, 82, 58);color: aliceblue;}";
	body += "body{background-color: rgba(215, 238, 236, 0.934);font-family: fantasy;text-align: center;padding: 0;border: 0;}"; 
    body += "hr.new4 {margin-top: 30px;border: 2px solid rgb(97, 82, 58);}";
    body += "hr.new5 {margin-top: 6px;border: 2px solid rgb(97, 82, 58);}";
    body += ".options_in_student{display: flex;}";
    body += ".object_in_options_student{width: 41%;margin-top: 30px;height: 60px;font-size: 25px;padding-top: 20px;margin-left: 6%;background-color: rgb(97, 82, 58);color: aliceblue;}";
    body += ".submit_class{width: 100%;height: 100px;}";
    body += ".logout_key{height: 40px;border: none;font-family: fantasy;font-size: 25px;color: aliceblue;background-color: rgb(97, 82, 58);}";
    body += ".submit_class{width: 10%;margin-left: 45%;margin-right: 45%;margin-top: 5px;height: 30px;}";
    body += "#show_course {display:none;height: 250px;width: 100%;padding: 10px;margin-top: 10px;text-align: center;background-color: rgba(241, 204, 149, 0.804);}";
    body += ".top_of_page{width: 100%;height: 100px;}";
    body += ".course_info_text{width: 50%;margin-left: 25%;height: 70px;margin-top: 30px;font-size: 35px;padding-top: 20px;background-color:  rgba(215, 238, 236, 0.934);border-style: solid;border-color: rgb(97, 82, 58);border-width: 7px;}";
    body += ".options_class{width: 70%;margin-left: 15%;margin-right: 40%;height: 20px;margin-top: 7px;}";
    body += "</style>";
    body += "</head>";
    body += "<body>";
    body += "<div class='top_of_page'><div class='course_info_text'>UT Admin</div></div>";
    body += "<hr class='new4'><hr class='new5'><hr class='new5'>";
    body += "<div class='options_in_student'><div class='object_in_options_student'><button class='logout_key' onclick='showFunction()'>Course offer</button></div><div class='object_in_options_student'><a href='sharePost'>Share post</a></div></div>";
    body += "<div id='show_course'><section class='login_form'><form action='/courseOffer' method='post'>";
    body += "<input name='course_id' type='text' placeholder='course id' class='options_class'>";
    body += "<input name='professor_id' type='text' placeholder='professor id' class='options_class'>";
    body += "<input name='capacity' type='text' placeholder='capacity' class='options_class'>";
    body += "<input name='time' type='text' placeholder='time' class='options_class'>";
    body += "<input name='exam_date' type='text' placeholder='exam date' class='options_class'>";
    body += "<input name='class_number' type='text' placeholder='class number' class='options_class'>";
    body += "<input type='submit' class='submit_class' value='click'>";
    body += "</form></section></div>";
    body += "<div class='options_in_student'><form class='object_in_options_student_last' action='/logout' method='post' ><input type='submit' class='logout_key' value='Logout'></form></div>";

    body += "<script>";
    body += "function showFunction() {var x = document.getElementById('show_course');if (x.style.display === 'none') {x.style.display = 'block';} else {x.style.display = 'none';}}";
    body += "</script>";

    body += "</body>";
    body += "</html>";

    return body;
}