#ifndef TRAIN_H
#define TRAIN_H

#include "comclass.h"
#include "car.h"
#include "mbworker.h"

class Train : virtual public ComClass
{
public:
    int car_count;
    int full_cc;
    int rout_number;
    Train* next;
    Train* prev;
    Car* first;
    Car* last;
    std::vector<std::string>* routs;
    int data_size;

    Train(Train* prev, Train* next, int tr_n, int cr_c, int rout_n);
    Train(Train* prev, Train* next);
    ~Train();

    std::vector<unsigned char> getWritebleData();
    void setData(std::vector<unsigned char> &);

    friend std::ostream& operator<<(std::ostream& out, Train& self);

    void updateCarFirstP(Passenger*);
    int getDataSize();
};

#endif // TRAIN_H
