// in God we trust <3

#include <iostream>
#include <string>
#include <vector>
using namespace std;

const vector<string> notFound = {"!"};

vector<string> deleteComma(string prereq) {
    string a = "";
    vector<string> vec;
    for(int i = 0; i < prereq.size(); i++) {
        if(prereq[i] != ',') a += prereq[i];
        else {
            vec.push_back(a);
            a = "";
        }
    }
    if(a != "") vec.push_back(a);
    return vec;
}

struct Courses {
    string name;
    int unit;
    vector<string> prereq;
    
    void input() {
        string stringPreReq;
        cin >> name >> unit >> stringPreReq;
        prereq = deleteComma(stringPreReq);
    }
};

struct LastCourses {
    string name;
    int unit;
    double grade;
    
    void input() {
        cin >> name >> unit >> grade;
    }
};

void inputCourseData(vector<Courses> &course) {
    int m; cin >> m;
    course.resize(m);
    for(Courses &c : course) {
        c.input();
    }
}

void inputLastCourseData(vector<LastCourses> &lastCourse) {
    int n; cin >> n;
    lastCourse.resize(n);
    for(LastCourses &lc : lastCourse) {
        lc.input();
    }
}

void inputMyCourseData(vector<string> &myCourse) {
    int k; cin >> k;
    myCourse.resize(k);
    for(int i = 0; i < k; i++) {
        cin >> myCourse[i];
    }
}

int wantedUnits(vector<Courses> &course, vector<string> &myCourse) {
    int cntUnit = 0;
    for(string unitName : myCourse) {
        for(Courses c : course)
            if(c.name == unitName) cntUnit += c.unit;
    }
    return cntUnit;
}

double calculateGPA(vector<LastCourses> &lastCourse) {
    double gpa = 0;
    int cntUnit = 0;
    // lc : short of last course
    for(LastCourses lc : lastCourse) {
        gpa += lc.grade * lc.unit;
        cntUnit += lc.unit;
    }

    return gpa / cntUnit;
}

bool checkGPA(vector<LastCourses> &lastCourse, vector<Courses> &course, vector<string> &myCourse) {
    // wu = short of wanted units
    int wu = wantedUnits(course, myCourse);
    double gpu = calculateGPA(lastCourse);
    if((gpu < 12 and wu > 14) || (gpu < 17 and wu > 20) || wu > 24) return false;
    return true;
}

bool checkForPresent(vector<Courses> &course, vector<string> &myCourse) {
    for(string unitName : myCourse) {
        bool flag = false;
        for(Courses c : course) {
            if(unitName == c.name) flag = true;
        }
        if(!flag) return false;
    }
    return true;
}

bool countForMinimumUnits(vector<Courses> &course, vector<string> &myCourse) {
    return ((wantedUnits(course, myCourse) < 12) ? false : true);
}

bool passUnit(string unit, vector<LastCourses> &lastCourse) {
    for(LastCourses lc : lastCourse) {
        if(unit == lc.name and lc.grade >= 10) return true;
    }
    return false;
}

bool checkPassIt(vector<LastCourses> &lastCourse, vector<string> &myCourse) {
    for(string unit : myCourse) {
        if(passUnit(unit, lastCourse)) return false;
    }
    return true;
}

vector<string> allPreq(string unit, vector<Courses> &course) {
    for(Courses c : course) {
        if(c.name == unit) return c.prereq;
    }
    return notFound;
}

bool checkPre(vector<Courses> &course, vector<LastCourses> &lastCourse, vector<string> &myCourse) {
    vector<string> preq;
    for(string unit : myCourse) {
        preq = allPreq(unit, course);
        if(preq == notFound ) return false;
        
        for(string eachPreReq : preq) {
            if(!passUnit(eachPreReq, lastCourse)) return false;
        }
    }
    return true;
}

string outPut(vector<Courses> &course, vector<LastCourses> &lastCourse, vector<string> &myCourse) {
    if(!checkForPresent(course, myCourse)) return "Course Not Offered!";
    else if(!countForMinimumUnits(course, myCourse)) return "Minimum Units Validation Failed!";
    else if(!checkGPA(lastCourse, course, myCourse)) return "Maximum Units Validation Failed!";
    else if(!checkPassIt(lastCourse, myCourse)) return "Course Already Taken!";
    else if(!checkPre(course, lastCourse, myCourse)) return "Prerequisites Not Met!";
    return "OK!";
}

int main() {

    vector<Courses> course;
    vector<LastCourses> lastCourse;
    vector<string> myCourse;
    
    inputCourseData(course);
    inputLastCourseData(lastCourse);
    inputMyCourseData(myCourse);

    cout << outPut(course, lastCourse, myCourse);

    return 0;
}
