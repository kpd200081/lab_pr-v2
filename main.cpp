#include <iostream>
#include "rwworker.h"

using namespace std;

int main()
{
    RWWorker rww;
    rww.set_file("test.hex");
    rww.set_key(" ");
    if(!rww.init()){
        cout<<"Error"<<endl; return -1;}
    for(int i=0;i<rww.buf.size();i++)
        cout<<rww.buf[i];
    cout<<endl;
    cout << "Hello World!" << endl;
    return 0;
}
