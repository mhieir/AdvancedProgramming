#ifndef STAGE_HPP
#define STAGE_HPP

#include "common.hpp"
#include "car.hpp"
#include "worker.hpp"

class Stage
{
public:
    void setPrice(int new_price);
    void setWashedCars(int new_washed_cars);
    void setCarsInQueue(int new_cars_in_queue);
    void setBeingWashed(int new_being_washed);
    void setIncome(int new_income);
    void setId(int new_id);
    int getPrice();
    int getWashedCars();
    int getCarsInQueue();
    int getBeingWashed();
    int getIncome();
    int getId();
    vector<Worker> workers;
    vector<Car> cars_queue;
    void carRequest(int car_id, Car &car, int right_now_time);
    void callWorkerToChange(int requested_worker_id);
    void printStageStatusMode(int car_id, Car &car, int right_now_time);
    void sortWorkers();

private:
    int price = 0, washed_cars = 0, cars_in_queue = 0, being_washed = 0, income = 0;
    int id;
};

#endif