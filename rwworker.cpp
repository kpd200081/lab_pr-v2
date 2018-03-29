#include "rwworker.h"

RWWorker::RWWorker()
{

}

void RWWorker::set_file(std::string c_name)
{
    name=c_name;
}

void RWWorker::write()
{
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
    using namespace std;
    MENU_INFO
    cout<<"File not exist. It will be created.\n";
    MENU_END
    ofstream tof("temp.hex", ios::binary|ios::out);
    int temp=0;
    tof.write(reinterpret_cast<const char *>(&temp),sizeof(temp));
    tof.write(reinterpret_cast<const char *>(&temp),sizeof(temp));
    tof.write(reinterpret_cast<const char *>(&temp),sizeof(temp));
    tof.close();
    ifstream tif("temp.hex",ios::binary|ios::in);
    char c;
    while(tif.get(c)){
        buf.push_back(c);
    }
    tif.close();
    remove("temp.hex");
    write();
}

RWWorker::~RWWorker()
{}

//
RWWorker &operator<<(RWWorker& self, ComClass& obj)
{
    std::vector<unsigned char> t=obj.getWritebleData();
    for(int i=0;i<t.size();i++)
        self.buf.push_back(t[i]);
    return self;
}

//
RWWorker &operator>>(RWWorker& self, ComClass& obj)
{
    std::vector<unsigned char> t;
    t.reserve(obj.getDataSize());
    for(int i=0;i<obj.getDataSize();i++){
        t.push_back((self.buf.front()));
        self.buf.pop_front();
      }
    obj.setData(t);
    return self;
}



bool RWWorker::init()
{
    if(name.c_str()==NULL){
        MENU_ERROR
        std::cout<<"Err: no data"<<std::endl;
        MENU_END
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
        MENU_ERROR
        std::cout<<"Err: check sum uncorrect"<<std::endl;
        MENU_END
        return false;
    }
    inf.close();
    return true;
}
