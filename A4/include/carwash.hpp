#ifndef CARWASH_HPP
#define CARWASH_HPP

#include "common.hpp"
#include "stage.hpp"
#include "car.hpp"
#include "worker.hpp"

class Carwash
{
public:
    int time = 0;
    bool found = false;
    vector<Stage> stages;
    vector<Car> cars;
    vector<Worker> workers;
    vector<pair<string, int>> time_table;
};

#endif
