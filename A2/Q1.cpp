// in God we trust <3

#include <iostream>
#include <string>
#include <math.h>

using namespace std;

#define maxN 20
#define inf 10000000
#define zero '0'
#define one '1'

bool is_smaller(string str1, string str2) {
    if(str1.length() < str2.length()) return true;
    if(str1.length() > str2.length()) return false;

    for(int i = 0; i < str1.length(); i++) { 
        if(str1[i] > str2[i]) return false;
        if(str1[i] < str2[i]) return true;
    }
    return true;
}

void rev_string(string& str) {
    reverse(str.begin(), str.end());
}

void make_same_size(string& smaller, string& bigger) {
    rev_string(smaller);
    for(int i = smaller.length(); i < bigger.length(); i++) smaller += zero;
    rev_string(smaller);
}

void subtract(string& str1, string& str2, string& diff) {
    int tmp = 0;
    for(int i = 0; i < str1.length(); i++) {
        int num1 = str1[i] - zero;
        int num2 = str2[i] - zero;

        if(num1 + tmp <= num2) {
            diff += ((num2 - num1 - tmp) + zero);
            tmp = 0;
        }
        else {
            diff += ((num2 + 10 - num1 - tmp) + zero);
            tmp = 1;
        }
    }

}

void delete_zero(string& str) {
    int len = str.length();
    while(len) {
        if(str[len - 1] != zero) return;
        str = str.substr(0, len - 1);
        len--;
    }
}

string subtract_strings(string smaller, string bigger) {
    if(!is_smaller(smaller, bigger)) swap(smaller, bigger);

    make_same_size(smaller, bigger);
    
    rev_string(smaller);
    rev_string(bigger);

    string diff = "";
    subtract(smaller, bigger, diff);
    delete_zero(diff);

    rev_string(diff);
    
    return diff;
}

void pre_process(vector<string>& ans) {
    ans[0] = "";
    for(int i = 1; i < maxN; i++) ans[i] = ans[i - 1] + one;
}

int solve(vector<string>& ans, string str) {
    if(str == "") return 0;
    int n = str.length(); 

    string newStr1 = subtract_strings(str, ans[n]);
    string newStr2 = subtract_strings(str, ans[n + 1]);

    int validAnswer = inf;
    if(is_smaller(newStr1, str)) validAnswer = min(validAnswer, n + solve(ans, newStr1));
    if(is_smaller(newStr2, str)) validAnswer = min(validAnswer, n + 1 + solve(ans, newStr2));
    return validAnswer; 
}

void get_input(string& str) {
    cin >> str;
}

void output(vector<string>& ans, string str) {
    cout << solve(ans, str);
}

int main() {

    vector<string> ans(maxN);
    string str;
    
    pre_process(ans);
    get_input(str);
    output(ans, str);

    return 0;
}
