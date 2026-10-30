#pragma once
#ifndef UTACCOUNT_INCLUDE
#define UTACCOUNT_INCLUDE

#include "Global.hpp"
#include "People.hpp"

class UTAccount : public People {
public:
    UTAccount(string id = ZERO_STRING, string password = UT_ACCOUNT);
    ~UTAccount() {};
    void personalPage(vector<string>& output);
    void getPost(vector<string>& output, int post_id);
protected:
private:
};

#endif