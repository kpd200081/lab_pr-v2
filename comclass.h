#ifndef COMCLASS_H
#define COMCLASS_H

#include "rwworker.h"
#include <iostream>
#include <vector>

class ComClass
{
private:
    int train_number;

    int data_size;

public:

    ComClass();

    std::vector<char> getWritebleData() const;
    void setData(std::vector<char>&);
    int getDataSize() const;
    //friend RWWorker& operator<<(RWWorker& out, const ComClass obj);
   // friend RWWorker& operator>>(RWWorker& in, const ComClass obj);
};

#endif // COMCLASS_H
