#include "car.h"

Car::Car(Car* cprev, Car* cnext, int cr_n, int tr_n, CarType ctype, int csit_count): ComClass (cprev,cnext,tr_n), Com2Class (cprev, cnext, tr_n, cr_n)
{
    prev=cprev;
    next=cnext;
    if(cprev!=NULL)
        cprev->next=this;
    if(cnext!=NULL)
        cnext->prev=this;
    //firstp=f;
    type=ctype;
    sit_count=csit_count;
    free_sc=csit_count;
    data_size=sizeof(int)*4+sizeof(CarType);
}

Car::Car(Passenger* f,Car* cprev, Car* cnext):ComClass(cprev, cnext), Com2Class(cprev, cnext)
{
    prev=cprev;
    next=cnext;
    if(cprev!=NULL)
        cprev->next=this;
    if(cnext!=NULL)
        cnext->prev=this;
    firstp=f;
    data_size=sizeof(int)*4+sizeof(CarType);
}

Car::~Car()
{
        if(prev)prev->next=next;
        if(next)next->prev=prev;
}


std::vector<unsigned char> Car::getWritebleData()
{
    using namespace std;
    vector<unsigned char> buf;
    ofstream tof("temp.hex", ios::binary|ios::out);
    //tof<<train_number<<car_number<<sit_count<<free_sc<<type;
    tof.write(reinterpret_cast<const char *>(&train_number), sizeof(train_number));
    tof.write(reinterpret_cast<const char *>(&car_number), sizeof(car_number));
    tof.write(reinterpret_cast<const char *>(&sit_count), sizeof(sit_count));
    tof.write(reinterpret_cast<const char *>(&free_sc), sizeof(free_sc));
    tof.write(reinterpret_cast<const char *>(&type), sizeof(type));
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

void Car::setData(std::vector<unsigned char> & data)
{
    using namespace std;
    ofstream tof("temp.hex", ios::binary|ios::out);
    for(int i=0;i<data.size();i++)
        tof.put(data[i]);
    tof.close();
    ifstream tif("temp.hex",ios::binary|ios::in);
    //tif>>train_number>>car_number>>sit_count>>free_sc>>type;
    tif.read(reinterpret_cast<char *>(&train_number), sizeof(train_number));
    tif.read(reinterpret_cast<char *>(&car_number), sizeof(car_number));
    tif.read(reinterpret_cast<char *>(&sit_count), sizeof(sit_count));
    tif.read(reinterpret_cast<char *>(&free_sc), sizeof(free_sc));
    tif.read(reinterpret_cast<char *>(&type), sizeof(type));
    tif.close();
    remove("temp.hex");
}

void Car::outPass()
{
    int j=0;
    Passenger* cur=firstp;
    while(cur!=NULL){
        if(cur->train_number==train_number&&cur->car_number==car_number){
            std::cout<<"\t\t"<<j+1<<". "<<*cur;
            j++;
        }
        cur=cur->next;
    }
}

std::ostream &operator<<(std::ostream &out, Car &self)
{
    using namespace std;
    ios init(NULL);
    init.copyfmt(cout);
    cout<<setfill('0')<<"Поезд №"<<setw(6)<<self.train_number;
    cout.copyfmt(init);
    cout<<setfill('0')<<"\tВагон №"<<setw(5)<<self.car_number;
    cout.copyfmt(init);
    cout<<"\tТип: ";
    cout<<setw(8);
    switch (self.type) {
        case Car::CarType::Seat:
            cout<<"Плацкарт";
            break;
        case Car::CarType::Compartment:
            cout<<"Купе";
            break;
        case Car::CarType::Restaurant:
            cout<<"Ресторан";
    }
    cout.copyfmt(init);
    if(self.type!=2)
        cout<<setfill('0')<<"\tСвободные места:"<<setw(3)<<self.free_sc<<setw(1)<<"/"<<setw(3)<<self.sit_count;
    cout<<endl;
    self.outPass();
    cout.copyfmt(init);
    return out;
}

int Car::getDataSize()
{
    return data_size;
}
