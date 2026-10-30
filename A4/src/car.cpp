#include "car.hpp"

void Car::changePosition()
{
    if (position == STAGE)
        position = QUEUE;
    else
        position = STAGE;
}

void Car::changeStatus(int car_status)
{
    if (car_status == IN_LINE)
        status = PRINT_IN_SERVICE + to_string(stage_id);
    else if (car_status == IN_SERVICE)
        status = PRINT_IN_LINE + to_string(stage_id);
    else if (car_status == DONE)
        status = PRINT_DONE;
}

void Car::carStatus()
{
    cout << status << endl;
}

void Car::setRemainingTime(int new_remaining_time) {
    remaining_time = new_remaining_time;
}

int Car::getRemainingTime() {
    return remaining_time;
}

void Car::setStageId(int new_stage_id) {
    stage_id = new_stage_id;
}

int Car::getStageId() {
    return stage_id;
}

void Car::setId(int new_id) {
    id = new_id;
}

int Car::getId() {
    return id;
}

void Car::setLastTimeMoved(int new_last_time_moved) {
    last_time_moved = new_last_time_moved;
}

int Car::getLastTimeMoved() {
    return last_time_moved;
}

void Car::setPosition(string new_position) {
    position = new_position;
}

string Car::getPosition() {
    return position;
}