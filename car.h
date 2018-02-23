#ifndef CAR_H
#define CAR_H

#include "com2class.h"
#include "passenger.h"

class Car : virtual public Com2Class
{
public:
    //enum CarType{Seat,Compartment,Restaurant};
    int sit_count;
    int free_sc;
    char type;
    Car* next;
    Car* prev;

    Car(Car* prev, Car* next, int cr_n, int tr_n, char type, int sit_count);
    Car(Car* prev, Car*next);
    ~Car();
    std::vector<unsigned char> getWritebleData();
    void setData(std::vector<unsigned char> &);
    friend std::ostream& operator<<(std::ostream& out, Car& self);
    //friend std::istream& operator>>(std::istream& in, Car& self);
};

#endif // CAR_H
