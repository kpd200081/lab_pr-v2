#include "rwworker.h"

RWWorker::RWWorker()
{

}

void RWWorker::set_key(char * c_key)
{
    key=c_key;
}

void RWWorker::set_file(char *c_name)
{
    name=c_name;
}

void RWWorker::write()
{

}

void RWWorker::calcCheckSum()
{

}

bool RWWorker::checkCheckSum()
{
  return true;
}

void RWWorker::creationOfFile(std::ofstream& out)
{

}

RWWorker &operator<<(RWWorker& self,const ComClass& obj)
{
    std::vector<char> t=obj.getWritebleData();
    for(int i=0;i<t.size();i++)
        self.buf.push_back(t[i]);
    return self;
}

RWWorker &operator>>(RWWorker& self, ComClass& obj)
{
    std::vector<char> t;
    t.reserve(obj.getDataSize());
    for(int i=0;i<t.size();i++){
        t.push_back((self.buf[self.buf.size()-1]));
        self.buf.pop_back();
      }
    return self;
}



bool RWWorker::init()
{
    if(key.c_str()==NULL||name.c_str()==NULL)
        return false;
    std::ifstream inf(name, std::ios_base::binary|std::ios_base::in);
    if(!inf.is_open()){
        inf.close();
        std::ofstream onf(name, std::ios_base::binary);
        creationOfFile(onf);
        onf.close();
        inf.open(name,std::ios_base::binary);
    }
    char c;
    while(true){
        inf.read(&c,1);
        buf.push_back(c);
    }
    if(!checkCheckSum()){
        buf.clear();
        return false;
    }
//    for(int i=0;i<40;i++)
//        buf.pop_back();

//    std::string data;
//    for(int i=0; i<buf.size();i++)
//        data+=buf[i];
//    std::string res=Encrypt::work(data,key);
//    buf.clear();
//    for(int i=0; i<res.length();i++)
//         buf.push_back(res[i]);
//    std::string check; check+=buf[1]; check+=buf[2]; check+=buf[3]; check+=' '; check+=buf[4]; check+=buf[5];
//    if(!(check=="Enc ok"))
//        return false;
    return true;
}
