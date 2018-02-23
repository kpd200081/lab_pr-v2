#include "encrypt.h"

#define BUFFER_SIZE 1024*1024

Encrypt::Encrypt()
{

}

//std::string Encrypt::work(std::string& data, std::string& key)
//{
//    std::string res="";
//    for(unsigned long i=0;i<data.length()+1;i++)
//        res+=data[i]^key[i%key.length()+1];
//    return res;
//}

std::string Encrypt::work(std::string& data, std::string& key, bool direction)
{
    srand(time(NULL));
    std::string res="";
    std::vector<unsigned char> keyv;
    for(int i=0;i<key.length();i++)
        keyv.push_back(key[i]);
    std::vector<unsigned char> datav;
    for(int i=0;i<data.length();i++)
            datav.push_back(data[i]);
    std::vector<unsigned char> resv;
    aes=new Aes256(keyv);
    if(data.length()>BUFFER_SIZE)
        return "";
    if(!direction){
        //encrypt
        resv.clear();
        aes->encrypt_start(data.length(), resv);
        for(int i=0;i<resv.size();i++)
            res+=resv[i];
        resv.clear();
        aes->encrypt_continue(datav, resv);
        for(int i=0;i<resv.size();i++)
            res+=resv[i];
        resv.clear();
        aes->encrypt_end(resv);
        for(int i=0;i<resv.size();i++)
            res+=resv[i];
    }else{
        //decrypt
        aes->decrypt_start(data.length());
        resv.clear();
        aes->decrypt_continue(datav,resv);
        for(int i=0;i<resv.size();i++)
            res+=resv[i];
        resv.clear();
        aes->decrypt_end(resv);
        for(int i=0;i<resv.size();i++)
            res+=resv[i];
    }
    delete aes;
    return res;
}

Encrypt::~Encrypt()
{}
