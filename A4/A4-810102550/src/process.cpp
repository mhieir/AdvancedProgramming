#include "process.hpp"

void signInSplitting(string &result, vector<string> &splitted)
{
    splitted.push_back(result);
    result = NULL_STRING;
}

void notSignInSplitting(string &result, char character)
{
    result += character;
}

vector<string> splitByInputSign(string inputString, char sign)
{
    string result = NULL_STRING;
    vector<string> splitted;
    for (auto &character : inputString)
    {
        if (character == sign)
        {
            signInSplitting(result, splitted);
        }
        else
        {
            notSignInSplitting(result, character);
        }
    }
    signInSplitting(result, splitted);
    return splitted;
}

void changeValue(int worker_id, int car_id, int stage_id, Carwash &carwash)
{
    carwash.stages[stage_id].setBeingWashed(carwash.stages[stage_id].getBeingWashed() - 1);
    carwash.stages[stage_id].setWashedCars(carwash.stages[stage_id].getWashedCars() + 1);
    carwash.stages[stage_id].setIncome(carwash.stages[stage_id].getIncome() + carwash.stages[stage_id].getPrice());
    carwash.stages[stage_id].callWorkerToChange(worker_id);
    carwash.cars[car_id].setLastTimeMoved(carwash.time);
    carwash.cars[car_id].requested_stages.erase(carwash.cars[car_id].requested_stages.begin());
}

void lastStage(int worker_id, int car_id, int stage_id, Carwash &carwash)
{
    carwash.cars[car_id].changeStatus(DONE);
    string new_happening = to_string(carwash.time) + CAR + to_string(car_id + 1) + COLON + SPACE + STAGE;
    new_happening += to_string(stage_id + 1) + SIGN + PRINT_DONE;
    carwash.time_table.push_back({new_happening, car_id + 1});
}

string makeNewHappeningInNotLast(Carwash &carwash, int car_id, int stage_id) {
    string new_happening = to_string(carwash.time) + CAR + to_string(car_id + 1) + COLON + SPACE;
    new_happening += STAGE + to_string(stage_id + 1) + SIGN + carwash.cars[car_id].getPosition();
    new_happening += to_string(carwash.cars[car_id].requested_stages[0]);
    return new_happening;
}

void notLastStage(int worker_id, int car_id, int stage_id, Carwash &carwash)
{
    for (int i = 0; i < carwash.stages.size(); i++)
    {
        if (carwash.stages[i].getId() == carwash.cars[car_id].requested_stages[0])
        {
            carwash.stages[i].carRequest(carwash.cars[car_id].getId(), carwash.cars[car_id], carwash.time);
            string new_happening = makeNewHappeningInNotLast(carwash, car_id, stage_id);
            carwash.time_table.push_back({new_happening, car_id + 1});
        }
    }
}

void changeLocation(int worker_id, int car_id, int stage_id, Carwash &carwash)
{
    changeValue(worker_id, car_id, stage_id, carwash);
    if (carwash.cars[car_id].requested_stages.empty())
    {
        lastStage(worker_id, car_id, stage_id, carwash);
    }
    else
    {
        notLastStage(worker_id, car_id, stage_id, carwash);
    }
}

void changeWorker(int worker_id, int car_id, int stage_id, Carwash &carwash)
{
    int new_remaining_time = carwash.cars[car_id].getRemainingTime() - 1;
    carwash.cars[car_id].setRemainingTime(new_remaining_time);
    if (carwash.cars[car_id].getRemainingTime() == 0)
    {
        changeLocation(worker_id, car_id, stage_id, carwash);
    }
}

void checkStage(Carwash &carwash, int stage_id)
{
    for (int i = 0; i < carwash.stages[stage_id].workers.size(); i++)
    {
        if (!carwash.stages[stage_id].workers[i].isWorking())
        {
            continue;
        }
        else
        {
            int working_car_id = carwash.stages[stage_id].workers[i].getCarNumber();
            if (carwash.cars[working_car_id - 1].getLastTimeMoved() == carwash.time)
                continue;
            changeWorker(i, working_car_id - 1, stage_id, carwash);
        }
    }
}

bool cars_in_queue_sort(Car a, Car b)
{
    if (a.getLastTimeMoved() != b.getLastTimeMoved())
        return a.getLastTimeMoved() < b.getLastTimeMoved();
    return a.getId() < b.getId();
}



void makeNewHappeningInQueue(Carwash &carwash, int stage_id)
{
    string new_happening = to_string(carwash.time);
    new_happening += CAR + to_string(carwash.stages[stage_id].cars_queue[0].getId()) + COLON;
    new_happening += SPACE + QUEUE + to_string(stage_id + 1);
    new_happening += SIGN + carwash.cars[carwash.stages[stage_id].cars_queue[0].getId() - 1].getPosition();
    new_happening += to_string(carwash.cars[carwash.stages[stage_id].cars_queue[0].getId() - 1].requested_stages[0]);
    carwash.time_table.push_back({new_happening, carwash.stages[stage_id].cars_queue[0].getId()});
}

void checkQueueInStage(Carwash &carwash, int stage_id)
{
    sort(carwash.stages[stage_id].cars_queue.begin(), carwash.stages[stage_id].cars_queue.end(), cars_in_queue_sort);
    for (int i = 0; i < carwash.stages[stage_id].workers.size(); i++)
    {

        if (!carwash.stages[stage_id].workers[i].isWorking() and !carwash.stages[stage_id].cars_queue.empty())
        {
            carwash.stages[stage_id].setCarsInQueue(carwash.stages[stage_id].getCarsInQueue() - 1);
            int car_id = carwash.stages[stage_id].cars_queue[0].getId() - 1;
            carwash.stages[stage_id].carRequest(carwash.stages[stage_id].cars_queue[0].getId(), carwash.cars[car_id], carwash.time);
            makeNewHappeningInQueue(carwash, stage_id);
            carwash.stages[stage_id].cars_queue.erase(carwash.stages[stage_id].cars_queue.begin());
        }

        else
        {
            continue;
        }
    }
}

void passTime(Carwash &carwash)
{
    for (int i = 0; i < carwash.stages.size(); i++)
    {
        checkStage(carwash, i);
        checkQueueInStage(carwash, i);
    }
}

bool sortTimeTable(pair<string, int> a, pair<string, int> b) {
    if(a.second != b.second) return a.second < b.second;
    return a.first < b.first;
}

void passTimeOneByOne(Carwash &carwash, int number_of_pass_time)
{
    for (int i = 0; i < number_of_pass_time; i++)
    {
        carwash.time++;
        passTime(carwash);
        if(carwash.time_table.size() > 1) sort(carwash.time_table.begin(), carwash.time_table.end(), sortTimeTable);
        for (auto new_happening : carwash.time_table)
            cout << new_happening.first << endl;
        carwash.time_table.clear();
    }
}

vector<string> readCsv(const char path[256])
{
    vector<string> lines;
    ifstream file_name;
    string new_line;
    file_name.open(path);
    while (getline(file_name, new_line))
    {
        lines.push_back(new_line);
    }
    file_name.close();
    return lines;
}

Car addCar(Carwash &carwash, vector<int> &requested_stages)
{
    Car new_car;
    new_car.requested_stages = requested_stages;
    new_car.setId(carwash.cars.size() + 1);
    return new_car;
}

Stage addStage(int id, int price)
{
    Stage new_stage;
    new_stage.setId(id);
    new_stage.setPrice(price);
    return new_stage;
}

Worker addWorker(int id, int time_to_finish)
{
    Worker new_worker;
    new_worker.setId(id);
    new_worker.setTimeToFinish(time_to_finish);
    return new_worker;
}

vector<int> makeRequsetedStages(vector<string> &splitted_string)
{
    vector<int> requested_stages;
    for (int i = 1; i < splitted_string.size(); i++)
    {
        requested_stages.push_back(stoi(splitted_string[i]));
    }
    return requested_stages;
}

void notFoundStage(Carwash &carwash, vector<int> requested_stages)
{
    for (int i = 0; i < requested_stages.size(); i++)
    {
        bool match_to_stage = false;
        for (int j = 0; j < carwash.stages.size(); j++)
        {
            if (requested_stages[i] == carwash.stages[j].getId())
                match_to_stage = true;
        }
        if (!match_to_stage)
            carwash.found = false;
    }
}

void carArrivalMode(Carwash &carwash, vector<string> &splitted_string)
{
    vector<int> requested_stages = makeRequsetedStages(splitted_string);
    notFoundStage(carwash, requested_stages);
    if(!carwash.found) return;
    carwash.cars.push_back(addCar(carwash, requested_stages));
    for (int i = 0; i < carwash.stages.size(); i++)
    {
        if (carwash.stages[i].getId() == requested_stages[0])
        {
            carwash.stages[i].carRequest(int(carwash.cars.size()), carwash.cars.back(), carwash.time);
            carwash.stages[i].printStageStatusMode(int(carwash.cars.size()), carwash.cars.back(), carwash.time);
        }
    }
}

void printStageStatusMode(Stage &requested_stage)
{
    cout << WASHED_CARS << requested_stage.getWashedCars() << endl;
    cout << IN_QUEUE_CARS << requested_stage.getCarsInQueue() << endl;
    cout << BEING_WASHED_CARS << requested_stage.getBeingWashed() << endl;
    cout << INCOME << requested_stage.getIncome() << endl;
}

void stageStatusMode(Carwash &carwash, int stage_id)
{
    for (int i = 0; i < carwash.stages.size(); i++)
    {
        if (carwash.stages[i].getId() == stage_id)
        {
            printStageStatusMode(carwash.stages[i]);
            return;
        }
    }
    carwash.found = false;
}

void printWorkerStatusMode(Worker &requested_worker)
{
    requested_worker.workerStatus();
}

void workerStatusMode(Carwash &carwash, int worker_id)
{
    for (int i = 0; i < carwash.stages.size(); i++)
    {
        for (int j = 0; j < carwash.stages[i].workers.size(); j++)
        {
            if (carwash.stages[i].workers[j].getId() == worker_id)
            {
                printWorkerStatusMode(carwash.stages[i].workers[j]);
                return;
            }
        }
    }
    carwash.found = false;
}

void printCarStatusMode(Car &requested_car)
{
    requested_car.carStatus();
}

void carStatusMode(Carwash &carwash, int car_id)
{
    for (int i = 0; i < carwash.cars.size(); i++)
    {
        if (carwash.cars[i].getId() == car_id)
        {
            printCarStatusMode(carwash.cars[i]);
            return;
        }
    }
    carwash.found = false;
}

void readQuery(Carwash &carwash, string query)
{
    carwash.found = true;
    vector<string> splitted_string = splitByInputSign(query, SPACE);
    string mode = splitted_string[0];
    if (mode == PASS_TIME)
        passTimeOneByOne(carwash, stoi(splitted_string[1]));
    else if (mode == CAR_ARRIVAL)
        carArrivalMode(carwash, splitted_string);
    else if (mode == CAR_STATUS)
        carStatusMode(carwash, stoi(splitted_string[1]));
    else if (mode == WORKER_STATUS)
        workerStatusMode(carwash, stoi(splitted_string[1]));
    else if (mode == STAGE_STATUS)
        stageStatusMode(carwash, stoi(splitted_string[1]));
    else
    {
        carwash.found = false;
    }
    if (!carwash.found)
        cout << NOT_FOUND << endl;
}

void process(Carwash &carwash)
{
    while (1)
    {
        string input_string;
        getline(cin, input_string);
        readQuery(carwash, input_string);
    }
}
