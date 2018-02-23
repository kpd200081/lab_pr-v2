#include <iostream>
#include "rwworker.h"

using namespace std;

int main(int argc,char** argv)
{
    RWWorker rww;
    rww.set_file("test.hex");
    rww.set_key("kpd200081");
    rww.buf.push_back('t'); rww.buf.push_back('e'); rww.buf.push_back('s'); rww.buf.push_back('t'); rww.buf.push_back(' ');  rww.buf.push_back('1'); rww.buf.push_back('.'); rww.buf.push_back('1');
    rww.write();
    if(!rww.init())
         return -1;
    std::string data;
    for(int i=0;i<rww.buf.size();i++)
        data+=rww.buf[i];
    cout<<data<<endl;

    return 0;
}
