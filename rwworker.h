#ifndef RWWORKER_H
#define RWWORKER_H

#include <iostream>
#include "comclass.h"
#include "sha1.h"
#include "encrypt.h"
#include <string>
#include <vector>
#include <deque>
#include <fstream>
#include <iomanip>

class ComClass;

class RWWorker
{
public:
    std::deque<unsigned char> buf;
private:
    std::string name, key;
    bool fileWasCreated=false;

    SHA1 checksum;
    Encrypt aes;

public:
    RWWorker();
    void set_key(std::string);
    void set_file(std::string);
    bool init();
    void write();
    void calcCheckSum();
    bool checkCheckSum();
    void creationOfFile();
    friend RWWorker& operator<<(RWWorker&,const ComClass&);
    friend RWWorker& operator>>(RWWorker&,ComClass&);
    ~RWWorker();
};

#endif // RWWORKER_H
