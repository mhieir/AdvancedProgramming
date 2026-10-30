#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

const string ON_WORK = "Idle";
const char SPACE = ' ';
const string PASS_TIME = "pass_time";
const string CAR_ARRIVAL = "car_arrival";
const string STAGE_STATUS = "get_stage_status";
const string WORKER_STATUS = "get_worker_status";
const string CAR_STATUS = "get_car_status";
const string WASHED_CARS = "Number of washed cars: ";
const string IN_QUEUE_CARS = "Number of cars in queue: ";
const string BEING_WASHED_CARS = "Number of cars being washed: ";
const string INCOME = "Income: ";
const string NULL_STRING = "";
const char COMMA = ',';
const string WORKING = "Working: ";
const string IDLE = "Idle";
const int IN_LINE = 0;
const int IN_SERVICE = 1;
const int DONE = 2;
const string PRINT_IN_LINE = "In line: ";
const string PRINT_IN_SERVICE = "In service: ";
const string PRINT_DONE = "Done";
const int IDLE_WORKER = -1;
const string QUEUE = "Queue ";
const string STAGE = "Stage ";
const string CAR = " Car ";
const string ARRIVED = ": Arrived -> ";
const string COLON = ":";
const string SIGN = " -> ";
const string NOT_FOUND = "NOT FOUND";

#endif