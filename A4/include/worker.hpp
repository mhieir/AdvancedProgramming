#ifndef WORKER_HPP
#define WORKER_HPP

#include "common.hpp"

class Worker
{
public:
    void changeStatus();
    void workerStatus();
    bool isWorking();
    void carNumber(int car_id);
    int getCarNumber() { return car_number; }
    void setTimeToFinish(int new_time) { time_to_finish = new_time; }
    int getTimeToFinish() { return time_to_finish; }
    void setId(int new_id) { id = new_id; }
    int getId() { return id; }

private:
    bool is_worked = false;
    int car_number = IDLE_WORKER;
    int remaining_time = 0, id, time_to_finish = 0;
};

#endif