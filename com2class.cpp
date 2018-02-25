#include "com2class.h"


Com2Class::Com2Class(Com2Class *prev, Com2Class *next, int tr_n, int cr_n): ComClass (prev,next,tr_n)
{
    car_number=cr_n;
}

Com2Class::Com2Class(Com2Class *prev, Com2Class *next):ComClass(prev, next)
{

}

Com2Class::~Com2Class()
{

}


