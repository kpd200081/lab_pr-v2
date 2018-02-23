#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <string>
#include "aes.h"
#include <vector>
#include <cstdlib>
#include <ctime>

class Encrypt
{
    Aes256* aes;
public:
    Encrypt();
    std::string work(std::string&, std::string&, bool);
    ~Encrypt();
};

#endif // ENCRYPT_H
