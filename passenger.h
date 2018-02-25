#ifndef PASSENGER_H
#define PASSENGER_H

#include "com2class.h"
#include <cstring>

class Passenger : virtual public Com2Class
{
public:
     std::string fio;
     Passenger* next;
     Passenger* prev;
     int data_size;

     Passenger(Passenger* prev, Passenger* next, int tr_n, int cr_cn, std::string cfio);
     Passenger(Passenger* prev, Passenger* next);
     ~Passenger();

     std::vector<unsigned char> getWritebleData();
     void setData(std::vector<unsigned char> &);

     friend std::ostream& operator<<(std::ostream& out, Passenger& self);

     int getDataSize();
};

#endif // PASSENGER_H
