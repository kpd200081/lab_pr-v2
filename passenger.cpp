#include "passenger.h"


Passenger::Passenger(Passenger *prev, Passenger *next, int tr_n, int cr_cn, std::string cfio): ComClass (prev,next,tr_n), Com2Class (prev, next, tr_n, cr_cn)
{
    fio=cfio;
    data_size=sizeof(int)*2+sizeof(char)*100;
}

Passenger::Passenger(Passenger *prev, Passenger *next):ComClass (prev, next), Com2Class (prev, next)
{
    data_size=sizeof(int)*2+sizeof(char)*100;
}

std::vector<unsigned char> Passenger::getWritebleData()
{
    using namespace std;
    vector<unsigned char> buf;
    ofstream tof("temp.hex", ios::binary|ios::out);
    char cfio[100];
    for(int u=0;u<100;u++){
        cfio[u]=0;
    }
    strncpy(cfio, fio.c_str(),fio.length()<100?fio.length():100);
    tof<<train_number<<car_number;
    for(int i=0;i<100;i++)
        tof<<cfio[i];
    tof.close();
    ifstream tif("temp.hex",ios::binary|ios::in);
    char c;
    while(tif.get(c)){
        buf.push_back(c);
    }
    tif.close();
    remove("temp.hex");
    return buf;
}

void Passenger::setData(std::vector<unsigned char> & data)
{
    using namespace std;
    ofstream tof("temp.hex", ios::binary|ios::out);
    for(int i=0;i<data.size();i++)
        tof.put(data[i]);
    tof.close();
    ifstream tif("temp.hex",ios::binary|ios::in);
    tif>>train_number>>car_number;
    char cfio[100];
    for(int i=0;i<100;i++)
        tif>>cfio[i];
    for(int i=0;i<100;i++){
        if(cfio[i]!='\0'){
            fio+=cfio[i];
        }
    }
}

std::ostream &operator<<(std::ostream &out, Passenger &self)
{
    std::cout<<"Passenger: "<<self.fio<<" Train №"<<self.train_number<<" Car №"<<self.car_number<<std::endl;
    return out;
}
