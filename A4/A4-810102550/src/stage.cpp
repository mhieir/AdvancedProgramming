#include "stage.hpp"

bool sortWorkerByItems(Worker a, Worker b)
{
    if (a.getTimeToFinish() != b.getTimeToFinish())
        return a.getTimeToFinish() < b.getTimeToFinish();
    return a.getId() < b.getId();
}

void Stage::sortWorkers()
{
    sort(workers.begin(), workers.end(), sortWorkerByItems);
}

void Stage::callWorkerToChange(int requested_worker_id)
{
    workers[requested_worker_id].changeStatus();
}

void Stage::printStageStatusMode(int car_id, Car &car, int right_now_time)
{
    cout << right_now_time << CAR << car_id << ARRIVED << car.getPosition() << id << SPACE << endl;
}

void Stage::carRequest(int car_id, Car &car, int right_now_time)
{
    car.setStageId(id);
    for (int i = 0; i < workers.size(); i++)
    {
        if (!workers[i].isWorking())
        {
            workers[i].changeStatus();
            workers[i].carNumber(car_id);
            car.setRemainingTime(workers[i].getTimeToFinish());
            car.changeStatus(IN_LINE);
            car.setPosition(STAGE);
            being_washed++;
            return;
        }
    }
    car.setLastTimeMoved(right_now_time);
    cars_queue.push_back(car);
    car.changeStatus(IN_SERVICE);
    car.setPosition(QUEUE);
    cars_in_queue++;
}

void Stage::setPrice(int new_price) { price = new_price; }
void Stage::setWashedCars(int new_washed_cars) { washed_cars = new_washed_cars; }
void Stage::setCarsInQueue(int new_cars_in_queue) { cars_in_queue = new_cars_in_queue; }
void Stage::setBeingWashed(int new_being_washed) { being_washed = new_being_washed; }
void Stage::setIncome(int new_income) { income = new_income; }
void Stage::setId(int new_id) { id = new_id; }

int Stage::getPrice() { return price; }
int Stage::getWashedCars() { return washed_cars; }
int Stage::getCarsInQueue() { return cars_in_queue; }
int Stage::getBeingWashed() { return being_washed; }
int Stage::getIncome() { return income; }
int Stage::getId() { return id; }