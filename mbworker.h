#ifndef MBWORKER_H
#define MBWORKER_H

#include "rwworker.h"
#include "train.h"
#include "passenger.h"
#include <sstream>
#include <cstdio>
#include <cstring>

class Train;
class MBWorker
{
    Train* first_t;
    Train* last_t;
    Passenger* first_p;
    Passenger* last_p;
    std::vector<std::string> routs;
    RWWorker* rww;
    int train_count, pass_count, routs_count;

public:
    MBWorker(RWWorker*);
    void init();
    int menu();
    void save();
    static int corInput(int);
    static int StrToInt(char*);
    ~MBWorker();
    void sell();
    void output();
    void add();
    void correct();
    void del();
    void output_trains();
    void output_passes();
    void outAllTrains();
    void outAllPas();
    void outRouts();
    void outPasByFio();
    void cor_train();
    void cor_dest();
    void cor_pas();
    void del_train();
    void del_dest();
    void del_pas();
    void create_dest();
    void add_train();
    Train* findTrain(int tr_n);
    void updateTrainCarFirstP();
    void cor_train_rout(Train*);
    void cor_train_num(Train*);
};

#endif // MBWORKER_H
