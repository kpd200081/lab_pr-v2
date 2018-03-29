#ifndef RWWORKER_H
#define RWWORKER_H

#include <iostream>
#include "comclass.h"
#include "sha1.h"
#include <string>
#include <vector>
#include <deque>
#include <fstream>
#include <iomanip>

class ComClass;

class RWWorker
{

    std::string name;
    bool fileWasCreated=false;

    SHA1 checksum;

public:
    std::deque<unsigned char> buf;
    RWWorker();
    void set_file(std::string);
    bool init();
    void write();
    void calcCheckSum();
    bool checkCheckSum();
    void creationOfFile();
    friend RWWorker& operator<<(RWWorker&,ComClass&);
    friend RWWorker& operator>>(RWWorker&,ComClass&);
    ~RWWorker();
};

#endif // RWWORKER_H
