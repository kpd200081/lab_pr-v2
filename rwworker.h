#ifndef RWWORKER_H
#define RWWORKER_H

#include <iostream>
#include "comclass.h"
#include "sha1.h"
#include "encrypt.h"
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

class ComClass;

class RWWorker
{
public:
    std::vector<char> buf;
private:
    std::string name, key;

    SHA1 checksum;

public:
    RWWorker();
    void set_key(char*);
    void set_file(char*);
    bool init();
    void write();
    void calcCheckSum();
    bool checkCheckSum();
    void creationOfFile(std::ofstream&);
    friend RWWorker& operator<<(RWWorker&,const ComClass&);
    friend RWWorker& operator>>(RWWorker&,ComClass&);
};

#endif // RWWORKER_H
