#ifndef INPUT_HPP
#define INPUT_HPP

#include "common.hpp"
#include "process.hpp"
#include "carwash.hpp"

void findWorkerStage(Carwash &carwash, vector<string> &splitted);

void sortWorkersEachStage(Carwash &carwash);

void workerInput(Carwash &carwash, vector<string> &workers_input);

void stagesInput(Carwash &carwash, vector<string> &stages_input);

void input(vector<string> &workers_input, vector<string> &stages_input, Carwash &carwash);

#endif