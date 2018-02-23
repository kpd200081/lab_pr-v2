#ifndef MBWORKER_H
#define MBWORKER_H

#include "rwworker.h"
#include "train.h"
#include "passenger.h"
#include <sstream>

class MBWorker
{
    Train* first_t;
    Train* last_t;
    Passenger* first_p;
    Passenger* last_p;
    std::vector<std::string> routs;
    RWWorker* rww;
    int train_count, pass_count, rout_count;

public:
    MBWorker(RWWorker*);
    void init();
    int menu();
    void save();
    ~MBWorker();
};

#endif // MBWORKER_H
