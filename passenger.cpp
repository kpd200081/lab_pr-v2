#include "passenger.h"


Passenger::Passenger(Passenger *cprev, Passenger *cnext, int tr_n, int cr_cn, std::string cfio): ComClass (cprev,cnext,tr_n), Com2Class (cprev, cnext, tr_n, cr_cn)
{
    prev=cprev;
    next=cnext;
    if(cprev!=NULL)
        cprev->next=this;
    if(cnext!=NULL)
        cnext->prev=this;
    fio=cfio;
    data_size=sizeof(int)*2+sizeof(char)*50;
}

Passenger::Passenger(Passenger *cprev, Passenger *cnext):ComClass (cprev, cnext), Com2Class (cprev, cnext)
{
    prev=cprev;
    next=cnext;
    if(cprev!=NULL)
        cprev->next=this;
    if(cnext!=NULL)
        cnext->prev=this;
    data_size=sizeof(int)*2+sizeof(char)*50;
}

Passenger::~Passenger()
{
    if(prev)prev->next=next;
    if(next)next->prev=prev;
}

std::vector<unsigned char> Passenger::getWritebleData()
{
    using namespace std;
    vector<unsigned char> buf;
    ofstream tof("temp.hex", ios::binary|ios::out);
    char cfio[50];
    for(int u=0;u<50;u++){
        cfio[u]=0;
    }
    strncpy(cfio, fio.c_str(),50);
    //tof<<train_number<<car_number;
    tof.write(reinterpret_cast<const char *>(&train_number), sizeof(train_number));
    tof.write(reinterpret_cast<const char *>(&car_number), sizeof(car_number));
    tof.write(cfio,50);
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
    //tif>>train_number>>car_number;
    tif.read(reinterpret_cast<char *>(&train_number), sizeof(train_number));
    tif.read(reinterpret_cast<char *>(&car_number), sizeof(car_number));
    char cfio[50];
    tif.read(cfio,50);
    for(int i=0;i<50;i++){
        if(cfio[i]!='\0'){
            fio+=cfio[i];
        }
    }
    tif.close();
    remove("temp.hex");
}

std::ostream &operator<<(std::ostream &out, Passenger &self)
{
    using namespace std;
    ios init(NULL);
    init.copyfmt(cout);
    cout<<"ФИО: "<<self.fio;
    cout.copyfmt(init);
    cout<<setfill('0')<<"\tПоезд №"<<setw(6)<<self.train_number;
    cout.copyfmt(init);
    cout<<setfill('0')<<"\tВагон №"<<setw(5)<<self.car_number<<endl;
    cout.copyfmt(init);
    return out;
}

int Passenger::getDataSize()
{
    return data_size;
}
