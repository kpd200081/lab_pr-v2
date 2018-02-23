#ifndef COM2CLASS_H
#define COM2CLASS_H
#include "comclass.h"

class Com2Class :virtual public ComClass
{
public:
    int car_number;
    Com2Class(Com2Class* prev, Com2Class* next, int tr_n, int cr_n);
    Com2Class(Com2Class* prev, Com2Class* next);
    virtual ~Com2Class();
};

#endif // COM2CLASS_H
