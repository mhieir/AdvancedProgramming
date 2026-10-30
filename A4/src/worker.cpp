#include "worker.hpp"

void Worker::workerStatus()
{
    if (is_worked)
    {
        cout << WORKING << car_number << endl;
    }
    else
    {
        cout << IDLE << endl;
    }
}

void Worker::changeStatus()
{
    if (is_worked)
    {
        is_worked = false;
        car_number = IDLE_WORKER;
    }
    else
    {
        is_worked = true;
    }
}

void Worker::carNumber(int car_id)
{
    car_number = car_id;
}

bool Worker::isWorking()
{
    if (is_worked)
        return true;
    return false;
}