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
    stream.read(reinterpret_cast<char *>(&routs_count), sizeof(routs_count));
    stream.read(reinterpret_cast<char *>(&pass_count), sizeof(pass_count));
    stream.read(reinterpret_cast<char *>(&train_count), sizeof(train_count));
    //routs.reserve(routs_count);
    stream.str(std::string());

    for(i=0;i<routs_count;i++){
        for(int j=0;j<50;j++){
            stream<<rww->buf.front();
            rww->buf.pop_front();
        }
        std::string t;
        //stream>>t;
        char c;
        for(int j=0;j<50;j++){
            stream>>c;
            if(c!=0)
                t+=c;
        }
        routs.push_back(t);
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
            first_t->first=new Car(first_p,NULL,NULL);
            *rww>>*(first_t->first);
        }
        Car* prevc=first_t->first;
        for(int j=1;j<first_t->car_count;j++){
            prevc->next=new Car(first_p,prevc, NULL);
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
            prevt->first=new Car(first_p,NULL,NULL);
            *rww>>*(prevt->first);
        }
        Car* prevc=prevt->first;
        for(int j=1;j<prevt->car_count;j++){
            prevc->next=new Car(first_p,prevc, NULL);
            prevc=prevc->next;
            *rww>>*prevc;
        }
        prevt->last=prevc;
    }
    last_t=prevt;
    updateTrainCarFirstP();
}

void MBWorker::save()
{
    std::stringstream stream;
    //unsigned long length=rout_count*50;
    stream.write(reinterpret_cast<const char *>(&routs_count), sizeof(routs_count));
    stream.write(reinterpret_cast<const char *>(&pass_count), sizeof(pass_count));
    stream.write(reinterpret_cast<const char *>(&train_count), sizeof(train_count));
    char srtbuf[50];
    for(int u=0;u<50;u++){
        srtbuf[u]=0;
    }
    int i;
    for(i=0;i<3*sizeof(int);i++){
        char c;
        stream>>c;
        rww->buf.push_back(c);
    }
    stream.str(std::string());
    for(i=0;i<routs_count;i++){
        strncpy(srtbuf,routs[i].c_str(),50);
        stream.write(srtbuf,50);
        for(int u=0;u<50;u++){
            srtbuf[u]=0;
        }
    }
    routs.clear();
    for(i=0;i<routs_count*50;i++){
        char c;
        stream>>c;
        rww->buf.push_back(c);
    }

    Passenger* curp=first_p;
    while (curp!=NULL) {
        *rww<<*curp;
        if(curp->next!=NULL){
        curp=curp->next;
        delete curp->prev;
        }else{delete curp; break;}
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
            }else{delete curc; break;}
        }
        if(curt->next!=NULL){
//            Car* cur=curt->first;
//            while(cur!=NULL){
//                if(cur->next!=NULL){
//                cur=cur->next;
//                delete cur->prev;
//                }else{
//                    //delete cur;
//                    break;
//                }
//            }
        curt=curt->next;
        delete curt->prev;
        }else{
//            Car* cur=curt->first;
//            while(cur!=NULL){
//                if(cur->next!=NULL){
//                cur=cur->next;
//                delete cur->prev;
//                }else{
//                    //delete cur;
//                    break;
//                }
//            }
            delete curt; break;}
    }
    MENU_INFO
    std::cout<<"Base saved.\n";
    MENU_END
    MENU_END
}

int MBWorker::menu(){
    int input;
    std::cout<<"Что Вы хотите сделать?\n";
    MENU_START
    std::cout<<"1. Продать билеты\n";
    std::cout<<"2. Вывести информацию\n";
    std::cout<<"3. Добавить информацию\n";
    std::cout<<"4. Исправить информацию\n";
    std::cout<<"5. Удалить информацию\n";
    std::cout<<"6. Сохранить и выйти из программы\n";
    std::cout<<"7. Выйти из программы без сохранения\n";
    MENU_END
    std::cout<<"Введите номер соответствующего действия: ";
    input=corInput(7);
    switch(input){
        case 1:
            sell();
            return menu();
        case 2:
            output();
            return menu();
        case 3:
            add();
            return menu();
        case 4:
            correct();
            return menu();
        case 5:
            del();
            return menu();
         case 6:
            return 1;
         case 7:
            return 0;
        }
    return -1;
}


int MBWorker::corInput(int max)
{
    char str[50];
    int inp;
    while(1){
        MENU_INPUT
        scanf("%s",str);
        MENU_END
        inp=StrToInt(str);
        if((inp!=0)&&(inp<=max)&&(inp>0))
            break;
       std::cout<<"Введено некорректное значение. Повторите попытку: ";
    }
    return inp;
}

int MBWorker::StrToInt(char* str){
    int i=0;
    int flag=0;
    if(strlen(str)>6)
        return 0;
    while(str[i]!=0){
        if(str[i]=='1'||str[i]=='2'||str[i]=='3'||str[i]=='4'||str[i]=='5'||str[i]=='6'||str[i]=='7'||str[i]=='8'||str[i]=='9'||str[i]=='0')
            i++;
        else{
            flag=1;
            break;
        }
    }
    if(flag==0)
        return atoi(str);
    else
        return 0;
}

MBWorker::~MBWorker()
{
}

void MBWorker::output(){
    using namespace std;
    cout<<"Что вы хотите вывести?\n";
    MENU_START
    cout<<"1. Направление\n"<<"2. Поезд\n"<<"3. Пассажира\n";
    MENU_END
    std::cout<<"Введите номер соответствующего действия: ";
    int input=corInput(3);
    switch(input){
        case 1:
            outRouts();
            break;
        case 2:
            output_trains();
            break;
        case 3:
            output_passes();
            break;
    }
}

void MBWorker::add(){
    using namespace std;
    cout<<"Что вы хотите добавить?\n";
    MENU_START
    cout<<"1. Направление\n"<<"2. Поезд\n";
    MENU_END
    std::cout<<"Введите номер соответствующего действия: ";
    int input=corInput(2);
    switch(input){
            case 1:
                create_dest();
                break;
            case 2:
                add_train();
                break;
        }
}

void MBWorker::sell(){
    using namespace std;
    if(train_count==0){
        cout<<"Поездов нет.  Вы будите возвращены в меню.\n";
    }
    Train* cur=first_t;
    cout<<"выберете поезд:\n";
    while(cur!=NULL){
        cout<<*cur;
        cur=cur->next;
    }
    cout<<"Введите номер соответствующего поезда: ";
    int tr_n=corInput(999999);
    cur=findTrain(tr_n);
    if(cur==NULL){
        cout<<"Такого поезда нет. Вы будите возвращены в меню.\n";
        return;
    }
    if(cur->full_cc==cur->car_count){
        cout<<"В этом поезде места кончились. Вы будите возвращены в меню.\n";
        return;
    }
    cout<<"Введите номер вагона: ";
    int cr_n=corInput(cur->car_count);
    Car* curc=cur->first;
    for(int i=1;i<cr_n;i++)
        curc=curc->next;
    if(curc->type==Car::CarType::Restaurant){
        cout<<"В этом типе вагонов места не продаются. Вы будите возвращены в меню.\n";
        return;
    }
    if(curc->free_sc==0){
        cout<<"В этом вагоне места кончились. Вы будите возвращены в меню.\n";
        return;
    }
    string name;
    cout<<"Введите ФИО пассажира: ";
    MENU_INPUT
    cin.get();
    getline(cin,name);
    MENU_END
    while(true){
        if(name.length()<=50)
            break;
        cout<<"ФИО слишком длинное. Введите другое: ";
        MENU_INPUT
        cin.get();
        getline(cin,name);
        MENU_END
    }
    Passenger* pas=new Passenger(last_p, NULL,cur->train_number,curc->car_number,name);
    last_p=pas;
    if(first_p==NULL)
        first_p=last_p;
    curc->free_sc--;
    if(curc->free_sc==0)
       cur->full_cc++;
    pass_count++;
    updateTrainCarFirstP();
}


void MBWorker::correct()
{
    using namespace std;
    cout<<"Что вы хотите исправить?\n";
    MENU_START
    cout<<"1. Направление\n"<<"2. Поезд\n"<<"3. Пассажира\n";
    MENU_END
    std::cout<<"Введите номер соответствующего действия: ";
    int input=corInput(3);
    switch(input){
            case 1:
                cor_dest();
                break;
            case 2:
                cor_train();
                break;
            case 3:
                cor_pas();
                break;
        }
}

void MBWorker::del()
{
    using namespace std;
    cout<<"Что вы хотите удалить?\n";
    MENU_START
    cout<<"1. Направление"<<"\033[1;31m"<<"  Внимание! Все поезда следующие этим направлением удалены!\n"<<"\033[0m"<<"\033[1;34m2. Поезд"<<"\033[1;31m"<<"        Внимание! Все пассажиры следующие этим поездом удалены!\n"<<"\033[0m"<<"\033[1;34m3. Пассажира\n";
    MENU_END
    std::cout<<"Введите номер соответствующего действия: ";
    int input=corInput(3);
    switch(input){
            case 1:
                del_dest();
                break;
            case 2:
                del_train();
                break;
            case 3:
                del_pas();
                break;
    }
}

void MBWorker::output_trains()
{
    using namespace std;
    cout<<"Что вы хотите вывести?\n";
    MENU_START
    cout<<"1. Все\n2. Поиск по номеру\n";
    MENU_END
    std::cout<<"Введите номер соответствующего действия: ";
    int input=corInput(2);
    switch (input) {
        case 1:
            outAllTrains();
            break;
        case 2:
            cout<<"Введите номер поезда: ";
            int tr_n=corInput(1000000);
            Train* tr;
            if((tr=findTrain(tr_n))!=NULL)
                cout<<*tr;
            else
                cout<<"Поезда с таким номером нет.  Вы будите возвращены в меню.\n";
            break;
    }
}

void MBWorker::output_passes()
{
    using namespace std;
    cout<<"Что вы хотите вывести?\n";
    MENU_START
    cout<<"1. Все\n2. Поиск по ФИО\n";
    MENU_END
    std::cout<<"Введите номер соответствующего действия: ";
    int input=corInput(2);
    switch (input) {
        case 1:
            outAllPas();
            break;
        case 2:
            outPasByFio();
            break;
    }

}

void MBWorker::outAllTrains()
{
    Train* cur=first_t;
    if(train_count==0)
        std::cout<<"Поездов нет. Вы будите возвращены в меню.\n";
    while(cur!=NULL){
        std::cout<<*cur;
        cur=cur->next;
    }
}

void MBWorker::outAllPas()
{
    Passenger* cur=first_p;
    if(pass_count==0)
         std::cout<<"Пассажиров нет. Вы будите возвращены в меню.\n";
    while(cur!=NULL){
        std::cout<<*cur;
        cur=cur->next;
    }
}

void MBWorker::outRouts()
{
    if(routs_count==0)
        std::cout<<"Направлений нет. Вы будите возвращены в меню.\n";
    for(int i=0;i<routs.size();i++){
        std::cout<<i+1<<". "<<routs[i]<<std::endl;
    }
}

void MBWorker::outPasByFio()
{
    std::vector<Passenger*> res;
    Passenger* cur=first_p;
    std::string fio_to_find;
    if(pass_count==0){
        std::cout<<"Пассажиров нет. Вы будите возвращены в меню.\n";
        return;
    }
    std::cout<<"Введите ФИО для поиска: ";
    MENU_INPUT
    std::cin.get();
    getline(std::cin, fio_to_find);
    MENU_END
    while(cur!=NULL){
        if(cur->fio==fio_to_find)
            res.push_back(cur);
        cur=cur->next;
    }
    if(res.size()==0)
        std::cout<<"Пассажир не найден.\n";
    for(int i=0;i<res.size();i++)
        std::cout<<i+1<<". "<<*res[i];
}

void MBWorker::cor_train()
{
    int j=0;
    Train* cur=first_t;
    if(train_count==0)
        std::cout<<"Поездов нет. Вы будите возвращены в меню.\n";
    std::cout<<"выберете поезд:\n";
    while(cur!=NULL){
        std::cout<<*cur;
        cur=cur->next;
    }
    std::cout<<"Введите номер соответствующего поезда: ";
    int tr_n=corInput(999999);
    cur=findTrain(tr_n);
    if(cur==NULL){
        std::cout<<"Такого поезда нет. Вы будите возвращены в меню.\n";
        return;
    }
    std::cout<<"Что вы хотите исправить?\n"<<"1. Номер\n"<<"2. Направление\n"<<"Если вы хотите изменить вагоны, то удалите и заново создайте поезд.\n";
    std::cout<<"Введите соответствующий номер: ";
    int input=corInput(2);
    switch (input) {
        case 1:
            cor_train_num(cur);
            break;
        case 2:
            cor_train_rout(cur);
            break;
    }
}

void MBWorker::cor_dest()
{
    using namespace std;
    cout<<"Выберете направление:\n";
    for(int i=0;i<routs.size();i++){
        cout<<i+1<<". "<<routs[i]<<std::endl;
    }
    std::cout<<"Введите номер соответствующего направления: ";
    int rt_n=corInput(routs_count);
    cout<<"Введите новое название направления: ";
    string name;
    MENU_INPUT
    cin.get();
    getline(cin,name);
    MENU_END
    bool f=false;
    while(true){
        if(name.length()<=50)
            break;
        cout<<"Название слишком длинное. Введите другое: ";
        MENU_INPUT
        cin.get();
        getline(cin,name);
        MENU_END
    }
    for(int i=0;i<routs.size();i++)
    {
        if(routs[i]==name)
            f=true;
    }
    if(f){
        cout<<"Такое направление уже существует. Вы будите возвращены в меню.\n";
        return;
    }
    routs[rt_n-1]=name;
}

void MBWorker::cor_pas()
{
    using namespace std;
    Passenger* cur=first_p;
    if(pass_count==0){
        cout<<"Пассажиров нет. Вы будите возвращены в меню.\n";
        return;
    }
    int i=1;
    cout<<"Выберете пассажира:\n";
    while(cur!=NULL){
        cout<<i++<<". "<<*cur;
        cur=cur->next;
    }
    int pass_n=corInput(pass_count);
    cur=first_p;
    for(i=1;i<pass_n;i++){
        cur=cur->next;
    }
    string name;
    cout<<"Введите новое ФИО пассажира: ";
    MENU_INPUT
    cin.get();
    getline(cin,name);
    MENU_END
    while(true){
        if(name.length()<=50)
            break;
        cout<<"ФИО слишком длинное. Введите другое: ";
        MENU_INPUT
        cin.get();
        getline(cin,name);
        MENU_END
    }
    cur->fio=name;
}

void MBWorker::del_train()
{
    Train* cur=first_t;
    if(train_count==0)
        std::cout<<"Поездов нет. Вы будите возвращены в меню.\n";
    std::cout<<"выберете поезд:\n";
    while(cur!=NULL){
        std::cout<<*cur;
        cur=cur->next;
    }
    std::cout<<"Введите номер соответствующего поезда: ";
    int tr_n=corInput(999999);
    cur=findTrain(tr_n);
    if(cur==NULL){
        std::cout<<"Такого поезда нет. Вы будите возвращены в меню.\n";
        return;
    }
    Passenger* pas=first_p;
    while (pas!=NULL) {
        if(pas->train_number==tr_n){
            if(pas->next!=NULL){
            pas=pas->next;
            if(pas==last_p)
                last_p=NULL;
            if(pas==first_p)
                first_p==NULL;
            delete pas->prev;
            }else{
                if(pas==last_p)
                    last_p=NULL;
                if(pas==first_p)
                    first_p==NULL;
                delete pas; break;
            }
            pass_count--;
        }else
            pas=pas->next;
    }
//    Car* curc=cur->first;
//    while(curc!=NULL){
//        if(curc->next!=NULL){
//        curc=curc->next;
//        delete curc->prev;
//        }else{
//            //delete curc;
//            break;
//        }
//    }
    if(cur==last_t)
        last_t=NULL;
    if(cur==first_t)
        first_t==NULL;
    delete cur;
    train_count--;
    updateTrainCarFirstP();
}

void MBWorker::del_dest()
{
    using namespace std;
    cout<<"Выберете направление:\n";
    for(int i=0;i<routs.size();i++){
        cout<<i+1<<". "<<routs[i]<<std::endl;
    }
    std::cout<<"Введите номер соответствующего направления: ";
    int rt_n=corInput(routs_count);
    Train* cur=first_t;
    while(cur!=NULL){
        if(cur->rout_number==rt_n){
            if(cur->next!=NULL){
                Passenger* pas=first_p;
                while (pas!=NULL) {
                    if(pas->train_number==cur->train_number){
                        if(pas->next!=NULL){
                        pas=pas->next;
                        delete pas->prev;
                        }else{
                            delete pas; break;
                        }
                        pass_count--;
                    }else
                        pas=pas->next;
                }
//                Car* curc=cur->first;
//                while(curc!=NULL){
//                    if(curc->next!=NULL){
//                    curc=curc->next;
//                    delete curc->prev;
//                    }else{
//                        //delete curc;
//                        break;
//                    }
//                }
                if(cur==last_t)
                    last_t=NULL;
                if(cur==first_t)
                    first_t==NULL;
            cur=cur->next;
            delete cur->prev;
            }else{
                Passenger* pas=first_p;
                while (pas!=NULL) {
                    if(pas->train_number==cur->train_number){
                        if(pas->next!=NULL){
                            if(pas==last_p)
                                last_p=NULL;
                            if(pas==first_p)
                                first_p==NULL;
                        pas=pas->next;
                        delete pas->prev;
                        }else{
                            if(pas==last_p)
                                last_p=NULL;
                            if(pas==first_p)
                                first_p==NULL;
                            delete pas; break;
                        }
                        pass_count--;
                    }else
                        pas=pas->next;
                }
//                Car* curc=cur->first;
//                while(curc!=NULL){
//                    if(curc->next!=NULL){
//                    curc=curc->next;
//                    delete curc->prev;
//                    }else{
//                        //delete curc;
//                        break;
//                    }
//                }
                if(cur==last_t)
                    last_t=NULL;
                if(cur==first_t)
                    first_t==NULL;
                delete cur; break;
            }
            train_count--;
        }else
            cur=cur->next;
    }
    cur=first_t;
    while(cur!=NULL){
        if(cur->rout_number>rt_n){
            cur->rout_number--;
        }
    }
    for(int i=rt_n;i<routs_count;i++){
        routs[i]=routs[i+1];
    }
    routs.pop_back();
    routs_count--;
    updateTrainCarFirstP();
}

void MBWorker::del_pas()
{
    using namespace std;
    Passenger* cur=first_p;
    if(pass_count==0){
        cout<<"Пассажиров нет. Вы будите возвращены в меню.\n";
        return;
    }
    int i=1;
    cout<<"Выберете пассажира:\n";
    while(cur!=NULL){
        cout<<i++<<". "<<*cur;
        cur=cur->next;
    }
    int pass_n=corInput(pass_count);
    cur=first_p;
    for(i=1;i<pass_n;i++){
        cur=cur->next;
    }
    if(cur==last_p)
        last_p=NULL;
    if(cur==first_p)
        first_p==NULL;
    delete cur;
    pass_count--;
    updateTrainCarFirstP();
}

void MBWorker::create_dest()
{
    using namespace std;
    string name;
    cout<<"Введите название нового направления: ";
    MENU_INPUT
    cin.get();
    getline(cin,name);
    MENU_END
    bool f=false;
    while(true){
        if(name.length()<=50)
            break;
        cout<<"Название слишком длинное. Введите другое: ";
        MENU_INPUT
        cin.get();
        getline(cin,name);
        MENU_END
    }
    for(int i=0;i<routs.size();i++)
    {
        if(routs[i]==name)
            f=true;
    }
    if(f){
        cout<<"Такое направление уже существует. Вы будите возвращены в меню.\n";
        return;
    }
    routs_count++;
    routs.push_back(name);
}

void MBWorker::add_train()
{
    using namespace std;
    if(routs_count==0){
        cout<<"Сначала добавьте направление. Вы будите возвращены в меню.\n";
        return;
    }
    cout<<"Выберете направление:\n";
    outRouts();
    std::cout<<"Введите соответствующий номер: ";
    int r_n=corInput(routs_count);
    cout<<"Введите номер поезда: ";
    int tr_n=corInput(999999);
    if(findTrain(tr_n)!=NULL){
        cout<<"Поезд с таким номером уже существует.  Вы будите возвращены в меню.\n";
        return;
    }
    cout<<"Введите количество вагонов: ";
    int cr_c=corInput(99999);
    Train* tr=new Train(last_t, NULL,tr_n, cr_c, r_n);
    last_t=tr;
    if(first_t==NULL)
        first_t=last_t;
    train_count++;
    last_t->routs=&routs;
    updateTrainCarFirstP();
}

Train *MBWorker::findTrain(int tr_n)
{
    Train* cur=first_t;
    Train* res=NULL;
    while (cur!=NULL) {
            if(cur->train_number==tr_n)
                res=cur;
            cur=cur->next;
    }
    return res;
}

void MBWorker::updateTrainCarFirstP()
{
    Train* cur=first_t;
    while(cur!=NULL){
        cur->updateCarFirstP(first_p);
        cur=cur->next;
    }
}

void MBWorker::cor_train_rout(Train *tr)
{
    using namespace std;
    cout<<"Выберете новое направление:\n";
    for(int i=0;i<routs.size();i++){
        cout<<i+1<<". "<<routs[i]<<std::endl;
    }
    std::cout<<"Введите номер соответствующего направления: ";
    int rt_n=corInput(routs_count);
    tr->rout_number=rt_n;
}

void MBWorker::cor_train_num(Train *tr)
{
    using namespace std;
    cout<<"Выберете новый номер: ";
    int tr_n=corInput(999999);
    if(findTrain(tr_n)!=NULL){
        cout<<"Поезд с таким номером уже существует.  Вы будите возвращены в меню.\n";
        return;
    }
    Passenger* cur=first_p;
    while(cur!=NULL){
        if(cur->train_number==tr->train_number)
            cur->train_number=tr_n;
        cur=cur->next;
    }
    Car* ccar=tr->first;
    while(ccar!=NULL){
        ccar->train_number=tr_n;
        ccar=ccar->next;
    }
    tr->train_number=tr_n;
}

