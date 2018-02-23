#ifndef COMCLASS_H
#define COMCLASS_H

#include "rwworker.h"
#include <iostream>
#include <vector>

class ComClass
{
protected:
    int data_size;
public:
    int train_number;

    ComClass* next;
    ComClass* prev;

    ComClass(ComClass* prev, ComClass* next,int tr_n);
    ComClass(ComClass* prev, ComClass* next);
    ~ComClass();
    virtual std::vector<unsigned char> getWritebleData()=0;
    virtual void setData(std::vector<unsigned char>&)=0;
    int getDataSize() const;
    //friend RWWorker& operator<<(RWWorker& out, const ComClass obj);
    //friend RWWorker& operator>>(RWWorker& in, const ComClass obj);
};

#endif // COMCLASS_H
