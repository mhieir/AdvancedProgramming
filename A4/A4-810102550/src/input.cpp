#include "input.hpp"

void findWorkerStage(Carwash &carwash, vector<string> &splitted)
{
    for (int i = 0; i < carwash.stages.size(); i++)
    {
        if (carwash.stages[i].getId() == stoi(splitted[1]))
        {
            carwash.stages[i].workers.push_back(addWorker(stoi(splitted[0]), stoi(splitted[2])));
        }
    }
}

void sortWorkersEachStage(Carwash &carwash)
{
    for (int i = 0; i < carwash.stages.size(); i++)
    {
        carwash.stages[i].sortWorkers();
    }
}

void workerInput(Carwash &carwash, vector<string> &workers_input)
{
    workers_input.erase(workers_input.begin());
    for (int i = 0; i < workers_input.size(); i++)
    {
        vector<string> splitted = splitByInputSign(workers_input[i], COMMA);
        findWorkerStage(carwash, splitted);
    }
    sortWorkersEachStage(carwash);
}

void stagesInput(Carwash &carwash, vector<string> &stages_input)
{
    stages_input.erase(stages_input.begin());
    for (int i = 0; i < stages_input.size(); i++)
    {
        vector<string> splitted = splitByInputSign(stages_input[i], COMMA);
        carwash.stages.push_back(addStage(stoi(splitted[0]), stoi(splitted[1])));
    }
}

void input(vector<string> &workers_input, vector<string> &stages_input, Carwash &carwash)
{
    stagesInput(carwash, stages_input);
    workerInput(carwash, workers_input);
}
