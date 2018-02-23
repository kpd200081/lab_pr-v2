#include <iostream>
#include "rwworker.h"
#include <cstring>
#include "mbworker.h"

using namespace std;

void case2(RWWorker& rww,char* arg);
int main(int argc,char** argv)
{
    RWWorker rww;
//    rww.set_file("test.hex");
//    rww.set_key("kpd200081");
//    string test="Тест 1.1";
//    for(int i=0;i<test.length();i++)
//        rww.buf.push_back(test[i]);
//    rww.write();
//    if(!rww.init())
//         return -1;
//    std::string data;
//    for(int i=0;i<rww.buf.size();i++)
//        data+=rww.buf[i];
//    cout<<data<<endl;
    switch (argc) {
    case 1:
        rww.set_file("base.hex");
        rww.set_key("kpd200081");
        break;
    case 2:
        case2(rww,argv[1]);
        rww.set_key("kpd200081");
        break;
    case 3:
        rww.set_file(argv[1]);
        rww.set_key(argv[2]);
        break;
    default:
        cout<<"Usage: lab_pr-v2 - key and base name default\n       lab_pr-v2 file_name - key default\n       lab_pr-v2 file_name key - all setted by operator\n";
    }
    if(!rww.init())
        return -1;
    MBWorker mbw(&rww);
    if(mbw.menu()){
        mbw.save();
        rww.write();
    }
    return 0;
}

void case2(RWWorker& rww,char* arg){
    if(strncmp(arg,"-help",5)==0)
        cout<<"Usage: lab_pr-v2 - key and base name default\n       lab_pr-v2 file_name - key default\n       lab_pr-v2 file_name key - all setted by operator\n";
    else
        rww.set_file(arg);
}
