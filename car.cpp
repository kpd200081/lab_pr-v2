#include "car.h"

Car::Car(Car* prev, Car* next, int cr_n, int tr_n, char ctype, int csit_count): ComClass (prev,next,tr_n), Com2Class (prev, next, tr_n, cr_n)
{
    type=ctype;
    sit_count=csit_count;
    data_size=sizeof(int)*4+sizeof(char);
}

Car::Car(Car* prev, Car* next):ComClass(prev, next), Com2Class(prev, next)
{
    data_size=sizeof(int)*4+sizeof(char);
}

Car::~Car(){
    if(prev)prev->next=next;
    if(next)next->prev=prev;
}

std::vector<unsigned char> Car::getWritebleData()
{
    using namespace std;
    vector<unsigned char> buf;
    ofstream tof("temp.hex", ios::binary|ios::out);
    tof<<train_number<<car_number<<sit_count<<free_sc<<type;
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
    tif>>train_number>>car_number>>sit_count>>free_sc>>type;
}

std::ostream &operator<<(std::ostream &out, Car &self)
{
    std::cout<<"Train №"<<self.train_number<<"Car №"<<self.car_number<<" Type: ";
    switch (self.type) {
        case 0:
            std::cout<<"Seat";
            break;
        case 1:
            std::cout<<"Compartment";
            break;
        case 2:
            std::cout<<"Restaurant";
    }
    if(self.type!=2)
        std::cout<<" Free seats "<<self.free_sc<<"/"<<self.sit_count<<std::endl;
    return out;
}
