#include "common.hpp"
#include "input.hpp"
#include "process.hpp"
#include "carwash.hpp"


int main(int argc, char *argv[])
{

    vector<string> stages_input = readCsv(argv[1]), workers_input = readCsv(argv[2]);
    Carwash carwash;

    input(workers_input, stages_input, carwash);
    process(carwash);

    return 0;
}
