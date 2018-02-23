#include "comclass.h"


ComClass::ComClass(ComClass *cprev, ComClass *cnext, int tr_n)
{
   prev=cprev;
   next=cnext;
   if(prev)prev->next=this;
   if(next)next->prev=this;
   train_number=tr_n;
}

ComClass::ComClass(ComClass *cprev, ComClass *cnext)
{
    prev=cprev;
    next=cnext;
    if(prev)prev->next=this;
    if(next)next->prev=this;
}

ComClass::~ComClass()
{
    if(prev)prev->next=next;
    if(next)next->prev=prev;
}

int ComClass::getDataSize() const
{
    return data_size;
}
