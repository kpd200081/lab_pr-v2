#ifndef CAR_H
#define CAR_H

#include "com2class.h"
#include "passenger.h"

class Car : virtual public Com2Class
{
public:
    enum CarType{Seat,Compartment,Restaurant};
    int sit_count;
    int free_sc;
    CarType type;
    Car* next;
    Car* prev;
    Passenger* firstp;
    int data_size;

    Car(Car* prev, Car* next, int cr_n, int tr_n, CarType type, int sit_count);
    Car(Passenger* first_p,Car* prev, Car* next);
    ~Car();
    void setFirstp(Passenger*);
    std::vector<unsigned char> getWritebleData();
    void setData(std::vector<unsigned char> &);
    friend std::ostream& operator<<(std::ostream& out, Car& self);
    void outPass();
    //friend std::istream& operator>>(std::istream& in, Car& self);
    int getDataSize();
};

#endif // CAR_H
