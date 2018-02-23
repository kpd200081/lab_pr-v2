#include "train.h"

Train::Train(Train *prev, Train *next, int tr_n, int cr_c, int rout_n): ComClass (prev, next, tr_n)
{
    car_count=cr_c;
    rout_number=rout_n;
    data_size=sizeof(int)*3;
}

Train::Train(Train *prev, Train *next):ComClass (prev, next)
{
    data_size=sizeof(int)*3;
}

std::vector<unsigned char> Train::getWritebleData()
{
    using namespace std;
    vector<unsigned char> buf;
    ofstream tof("temp.hex", ios::binary|ios::out);
    tof<<train_number<<car_count<<rout_number;
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
    tif>>train_number>>car_count>>rout_number;
}

std::ostream &operator<<(std::ostream &out, Train &self)
{
    std::cout<<"Train №"<<self.train_number<<" Rout: "<<self.routs->at(self.rout_number)<<" Full cars "<<self.full_cc<<"/"<<self.car_count<<std::endl;
    return out;
}
