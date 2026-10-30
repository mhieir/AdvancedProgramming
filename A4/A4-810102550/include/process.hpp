#ifndef PROCESS_HPP
#define PROCESS_HPP

#include "worker.hpp"
#include "stage.hpp"
#include "carwash.hpp"

void signInSplitting(string &result, vector<string> &splitted);

void notSignInSplitting(string &result, char character);

vector<string> splitByInputSign(string inputString, char sign);

void changeValue(int worker_id, int car_id, int stage_id, Carwash &carwash);

void lastStage(int worker_id, int car_id, int stage_id, Carwash &carwash);

string makeNewHappeningInNotLast(Carwash &carwash, int car_id, int stage_id);

void notLastStage(int worker_id, int car_id, int stage_id, Carwash &carwash);

void changeLocation(int worker_id, int car_id, int stage_id, Carwash &carwash);

void changeWorker(int worker_id, int car_id, int stage_id, Carwash &carwash);

void checkStage(Carwash &carwash, int stage_id);

bool cars_in_queue_sort(Car a, Car b);

void makeNewHappeningInQueue(Carwash &carwash, int stage_id);

void checkQueueInStage(Carwash &carwash, int stage_id);

void passTime(Carwash &carwash);

bool sortTimeTable(pair<string, int> a, pair<string, int> b);

void passTimeOneByOne(Carwash &carwash, int number_of_pass_time);

vector<string> readCsv(const char path[256]);

Car addCar(Carwash &carwash, vector<int> &requested_stages);

Stage addStage(int id, int price);

Worker addWorker(int id, int time_to_finish);

vector<int> makeRequsetedStages(vector<string> &splitted_string);

void notFoundStage(Carwash &carwash, vector<int> requested_stages);

void carArrivalMode(Carwash &carwash, vector<string> &splitted_string);

void printStageStatusMode(Stage &requested_stage);

void stageStatusMode(Carwash &carwash, int stage_id);

void printWorkerStatusMode(Worker &requested_worker);

void workerStatusMode(Carwash &carwash, int worker_id);

void printCarStatusMode(Car &requested_car);

void carStatusMode(Carwash &carwash, int car_id);

void readQuery(Carwash &carwash, string query);

void process(Carwash &carwash);

#endif