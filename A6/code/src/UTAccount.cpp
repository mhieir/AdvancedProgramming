#include "UTAccount.hpp"

UTAccount::UTAccount(string id, string password) :
People(id, UT_ACCOUNT, nullptr, password, _UTACCOUNT) {}

void UTAccount::personalPage(vector<string>& output) {
    output.push_back(UT_ACCOUNT + END_LINE);
    People ::showPosts(output);
}

void UTAccount::getPost(vector<string>& output, int post_id) {
    output.push_back(UT_ACCOUNT + END_LINE);
    People ::showOnePost(output, post_id);
}