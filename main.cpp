#include <iostream>
#include "rwworker.h"
#include <cstring>
#include "mbworker.h"

using namespace std;

void case2(RWWorker& rww,char* arg);
int main(int argc,char** argv)
{
    RWWorker rww;
    switch (argc) {
    case 1:
        rww.set_file("base.hex");
        break;
    case 2:
        case2(rww,argv[1]);
        break;
    default:
        cout<<"Usage: lab_pr-v2 - base name default\n       lab_pr-v2 file_name - setted by user\n";
    }
    if(!rww.init())
        return -1;
    MBWorker mbw(&rww);
    mbw.init();
    if(mbw.menu()){
        mbw.save();
        rww.write();
    }
    return 0;
}

void case2(RWWorker& rww,char* arg){
    if(strncmp(arg,"-help",5)==0)
        cout<<"Usage: lab_pr-v2 - base name default\n       lab_pr-v2 file_name - setted by user\n";
    else
        rww.set_file(arg);
}
