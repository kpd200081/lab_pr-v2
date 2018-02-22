#include "encrypt.h"

Encrypt::Encrypt()
{

}

std::string Encrypt::work(std::string& data, std::string& key)
{
    std::string res="";
    for(unsigned long i=0;i<data.length()+1;i++)
        res+=data[i]^key[i%key.length()+1];
    return res;
}
