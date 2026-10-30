#include "Global.hpp"

vector<string> read_csv(const char path[256]) {
    vector<string> lines;
    ifstream file_name;
    string new_line;
    file_name.open(path);
    while (getline(file_name, new_line)) {
        lines.push_back(new_line);
    }
    file_name.close();
    return lines;
}

void signInSplitting(string &result, vector<string> &splitted) {
    splitted.push_back(result);
    result = NULL_STRING;
}

void notSignInSplitting(string &result, char character) {
    result += character;
}

vector<string> splitByInputSign(string inputString, char sign) {
    string result = NULL_STRING;
    vector<string> splitted;
    bool flag = false;
    for (int i = 0; i < (int) inputString.size(); i++)
    {
        if (inputString[i] != sign || flag) {
            notSignInSplitting(result, inputString[i]);
        }
        else {
            signInSplitting(result, splitted);
        }
        if (inputString[i] == QUOTION) {
            if (flag) {
                flag = false;
            }
            else {
                flag = true;
            }
        }
    }
    if (inputString.back() != sign){
        splitted.push_back(result);
    }
    return splitted;
}

bool isQuestionMark(string input_line) {
    if(input_line == QUESTION_MARK) {
        return true;
    }
    else {
        return false;
    }
}

bool isNumber(string post_id) {
    for(char c : post_id) {
        if(!isdigit(c)) {
            return false;
        }
    }
    return true;
}

string makeText(vector<string> input_line, int start, int end) {
    string result = NULL_STRING;
    for(int i = start; i < end; i++) {
        result += input_line[i] + SPACE;
    }
    result += input_line[end];
    return result;
}

vector<int> findQuotion(vector<string> input_line) {
    vector<int> quotion;
    for(int i = 3; i < input_line.size(); i++) {
        if(input_line[i][0] == QUOTION) {
            quotion.push_back(i);
        }
        if(input_line[i].back() == QUOTION and (int) input_line[i].size() != 1) {
            quotion.push_back(i);
        }
    }
    return quotion;
}

bool hasCommon(int a, int b, int c, int d) {
    if(max(a, c) < min(b, d)) {
        return true;
    }
    else {
        return false;
    }
}