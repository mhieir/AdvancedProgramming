#ifndef CAR_HPP
#define CAR_HPP

#include "common.hpp"

class Car
{
public:
    void setRemainingTime(int new_remaining_time);
    int getRemainingTime();
    void setStageId(int new_stage_id);
    int getStageId();
    void setId(int new_id);
    int getId();
    void setLastTimeMoved(int new_last_time_moved);
    int getLastTimeMoved();
    void setPosition(std::string new_position);
    string getPosition();
    vector<int> requested_stages;
    void carStatus();
    void changePosition();
    void changeStatus(int car_status);

private:
    string status, position;
    int id, stage_id, remaining_time = 0;
    int last_time_moved = 0;
};

#endif