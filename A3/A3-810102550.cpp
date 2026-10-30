// in God we trust <3
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

struct NameIntro {
    string name;
    double cost;
};

struct UserInformations {
    string name;
    double money;

    void change_money(double cost) {
        money += cost;
    }
};

typedef vector<NameIntro> NameInformation;

struct expenses {
    string mode, inputString;
    NameInformation payers, borrowers;
    vector<string> splittedByComma;
};


const string NULL_STRING = "";
const char SPLITTER_CHARACTER = ',';
const string NOT_EQUALLY_MODE = "";
const string ZERO_STRING = "0";
const char ZERO_INT = 0;
const char SEMICOLON = ';';
const char COLON = ':';
const string EQUALLY = "equally";
const string UNEQUALLY = "unequally";
const string ADJUSTMENT = "adjustment";
const int INDECTION = -1;
const int MODE = 0;
const int PAYER = 1;
const int BORROWER = 2;
const string PRINT_SIGN = " -> ";
const string OTHER_PRINT_SIGN = ": ";
const double HUNDRED = 100.0;

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

NameIntro make_nameintro(string name, double cost) {
    NameIntro intro;
    intro.name = name;
    intro.cost = cost;
    return intro;
}

void semicolon_in_colon_splitting(string& result, vector<string>& splitted) {
    splitted.push_back(result);
    result = NULL_STRING;
}

void not_semicolon_in_colon_splitting(string& result, char character) {
    result += character;
}

vector<string> split_by_comma(string inputString) {
    string result = NULL_STRING;
    vector<string> splitted;
    for(auto character : inputString) {
        if(character == SPLITTER_CHARACTER) {
            semicolon_in_colon_splitting(result, splitted);
        }
        else {
            not_semicolon_in_colon_splitting(result, character);
        }
    }
    semicolon_in_colon_splitting(result, splitted);
    
    return splitted;
}

void semicolon_in_colon_splitting(string& name, string& cost, bool& colon_flag, NameInformation& splitted) {
    splitted.push_back(make_nameintro(name, stoi(cost)));
    name = NULL_STRING;
    cost = ZERO_STRING;
    colon_flag = false;
}

void colon_in_colon_splitting(string& cost, bool& colon_flag) {
    colon_flag = true;
    cost = NOT_EQUALLY_MODE;
}

void false_colon_in_colon_splitting(string& name, char character) {
    name += character;
}

void true_colon_in_colon_splitting(string& cost, char character) {
    cost += character;
}
      
vector<NameIntro> split_by_colon(string inputString) {
    vector<NameIntro> splitted;

    string name, cost = ZERO_STRING;
    bool colon_flag = false;
    for(auto character : inputString) {
        if(character == SEMICOLON) {
            semicolon_in_colon_splitting(name, cost, colon_flag, splitted);
        }
        else if(character == COLON) {
            colon_in_colon_splitting(cost, colon_flag);
        }
        else {
            if(!colon_flag) false_colon_in_colon_splitting(name, character);
            else true_colon_in_colon_splitting(cost, character);
        }
    }
    semicolon_in_colon_splitting(name, cost, colon_flag, splitted);
    
    return splitted;
}

NameInformation full_name_for_borrowers(vector<UserInformations>& userInfo) {
    NameInformation borrowers;
    for(auto user : userInfo) {
        borrowers.push_back(make_nameintro(user.name, ZERO_INT));
    }
    return borrowers;
}

NameInformation check_for_no_borrowers(string inputString, vector<UserInformations>& userInfo) {
    if(inputString.size() == 0) return full_name_for_borrowers(userInfo);
    else return split_by_colon(inputString);
}

double round_down(double cost) {
    return floor(cost * HUNDRED) / HUNDRED;
}

double calculate_cost(NameInformation& transactions) {
    double sumOfMoney = 0;
    for(auto transaction : transactions) {
        sumOfMoney += transaction.cost;
    }
    return sumOfMoney;
}

int find_index(string name, vector<UserInformations>& userInfo) {
    for(int i = 0; i < userInfo.size(); i++) {
        if(userInfo[i].name == name) return i;
    }
    return 0;
}

void payer_mode(NameInformation& payers, vector<UserInformations>& userInfo) {
    for(auto payer : payers) {
        userInfo[find_index(payer.name, userInfo)].change_money(payer.cost);
    }
}

void borrowers_mode_equally(NameInformation& borrowers, NameInformation& payers, vector<UserInformations>& userInfo) {
    double sumOfMoney = calculate_cost(payers);
    int number = borrowers.size();
    
    double settled = round_down(sumOfMoney / number);
    for(int i = 0; i + 1 < borrowers.size(); i++) {
        userInfo[find_index(borrowers[i].name, userInfo)].change_money(INDECTION * settled);
    }
    sumOfMoney -= (number - 1) * settled;
    userInfo[find_index(borrowers[number - 1].name, userInfo)].change_money(INDECTION * sumOfMoney);
}

void equally_mode(NameInformation& payers, NameInformation& borrowers, vector<UserInformations>& userInfo) {
    payer_mode(payers, userInfo);
    borrowers_mode_equally(borrowers, payers, userInfo);
}

void borrowers_mode_unequally(NameInformation& borrowers, vector<UserInformations>& userInfo) {
    for(auto borrower : borrowers) {
        userInfo[find_index(borrower.name, userInfo)].change_money(INDECTION * borrower.cost);
    }
}

void unequally_mode(NameInformation& payers, NameInformation& borrowers, vector<UserInformations>& userInfo) {
    payer_mode(payers, userInfo);
    borrowers_mode_unequally(borrowers, userInfo);
}

void extra_amount_adjustment(NameInformation& borrowers, vector<UserInformations>& userInfo) {
    borrowers_mode_unequally(borrowers, userInfo);
}

void equall_part_adjustment(NameInformation& payers, NameInformation& borrowers, vector<UserInformations>& userInfo) {
    double sumOfMoney = calculate_cost(payers) - calculate_cost(borrowers);
    int number = userInfo.size();
    double settled = round_down(sumOfMoney / number);
    
    string lastPerson = borrowers.back().name;
    int indexLastPerson;
    for(int i = 0; i < userInfo.size(); i++) {
        if(userInfo[i].name != lastPerson) userInfo[i].change_money(INDECTION * settled);
        else indexLastPerson = i;
    }
    sumOfMoney -= (number - 1 ) * settled;
    userInfo[indexLastPerson].change_money(INDECTION * sumOfMoney);
}

void borrowers_mode_adjustment(NameInformation borrowers, NameInformation payers, vector<UserInformations>& userInfo) {
    extra_amount_adjustment(borrowers, userInfo);
    equall_part_adjustment(payers, borrowers, userInfo);
}

void adjustment_mode(NameInformation& payers, NameInformation& borrowers, vector<UserInformations>& userInfo) {
    payer_mode(payers, userInfo);
    borrowers_mode_adjustment(borrowers, payers, userInfo);
}

void make_value(expenses& expense, vector<UserInformations>& userInfo) {
    expense.splittedByComma = split_by_comma(expense.inputString);
    expense.mode = expense.splittedByComma[MODE];
    expense.payers = split_by_colon(expense.splittedByComma[PAYER]);
    expense.borrowers = check_for_no_borrowers(expense.splittedByComma[BORROWER], userInfo);
}

void check_mode(expenses& expense, vector<UserInformations>& userInfo) {
    if(expense.mode == EQUALLY) {
        equally_mode(expense.payers, expense.borrowers, userInfo);
    }
    else if(expense.mode == UNEQUALLY) {
        unequally_mode(expense.payers, expense.borrowers, userInfo);
    }
    else if(expense.mode == ADJUSTMENT) {
        adjustment_mode(expense.payers, expense.borrowers, userInfo);
    }
}

void name_input(vector<string>& namesInput, vector<UserInformations>& userInfo) {
    namesInput.erase(namesInput.begin());
    userInfo.resize(namesInput.size());
    for(int i = 0; i < namesInput.size(); i++) {
        userInfo[i].name = namesInput[i];
    }
}

void expense_input(vector<string>& expenseInput, vector<expenses>& expense, vector<UserInformations>& userInfo) {
    expenseInput.erase(expenseInput.begin());
    expense.resize(expenseInput.size());
    for(int i = 0; i < expenseInput.size(); i++) {
        expense[i].inputString = expenseInput[i];
    }
}

void input(vector<string>& expenseInput, vector<expenses>& expense, vector<string>& namesInput, vector<UserInformations>& userInfo) {
    name_input(namesInput, userInfo);
    expense_input(expenseInput, expense, userInfo);
}

bool amountCompare(NameIntro a, NameIntro b) {
    if(a.cost != b.cost) return a.cost > b.cost;
    return a.name < b.name;
}

void sorting(NameInformation& debtors, NameInformation& creditors) {
    sort(debtors.begin(), debtors.end(), amountCompare);
    sort(creditors.begin(), creditors.end(), amountCompare);
}

void find_group(NameInformation& debtors, NameInformation& creditors, vector<UserInformations> userInfo) {
    for(auto user : userInfo) {
        if(user.money < 0) debtors.push_back(make_nameintro(user.name, abs(user.money)));
        else if(user.money > 0) creditors.push_back(make_nameintro(user.name, abs(user.money)));
    }
}

struct Payments {
    string debtor, creditor;
    double amount;
    
    void print() {
        cout << debtor << PRINT_SIGN << creditor << OTHER_PRINT_SIGN << amount << endl;
    }
};

Payments make_payment(string debtor, string creditor, double amount) {
    Payments pay;
    pay.debtor = debtor;
    pay.creditor = creditor;
    pay.amount = amount;
    return pay;
}

void more_debt_mode(string debtor, string creditor, double debt, double credit, NameInformation& debtors, NameInformation& creditors, int& debtorsInd, int& creditorsInd, vector<Payments>& payment) {
    payment.push_back(make_payment(debtor, creditor, credit));
    creditors[creditorsInd].cost = 0;
    debtors[debtorsInd].cost -= credit;
}

void more_credit_mode(string debtor, string creditor, double debt, double credit, NameInformation& debtors, NameInformation& creditors, int& debtorsInd, int& creditorsInd, vector<Payments>& payment) {
    payment.push_back(make_payment(debtor, creditor, debt));
    creditors[creditorsInd].cost -= debt;
    debtors[debtorsInd].cost = 0;
}

void equall_debt_credit_mode(string debtor, string creditor, double debt, double credit, NameInformation& debtors, NameInformation& creditors, int& debtorsInd, int& creditorsInd, vector<Payments>& payment) {
    payment.push_back(make_payment(debtor, creditor, credit));
    creditors[creditorsInd].cost = 0;
    debtors[debtorsInd].cost = 0;
}

bool compare(Payments a, Payments b) {
    if(a.amount != b.amount) return a.amount > b.amount;
    if(a.debtor != b.debtor) return a.debtor < b.debtor;
    return a.creditor < b.creditor;
}

void amount_process(NameInformation& debtors, NameInformation& creditors, vector<Payments>& payment) {
    int debtorsInd = 0, creditorsInd = 0;
    while(debtorsInd < debtors.size() and creditorsInd < creditors.size()) {
        string debtor = debtors[debtorsInd].name, creditor = creditors[creditorsInd].name;
        double debt = debtors[debtorsInd].cost, credit = creditors[creditorsInd].cost;
        
        if(debt > credit) {
            more_debt_mode(debtor, creditor, debt, credit, debtors, creditors, debtorsInd, creditorsInd, payment);
        }
        else if(debt < credit) {
            more_credit_mode(debtor, creditor, debt, credit, debtors, creditors, debtorsInd, creditorsInd, payment);
        }
        else {
            equall_debt_credit_mode(debtor, creditor, debt, credit, debtors, creditors, debtorsInd, creditorsInd, payment);
        }
        if(creditors[creditorsInd].cost == 0) creditorsInd++;
        if(debtors[debtorsInd].cost == 0) debtorsInd++;
    }
    sort(payment.begin(), payment.end(), compare);
}

void grouping(vector<UserInformations> userInfo, vector<Payments>& payment) {
    NameInformation debtors, creditors;
    find_group(debtors, creditors, userInfo);
    sorting(debtors, creditors);
    amount_process(debtors, creditors, payment);
}

void process(vector<expenses>& expense, vector<UserInformations>& userInfo, vector<Payments>& payment) {
    for(int i = 0; i < expense.size(); i++) {
        make_value(expense[i], userInfo);
        check_mode(expense[i], userInfo);
    }
    grouping(userInfo, payment);
}

void print(vector<Payments>& payment) {
    for(auto pay : payment) {
        pay.print();
    }
}

int main(int argc, char *argv[]) {
    
    vector<string> namesInput = read_csv(argv[1]), expenseInput = read_csv(argv[2]);
    vector<UserInformations> userInfo;
    vector<expenses> expense;
    vector<Payments> payment;

    input(expenseInput, expense, namesInput, userInfo);
    process(expense, userInfo, payment);
    print(payment);
    return 0;
}
