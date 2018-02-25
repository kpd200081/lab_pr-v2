#include "train.h"

Train::Train(Train *cprev, Train *cnext, int tr_n, int cr_c, int rout_n): ComClass (cprev, cnext, tr_n)
{
    prev=cprev;
    next=cnext;
    if(cprev!=NULL)
        cprev->next=this;
    if(cnext!=NULL)
        cnext->prev=this;
    car_count=cr_c;
    rout_number=rout_n;
    data_size=sizeof(int)*4;
    full_cc=0;
    first=NULL;
    last=NULL;
    using namespace std;
    if(cr_c>0){
        int s_c;
        Car::CarType t;
        cout<<"Выберете тип вагона:\n";
        cout<<"1. Плацкарт\n";
        cout<<"2. Купе\n";
        cout<<"3. Вагон-ресторан\n";
        cout<<"Введите соответствующий номер: ";
        int t_n=MBWorker::corInput(3);
        switch (t_n) {
            case 1:
                t=Car::CarType::Seat;
                break;
            case 2:
                t=Car::CarType::Compartment;
                break;
            case 3:
                t=Car::CarType::Restaurant;
                break;
            }
        if(t_n==3){
            s_c=0;
            full_cc++;
        }
        else{
            cout<<"Введите количество мест в вагоне: ";
            s_c=MBWorker::corInput(999);
        }
        Car* car=new Car(NULL,NULL,1, tr_n, t, s_c);
        first=car;
    }
    Car* cur=first;
    for(int i =1;i<car_count;i++){
        int s_c;
        Car::CarType t;
        cout<<"Выберете тип вагона:\n";
        cout<<"1. Плацкарт\n";
        cout<<"2. Купе\n";
        cout<<"3. Вагон-ресторан\n";
        cout<<"Введите соответствующий номер: ";
        int t_n=MBWorker::corInput(3);
        switch (t_n) {
            case 1:
                t=Car::CarType::Seat;
                break;
            case 2:
                t=Car::CarType::Compartment;
                break;
            case 3:
                t=Car::CarType::Restaurant;
                break;
            }
        if(t_n==3){
            s_c=0;
            full_cc++;
        }
        else{
            cout<<"Введите количество мест в вагоне: ";
            s_c=MBWorker::corInput(999);
        }
        Car* car=new Car(cur,NULL,i+1, tr_n, t, s_c);
        cur=car;
    }
    last=cur;
}

Train::Train(Train *cprev, Train *cnext):ComClass (cprev, cnext)
{
    prev=cprev;
    next=cnext;
    if(cprev!=NULL)
        cprev->next=this;
    if(cnext!=NULL)
        cnext->prev=this;
    data_size=sizeof(int)*4;
    first=NULL;
    last=NULL;
}

Train::~Train()
{
    if(prev)prev->next=next;
    if(next)next->prev=prev;
}

std::vector<unsigned char> Train::getWritebleData()
{
    using namespace std;
    vector<unsigned char> buf;
    ofstream tof("temp.hex", ios::binary|ios::out);
    //tof<<train_number<<car_count<<rout_number;
    tof.write(reinterpret_cast<const char *>(&train_number), sizeof(train_number));
    tof.write(reinterpret_cast<const char *>(&car_count), sizeof(car_count));
    tof.write(reinterpret_cast<const char *>(&full_cc), sizeof(full_cc));
    tof.write(reinterpret_cast<const char *>(&rout_number), sizeof(rout_number));
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

void Train::setData(std::vector<unsigned char> & data)
{
    using namespace std;
    ofstream tof("temp.hex", ios::binary|ios::out);
    for(int i=0;i<data.size();i++)
        tof.put(data[i]);
    tof.close();
    ifstream tif("temp.hex",ios::binary|ios::in);
    //tif>>train_number>>car_count>>rout_number;
    tif.read(reinterpret_cast<char *>(&train_number), sizeof(train_number));
    tif.read(reinterpret_cast<char *>(&car_count), sizeof(car_count));
    tif.read(reinterpret_cast<char *>(&full_cc), sizeof(full_cc));
    tif.read(reinterpret_cast<char *>(&rout_number), sizeof(rout_number));
    tif.close();
    remove("temp.hex");
}

void Train::updateCarFirstP(Passenger * f)
{
    Car* cur=first;
    while (cur!=NULL) {
        cur->firstp=f;
        //if()
        cur=cur->next;
    }
}

std::ostream &operator<<(std::ostream &out, Train &self)
{
    using namespace std;
    ios init(NULL);
    init.copyfmt(cout);
    cout<<setfill('0')<<"Поезд №"<<setw(6)<<self.train_number;
    cout.copyfmt(init);
    cout<<"\tНаправление: "<<(self.routs)->at(self.rout_number-1);
    cout.copyfmt(init);
    cout<<setfill('0')<<"\t\tПолные вагоны: "<<setw(5)<<self.full_cc<<setw(1)<<"/"<<setw(5)<<self.car_count<<std::endl;
    cout.copyfmt(init);
    Car* cur=self.first;
    while (cur!=NULL) {
        cout<<"\t"<<*cur;
        cur=cur->next;
    }
    return out;
}

int Train::getDataSize()
{
    return data_size;
}
