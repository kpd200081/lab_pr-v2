#ifndef COMCLASS_H
#define COMCLASS_H

#include "rwworker.h"
#include <iostream>
#include <vector>


#define MENU_START std::cout<<"\033[1;34m";
#define MENU_END std::cout<<"\033[0m";
#define MENU_INPUT std::cout<<"\033[33m";
#define MENU_ERROR std::cout<<"\033[1;31m";
#define MENU_INFO std::cout<<"\033[1;32m";

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
    virtual ~ComClass();
    virtual std::vector<unsigned char> getWritebleData()=0;
    virtual void setData(std::vector<unsigned char>&)=0;
    virtual int getDataSize()=0;
    //friend RWWorker& operator<<(RWWorker& out, const ComClass obj);
    //friend RWWorker& operator>>(RWWorker& in, const ComClass obj);
};

#endif // COMCLASS_H
