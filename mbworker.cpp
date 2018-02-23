#include "mbworker.h"

MBWorker::MBWorker(RWWorker* crww)
{
    rww=crww;
    first_p=NULL;
    last_p=NULL;
    first_t=NULL;
    last_t=NULL;
}

void MBWorker::init()
{
    std::stringstream stream;
    int i;
    for(i=0;i<sizeof(int)*3;i++){
        stream<<rww->buf.front();
        rww->buf.pop_front();
    }
    stream>>rout_count>>pass_count>>train_count;
    routs.reserve(rout_count);
    stream.str(std::string());

    for(i=0;i<rout_count;i++){
        for(int j=0;j<100;j++){
            stream<<rww->buf.front();
            rww->buf.pop_front();
        }
        stream>>routs[i];
        stream.str(std::string());
    }

    if(pass_count>0){
        first_p=new Passenger(NULL,NULL);
        *rww>>*first_p;
    }
    Passenger* prevp=first_p;
    for(i=1;i<pass_count;i++){
        prevp->next=new Passenger(prevp,NULL);
        prevp=prevp->next;
        *rww>>*prevp;
    }
    last_p=prevp;

    if(train_count>0){
        first_t=new Train(NULL,NULL);
        *rww>>*first_t;
        first_t->routs=&routs;
        if(first_t->car_count>0){
            first_t->first=new Car(NULL,NULL);
            *rww>>*(first_t->first);
        }
        Car* prevc=first_t->first;
        for(int j=1;j<first_t->car_count;j++){
            prevc->next=new Car(prevc, NULL);
            prevc=prevc->next;
            *rww>>*prevc;
        }
        first_t->last=prevc;
    }
    Train* prevt=first_t;
    for(i=1;i<train_count;i++){
        prevt->next=new Train(prevt,NULL);
        prevt=prevt->next;
        prevt->routs=prevt->prev->routs;
        *rww>>*prevt;
        if(prevt->car_count>0){
            prevt->first=new Car(NULL,NULL);
            *rww>>*(prevt->first);
        }
        Car* prevc=prevt->first;
        for(int j=1;j<prevt->car_count;j++){
            prevc->next=new Car(prevc, NULL);
            prevc=prevc->next;
            *rww>>*prevc;
        }
        prevt->last=prevc;
    }
}

int MBWorker::menu(){



    return 1;
}

void MBWorker::save()
{
    std::stringstream stream;
    unsigned long length=rout_count*100;
    char srtbuf[100];
    for(int u=0;u<100;u++){
        srtbuf[u]=0;
    }
    int i;
    for(i=0;i<rout_count;i++){
        strncpy(srtbuf, routs[i].c_str(),routs[i].length()<100?routs[i].length():100);
        for(int j=0;j<100;j++){
            stream<<srtbuf[j];
        }
        for(int u=0;u<100;u++){
            srtbuf[u]=0;
        }
    }
    routs.clear();

    Passenger* curp=first_p;
    while (curp!=NULL) {
        *rww<<*curp;
        if(curp->next!=NULL){
        curp=curp->next;
        delete curp->prev;
        }else{delete curp;}
    }

    Train* curt=first_t;
    while(curt!=NULL){
        *rww<<*curt;
        Car* curc=curt->first;
        while(curc!=NULL){
            *rww<<*curc;
            if(curc->next!=NULL){
            curc=curc->next;
            delete curc->prev;
            }else{delete curc;}
        }
        if(curt->next!=NULL){
        curt=curt->next;
        delete curt->prev;
        }else{delete curt;}
    }
}

MBWorker::~MBWorker()
{
}
