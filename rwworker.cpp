#include "rwworker.h"

RWWorker::RWWorker()
{

}

void RWWorker::set_key(std::string c_key)
{
    key=c_key;
}

void RWWorker::set_file(std::string c_name)
{
    name=c_name;
}

void RWWorker::write()
{
    buf.push_front('k'); buf.push_front('o'); buf.push_front('c'); buf.push_front('n'); buf.push_front('E');
    std::string data;
    for(int i=0; i<buf.size();i++)
         data+=buf[i];
    std::string res=aes.work(data,key, false);
    buf.clear();
    for(int i=0; i<res.length();i++)
         buf.push_back(res[i]);
    calcCheckSum();
    std::ofstream out(name);
    for(int i=0; i<buf.size();i++)
        out.put(buf[i]);
    out.close();
    buf.clear();
}

void RWWorker::calcCheckSum()
{
    std::string data;
    std::string sum;
    for(int i =0;i<buf.size();i++)
        data+=buf[i];
    checksum.update(data);
    sum=checksum.final();
    for(int i=0;i<sum.length();i++)
        buf.push_back(sum[i]);
}

bool RWWorker::checkCheckSum()
{
    if(buf.size()<40)
        return false;
    std::string base;
    for(int i=0;i<buf.size()-40;i++)
        base+=buf[i];
    std::string sum;
    for(int i=buf.size()-40;i<buf.size();i++)
        sum+=buf[i];
    checksum.update(base);
    if(!(sum==checksum.final()))
        return false;
    for(int i=0;i<40;i++)
        buf.pop_back();
    return true;
}

void RWWorker::creationOfFile()
{
    fileWasCreated=true;
    buf[0]='t';
    write();
}

RWWorker::~RWWorker()
{}

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
    if(key.c_str()==NULL||name.c_str()==NULL){
        std::cout<<"Err: no data"<<std::endl;
        return false;
    }
    std::ifstream inf(name, std::ios::binary|std::ios::in);
    if(!inf.is_open()){
        inf.close();
        std::ofstream onf(name, std::ios::binary|std::ios::out);
        onf.close();
        creationOfFile();
        inf.open(name,std::ios::binary|std::ios::in);
    }
    char c;
    while(inf.get(c)){
        buf.push_back(c);
    }
    if(!checkCheckSum()){
        buf.clear();
        inf.close();
        std::cout<<"Err: check sum uncorrect"<<std::endl;
        return false;
    }

    std::string data;
    for(int i=0; i<buf.size();i++)
        data+=buf[i];
    std::string res=aes.work(data,key, true);
    buf.clear();
    for(int i=0; i<res.length();i++)
         buf.push_back(res[i]);
    std::string check; check+=buf[0]; check+=buf[1]; check+=buf[2]; check+=' '; check+=buf[3]; check+=buf[4];
    if(!(check=="Enc ok")){
        buf.clear();
        inf.close();
        std::cout<<"Err: decryption error"<<std::endl;
        return false;
    }
    buf.pop_front();  buf.pop_front();  buf.pop_front();  buf.pop_front();  buf.pop_front();
    inf.close();
    return true;
}
