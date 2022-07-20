#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;

int checkoplist(int node);
int checkll(int node,int edgelength);
int shortestPath();
void Cities();
void display_distance(int s,int d);

template <class T>
T get_input(const string &strQuery);

vector<string>V1;
vector<string>V2;

class user{
    public:
        string username,password;
        virtual int Login()=0;
};

class Admin:public user
{       
    public:     
        string  num, busCompany, busType, from, to, distance;
        char name[30];
int total_seats,fare;   
int Login();
int adminView();
int registerBus();
void deleteBus();
int checkListOfBusesRegistered();
int checkListOfPassengersRegistered();
};

class passenger:public user
{   
    public:
        string name,from,to;
        int age;
        int Login();
        string get_username();
        string get_password();
        void save_user(const string &username, const string &password);
        void login_user();
        void register_user();
        void main_menu();
        void reservation();
        void cancellation();
        void book_det();
        void display(string name);
};

class Date{
    public:
        unsigned int date;
        unsigned int month;
        unsigned int year;
}depart; 

//admin
int Admin::Login()
{   
    tag:
    system("CLEAR");
    cout<<"\n -------------------- Admin Login -----------------";  
string username;
    string password;
    int n[2];
    int i;
    int x;
    for(i=0;i<2;i++)
    {   x=rand()%10;
        n[i]=x; 
    }   
    int sm;
    int smtmp;
    sm=n[0]+n[1];
    cout<<"\n Enter username : ";
    cin>>username;
    cout<<"\n Enter password : ";
    cin>>password;
    cout<<"Check if you are not a robot:\n";
    cout<<n[0]<<" + "<<n[1]<<" = ";
    cin>>smtmp;
    if(smtmp==sm)
    {   
        if(username=="Ayanakouji" && password=="21092003") 
        {
            adminView();
            getchar();  
           }   
           else
           {
            cout<<"\n Error ! Invalid Credintials..";   
            cout<<"\n Press any key for main menu ";
            getchar();getchar();
          }
    }
    else{
        cout<<"\nAre you a Robot !!!";
        cout<<"\nPress any key to Try Again\n";
        getchar(); getchar();
        goto tag;
        }
   return 0;
}
int Admin::adminView()
{   
    int goBack = 0;
    while(1)
    {
        system("clear");
        cout<<"\n 1 Register a Bus";
        cout<<"\n 2 Delete a registered Bus";
        cout<<"\n 3 Check List of Registered Buses";
        cout<<"\n 4 Check List of Registered Passengers";
        cout<<"\n 0. Go Back <- \n";
        int choice;

        cout<<"\n Enter you choice: ";
        cin>>choice;
        

        switch(choice)
        {
            case 1: registerBus();break;  
            case 2: deleteBus(); break;
            case 3: checkListOfBusesRegistered(); 
                    break;
            case 4: checkListOfPassengersRegistered(); 
                    break; 
            case 0: goBack = 1;break;
default: cout<<"\n Invalid choice. Enter again ";                
            getchar();              
       }   
       if(goBack == 1)
       {
        break; 
           }    
   }
   return 0;
}

void Admin::deleteBus()
{
    int flag=0;
    int ctr=0;
    string line,b_name;

    cout<<"\n Enter the name of the Bus to be deleted \t";
    cin>>b_name;

    ifstream fin;
    ofstream fout;
    fin.open("db_bus.csv",ios::in);
    if (!fin)
        {cout<<"\nFile not Found";
         cout<<"\nPress any key to continue..."<<endl;
         getchar();
         getchar();
        }
    else{fout.open("tempfile.csv",ios::out);
        fin.seekg(0);
        while(!fin.eof()){
                int i=0;
                getline(fin,line,'\n');
                string s="";
                while(line[i] != ','){
                    s+=line[i];
                    i++;
                }
                if(s != b_name){
                    if(flag == 0){
                        fout<<line<<endl;
                        flag=1;
                    }
                    else
                        fout<<endl<<line;

                }
                else if(s==b_name)
                {
                    ctr++;
                }
        }
        fin.close();
        fout.close();
        remove("db_bus.csv");
        
        rename("tempfile.csv","db_bus.csv");
        if(ctr==0)
        {
            cout<<endl<<"Cannot delete record..."<<endl;
            cout<<"Record not found !"<<endl;
            cout<<"Press any key to continue..."<<endl;
            getchar();
            getchar();
        }
        else {
            cout<<"Deletion Successful"<<endl;
            cout<<"Press any key to continue..."<<endl;
            getchar();
            getchar();
        }
    }
}

int Admin::checkListOfBusesRegistered(){
    cout<<"\n ---------- List of Registere Busesd ----------- \n";

    ifstream read;
    read.open("db_bus.csv");
    string line;
    while(read.good())
    {
        getline(read,line,',');
        if(line=="")break;
        cout<<"Bus name : "<<line<<endl;
        getline(read,line,',');
        cout<<"Bus number : "<<line<<endl;
        getline(read,line,',');
        cout<<"Bus company : "<<line<<endl;
        getline(read,line,',');
        cout<<"Bus type : "<<line<<endl;
        getline(read,line,',');
        cout<<"From : "<<line<<endl;
        getline(read,line,',');
        cout<<"To : "<<line<<endl;
        getline(read,line,',');
        cout<<"Total distance : "<<line<<endl;
        getline(read,line,',');
        cout<<"Total fare : "<<line<<endl;
        getline(read,line,'\n');
        cout<<"Total number of seats : "<<line;
        cout<<"\n--------------------------------------------------------------------------------------------------------\n";
    }
    read.close();
    cout<<"\n Please press any key to continue..";
    getchar(); getchar();
    return 0;
}


int Admin::checkListOfPassengersRegistered(){
    cout<<"\n ---------- List of Registered Passengers ----------- \n";

    
    ifstream read;
    read.open("passenger.csv");
    string line;
        while(read.good())
    {
        getline(read,line,',');
        cout<<"Passenger's name : "<<line<<endl;
        getline(read,line,',');
        cout<<"Passenger's Age : "<<line<<endl;
        getline(read,line,',');
        cout<<"Depature City : "<<line<<endl;
        getline(read,line,',');
        cout<<"Arrival City : "<<line<<endl;
        getline(read,line,'\n');
        cout<<"Date of Travel : "<<line<<endl;
        cout<<"--------------------------------------------------------------------------------------------------------"<<endl;
    }

    read.close();
    cout<<"\n Please press any key to continue..";
    getchar(); getchar();
    return 0;
}

int Admin::registerBus()
{
    cout<<"\n ----- Info to Register Bus ---- \n";

    cout<<"\n Enter Name of the Bus: ";     cin>>name;

    cout<<"\n Enter Number of the Bus : ";     cin>>num;

    cout<<"\n Enter Company of the Bus : ";     cin>>busCompany;

    getchar();

    char add[100];
    cout<<"\n Enter Bus Type :\n1.Seater    2.Sleeper   3.A/C \t";     cin.getline(add, 100);

    cout<<"\n Depature City :\t"; cin>>from;

    cout<<"\n Arrival City  :\t"; cin>>to;

    cout<<"\n Enter total distance :\t";    cin>>distance;

    cout<<"\n Total Fare :\t";  cin>>fare;

    cout<<"\n Total Number Of Seats of the Bus :\t";        cin>>total_seats;
    //check if record already exist..
    ifstream read;
    read.open("db_bus.csv");

    if(read)
    {      int recordFound=0;
       string line;
            while(getline(read, line,',')) {
            if(line == name )
            {
                recordFound = 1 ;
                break;
            }
        }
        if(recordFound == 1)
        {
            cout<<"\n Bus already Registered. Please choose another name";
            getchar();
            read.close();
            return 0;
        }
    }
    read.close();

    ofstream out1;
    out1.open("db_bus.csv", ios::app);
    out1<<name<<",";    
    out1<<num<<",";
    out1<<busCompany<<",";  
    out1<<add<<",";
    out1<<from<<",";    out1<<to<<",";
    out1<<distance<<",";
    out1<<fare<<",";    
    out1<<total_seats<<"\n";
    out1.close();

    cout<<"\n Bus Registered Successfully !!";

        cout<<"\n Please any key to continue..";
    getchar(); getchar();
    return 0;
}


//passenger

template <class T>
T get_input(const string &strQuery)
{
    cout << strQuery << "\n> ";
    T out = T();

    while (!(cin >> out)) {
        cin.clear();
        cout << "Error!" "\n";
        cout << strQuery << "\n> ";
    }

    return out;
}

int passenger::Login()
{   
    passenger s;
    system("CLEAR");
    cout<<"\n -------------------- Passenger System ----------------- \n";  
    main_menu();

    return 0; 
}

void passenger::main_menu()
{
    int choice = get_input <int>(
        "Hello, Would you like to log in or register?" "\n"
        "[1] Register" "\n"
        "[2] Login" "\n"
        "[3] Exit");

    switch (choice)
    {
    case 1:
        register_user();
        break;
    case 2:
        login_user();
        break;
    }
}

void passenger::register_user()
{
    string username = get_username();
    string password = get_password();
    save_user(username, password);
}

void passenger::save_user(const string &username, const string &password)
{
   int i =0;
    ofstream file;
    file.open("login.csv",ios::app);

        V1.push_back(username);
        V2.push_back(password);
    
    cout<<V1[i]<<" "<<V2[i]<<" "<<endl;
    file << V1[i]<<",";
    file << V2[i] << "\n";
    i++;
    file.close();
}

string passenger::get_password()
{
    string password1 = get_input <string> ("Please enter your password.");
    string password2 = get_input <string> ("Please re-enter your password.");

    while (password1 != password2) {
        cout << "Error! Passwords do not match." "\n";
        password1 = get_input <string>("Please enter your password.");
        password2 = get_input <string>("Please re-enter your password.");
    }

    return password1;
}

string passenger::get_username()
{
    string username = get_input <string>("Please enter a username.");
    cout << "Username: \"" << username << "\"\n";

    while (get_input <int>("Confirm? [0|1]") != 1) {
        username = get_input <string>("Please enter a username.");
        cout << "Username: \"" << username << "\"\n";
    }
    
    return username;
}

void passenger::login_user()
{
    passenger p1;
    int f=0;
    int choice;
    string u="";
    string p="";
    tag:
    label:
    int n[2];
    int i;
    int x;
    for(i=0;i<2;i++)
    {
        x=rand()%10;
        n[i]=x;
        
    }   
    int sm;
    int smtmp;
    sm=n[0]+n[1];
    
    string username = get_input <string>("Please enter a username.");
    cout << "Username: \"" << username << "\"\n";

    while (get_input <int>("Confirm? [0|1]") != 1) {
        username = get_input <string>("Please enter a username.");
        cout << "Username: \"" << username << "\"\n";
    }
    getchar();
    string password = get_input <string> ("Please enter your password.");
    
    cout<<"Check if you are not a robot:\n";
    cout<<n[0]<<" + "<<n[1]<<" = ";
    cin>>smtmp;
    if(smtmp == sm){
        ifstream file;
        file.open("login.csv");
        while(file.good()){
                getline(file,u,',');
                getline(file,p,'\n');
    
            if((u == username) && (p == password)){
                cout<<"\n------------------------------Welcome----"<<u<<"----------------------\n";
                cout<<"Enter you choice:\n[1]Reservation \n[2]Cancellation\n ";
                cin>>choice;
                switch(choice){
                    case 1: 
                            p1.reservation();
                            break;
                    case 2:
                            p1.cancellation();
                            break;  
                }
                f=1;
                break;
            }
        }
        file.close();
        if(!f){
            cout<<"\n Invalid Credentials \n";
            cout<<"Press any key to Try Again...\n";
            goto label;
        
        }   getchar();
    }
    else{
        cout<<"\nAre you a Robot !!!";
        cout<<"\nPress any key to Try Again\n";
        getchar(); getchar();
        goto tag;
    }
}

void passenger::reservation()
{   
    system("CLEAR");
    passenger p;
    char ans;
    do
    { 
        cout<<"\t\t ********************************************\n";
        cout<<"\t\t              BOOKINGS PORTAL \n";
        cout<<"\t\t ********************************************\n";
        p.book_det();
        cout<<"\n\n\t\t\t  Do you Want to book again?(Y/N):";
            cin>>ans;
        }while(ans=='y'||ans=='Y');

}

void passenger::book_det()
{

    cout<<"\n Enter name: ";
        cin>>name;
    cout<<" Enter age: ";
        cin>>age;
    cout<<"\n*Our services connect Bhubaneswar,Puri,Balasore and Cuttack\n";
    while(1)
    {
        cout<<"\nDeparture City:";
            cin>>from;
        if((from.compare("Bhubaneswar")==0) || (from.compare("Puri")==0) || (from.compare("Balasore")==0) || (from.compare("Cuttack")==0))
            break;
        else cout<<"\nPlease choose from the above cities!";
    }
    while(1)
    {
        cout<<"Arrival City:";
            cin>>to;
        if(to.compare(from)==0)
            cout<<"\nThe Departure and arrival destinations are the same!!\n";
        else if((from.compare("Bhubaneswar")==0) || (from.compare("Puri")==0) || (from.compare("Balasore")==0) || (from.compare("Cuttack")==0))
            break;
        else cout<<"\nPlease choose from the above cities";
    }
    while(1)
    { 
        cout<<"\n*DEPARTURE*";
        cout<<"\n  Enter the date:";
            cin>>depart.date;
        cout<<"  Enter the month:";
            cin>>depart.month;
        cout<<"  Enter the year:";
            cin>>depart.year;
        if(depart.date>=1&&depart.date<=31&&depart.month>=1&&depart.month<=12&&depart.year>=2016&&depart.year<=2021)
            break;
        else cout<<"\nPlease enter a valid date of departure!!";
    }

    cout<<"\n\t       Press any key to continue...";
    getchar();
    
    
    ofstream fout ;
    fout.open("Passenger.csv",ios::app);
    fout<<name<<",";
    fout<<age<<",";
    fout<<from<<",";
    fout<<to<<",";
    fout<<depart.date<<"/"<<depart.month<<"/"<<depart.year<<"\n";  

    
    fout.close();       
    system("CLEAR");
    cout<<"\n\t\t\t  Thank You For Booking!!!\n";
    cout<<"\n\t\t\t  Your Details are as follows \n\n";
    display(name);
    cout<<"\n\n\t\t\t   Have a Happy Journey!!";

}

void passenger::display(string name1){
    string n1,n2,n3,n4,n5;
    ifstream read;
    
    read.open("Passenger.csv");
    while(read.good())
    {
        getline(read,n1,',');
        getline(read,n2,',');
        getline(read,n3,',');
        getline(read,n4,',');
        getline(read,n5,'\n');
    
        if(name == n1)
        {   
            cout<<"Name : "<<name1;
            cout<<"\nAge : "<<n2;
            cout<<"\nFrom : "<<n3;
            cout<<"\nTo : "<<n4;
            cout<<"\nDate Of Travel : "<<n5<<"\n";
            break;
        }
    }
    
    cout<<"\n Please press any key to continue..";
    getchar();

}

void passenger::cancellation()
{ 
    system("CLEAR");
    ifstream fio("Passenger.csv",ios::in);
    ofstream fout("temp.csv",ios::out);
    
    int flag=0;
    string name,line;   
    char confirm;
    char found='f';
    if(!fio)
    {
        cout<<"\n\n\t\tBooking not found!!";
        return;
    }
    else
    {
        cout<<"\t\t ********************************************\n";
        cout<<"\t\t              CANCELLATION PORTAL \n";
        cout<<"\t\t ********************************************\n";
        cout<<"\n\n\n\t\t        Enter your Name: ";
        cin>>name;
                display(name);
                found='t';
        cout<<"\n\n\t\t   Are you sure you want to cancel your booking?(Y/N):";
                    cin>>confirm;
        if(confirm=='y' || confirm=='Y'){
            fio.seekg(0);
            while(!fio.eof()){
                    int i=0;
                    getline(fio,line,'\n');
                    string s="";
                    while(line[i] != ','){
                        s+=line[i];
                        i++;
                    }
                    if(s != name){
                        if(flag == 0){
                            fout<<line<<endl;
                            flag=1;
                        }           
                        else
                            fout<<endl<<line;   
                    }
            }
        }   
        fio.close();
        fout.close();
        remove("Passenger.csv");
        rename("temp.csv","Passenger.csv");
        if(found=='f')
            cout<<"\n\n\t\t    Please Check Your Name Entered!!!";
        else
        { 
            system("CLEAR");
            cout<<"\n\t\t\t Thank you for you valuable time.\n\t\tYour booking has been successfully cancelled.";
            ofstream fin("feedback.txt",ios::app);
            cout<<"\n\n\t\t\t Help us to improve ourselves.\n\t\tPlease enter a reason for your cancellation:";
            cout<<"\n\t\t      1) Inadequate Services";
            cout<<"\n\t\t      2) Write a feedback";
            cout<<"\n\t\t      3) Book a different bus";
            cout<<"\n\t\t      4) Miscellaneous";
            cout<<"\n\t\t   Please choose from the above option:";
            char answ,feedback[80];
            int choice;
            cin>>choice;
            switch(choice)
            { 
                case 1: cout<<"\n\n\t\tSorry for the inconvenience caused.We promise to improve ourselves";
                        return;
                case 2: cout<<"\n\n\t\t  Please enter your complaints:";
                        cin.getline(feedback, 100);
                        fin<<feedback;
                        cout<<"\n\t\t        Thank you for your feedback.";
                        cout<<"\n\tWe will get it resolved by our customer care as soon as possible";
                        return;
                case 3: cout<<"\n\n\t\tPress 'Y' to visit booking portal,and any other key to go back to menu:";
                        cin>>answ;
                        if(answ=='Y'||answ=='y')
                        {
                            system("CLEAR");
                            cout<<"\n";
                            reservation();
                        }
                        fin.close();
                        return;
                case 4: cout<<"\n\nThank you for choosing our service!!See you soon";
                        getchar();
                        fin.close();
                        return;
                default:cout<<"\nPlease choose from the above options!!";
            }
        }
    }
}




//Show Total Distance and Intermediate cities 

const int inf=10000,NoN=10;
int matrix[NoN][NoN]={
                        {0,70,32,inf,83,inf,314,inf,inf,inf},
                        {70,0,inf,inf,inf,inf,inf,inf,inf,inf},
                        {32,inf,0,44,52,inf,inf,inf,inf,326},
                        {inf,inf,44,0,inf,59,inf,inf,inf,223},
                        {83,inf,52,inf,0,inf,inf,149,127,inf},
                        {inf,inf,inf,59,inf,0,210,314,inf,inf},
                        {314,inf,inf,inf,inf,210,0,inf,inf,inf},
                        {inf,inf,inf,inf,149,134,inf,0,219,inf},
                        {inf,inf,inf,inf,127,inf,inf,219,0,inf},
                        {inf,inf,326,223,inf,inf,inf,inf,inf,0}
                     };
struct list
{
    int dist,dn,sn;
}output[20]={0};
int index1=0;
struct linkedList
{
    int ns,nd,length;
    struct linkedList *link;
}*r=NULL,*f=NULL;

void Cities()
{
    string city[NoN]={"Bhubaneswar","Puri","Cuttack","Dhenkanal","Jajpur","Angul","Balangir","Kendujhar","Balasore","Rourkela"};
    cout<<"INDEX"<<"        "<<"CITIES"<<endl;
    for(int i=0;i<10;i++)
    {
        cout<<" "<<i<<"       "<<city[i]<<endl;
    }
}

int checkoplist(int node)
{
    for(int k=0;k<index1;k++)
    {
        if(output[k].dn==node)
            return(0);
        else
            return(1);
    }
    return 1;
}

int checkll(int node,int edgelength)
{
    //find if given node is already in linkedlist.
    struct linkedList *p=r,*q=r;
    while(q!=NULL)   //didnt use t->link!=null because in that case last node wont be checked.
    {
        if(q->nd==node)
        {
            //if it exists, check whether new distance is less.
            //for first node
            if(q==r)
            {
                if(r->length>edgelength)
                {
                    //If yes, delete pre-existing node.
                    if(f==r)//suppose only one node exists and has only one adjacent.meh.lonely node.
                        f=q->link;
                    r=q->link;
                    free(q);
                    return(1);
                }
                else
                    return(0);
            }
            //for last node
            else if(q->link==NULL)
            {
                if(q->length>edgelength)
                {
                    while(p->link!=q)
                        p=p->link;
                    f=p;
                    p->link=NULL;
                    //If yes, delete pre-existing node.
                    free(q);
                    return(1);
                }
                else
                    return(0);
            }
            //for intermediate node
            else
            {
                while(p->link!=q)
                    p=p->link;
                if(q->length>edgelength)
                {
                    //If yes, delete pre-existing node.
                    p->link=q->link;
                    free(q);
                    return(1);
                }
                //else dont add node.
                else
                    return(0);
            }
        }
        q=q->link;
    }
    return(1);
}

int shortestPath()
{
    //check shortest node to promote to output list.
    struct linkedList *a=r->link,*temp=r,*b=r;
    int min=r->length;
    //for lonely node.
    if(a==NULL)
    {
        output[index1].sn=b->ns;
        output[index1].dn=b->nd;
        output[index1].dist=b->length;
        index1++;
        r=NULL;f=NULL;
        return(inf);
    }
    else
    {
        while(a!=NULL)
        {
            if(a->length<min)
            {
                b=a;
                min=a->length;
            }
            a=a->link;
        }
    }
    output[index1].sn=b->ns;
    output[index1].dn=b->nd;
    output[index1].dist=b->length;
    index1++;
    //now to delete the node from linkedlist
    if(b==r)
    {
        if(f==r)
            f=b->link;
        r=b->link;
        free(b);
    }
    else if(b->link==NULL)
    {
        while(temp->link!=b)
            temp=temp->link;
        f=temp;
        f->link=NULL;
        free(b);
    }
    else
    {
        while(temp->link!=b)
            temp=temp->link;
        temp->link=b->link;
        free(b);
    }
    //symmetric matrix so changing certain values to zero.
    for(int j=0;j<NoN;j++)
        matrix[j][output[index1-1].dn]=0;
    matrix[output[index1-1].dn][output[index1-1].sn]=0;
    return(output[index1-1].dn);
}

void addAdjacent(int source)//this function accepts a node and adds its adjacents.
{
    int k,l=0;
    //adding adjacents of source to ll
    for(int i=0;i<NoN;i++)
    {
        if(source==inf)
            break;
        struct linkedList *t;
        t=(struct linkedList*)malloc(sizeof(struct linkedList));
        if(matrix[source][i]!=0 && matrix[source][i]!=inf)
        {
            //checking list if adjacent of source is already selected as shortest-path node, if not then continue into if block.
            if(checkoplist(i))
            {
                t->ns=source;
                t->nd=i;
                //distance from source node to current node
                for(k=0;k<index1;k++)
                {
                    if(output[k].dn==source)
                        break;
                }
                //add source and destination to linkedlist along with added distance
                t->length=output[k].dist+matrix[source][i];
                t->link=NULL;
                //check if the added adjacent provides a shorter path. If yes, add, else dont.
                if(checkll(i,t->length))
                {
                    if (f==NULL)
                    {
                        f=t;
                        r=f;
                    }
                    else
                    {
                        f->link=t;
                        f=t;
                    }
                }
                else
                    free(t);
            }
            else
                continue;
        }
    }
    if (source!=inf)
    {
        int nextNode=shortestPath();
        addAdjacent(nextNode);
    }
}

void display_distance(int s,int d)
{

int i=0;
    while(output[i].dn!=d)
        i++;
    cout<<"Distance is "<<output[i].dist<<endl;
    getchar();
    cout <<"\nIntermediate cities"<<endl;
    while(d!=s)
    {
        i=0;
        while(output[i].dn!=d)
            i++;
        string city[NoN]={"Bhubaneswar","Puri","Cuttack","Dhenkanal","Jajpur","Angul","Balangir","Kendujhar","Balasore","Rourkela"};
        cout<<city[output[i].sn]<<endl;
        d=output[i].sn;
    }
    cout<<"Press any key to continue...";
    getchar();
    
}

class Hospitals
{
private:
    string city;
    string hospital;
public:
    void get(string hosp,string c)
    {
        hospital=hosp;
        city=c;
    }
    void display()
    {
        cout<<"city:- "<<city<<"        hospital:- "<<hospital<<endl;
    }
};

class Restaurants
{
private:
    string city;
    string restaurant;
public:
    void get(string res,string c)
    {
        restaurant=res;
        city=c;
    }
    void display()
    {
        cout<<"city:- "<<city<<"        restaurant:- "<<restaurant<<endl;
    }
};



















int main(int argc, char** argv) {
    system("clear");
    user *u;
    Admin a;
    passenger p;
    int source,destination;
    while(1)
    {
        system("CLEAR");
        
        cout<<"\t\t\t -------------------------------------------------------------------------\n";
        cout<<"\t\t\t *************************************************************************\n";
        cout<<"\t\t\t\t\t  ROAD TRANSPORTATION SYSTEM \n";
        cout<<"\t\t\t *************************************************************************\n";
        cout<<"\t\t\t -------------------------------------------------------------------------\n\n";

        cout<<"1. Adminstrative System\n";
        cout<<"2. Passenger System\n";
        cout<<"3. General Information\n";
        cout<<"0. Exit\n";
        int choice,index;
        int c,x;
        
        cout<<"\n Enter you choice: ";
        cin>>choice;

        switch(choice)
        {
            case 1:     u = &a;
                        u -> Login();
                        break;
            case 2:     
                        u = &p;
                        u -> Login();
                        break;
            case 3:     
                        system("CLEAR");
                        cout<<"\n\n------------------------------Information Section---------------------------\n\n";
                        Cities();
                        abc:
                        cout<<"\nInformation on...\n";
                        cout<<"[1] Distance between your Source and Destination ";
                        cout<<"and Intermediate cities\n";
                        cout<<"[2] Names of Hospitals and Restaurants\n";
                        
                        cout<<"Enter your choice : ";
                        cin>>c;
                        if(c == 1){
                            cout<<"Enter index of start point and destination"<<endl;
                            cin>>source;
                            cin>>destination;
                            
                            output[index1].sn=source;
                            output[index1].dn=source;
                            output[index1].dist=0;
                            index1++;
                            addAdjacent(source);
                            display_distance(source,destination);
                        
                            goto abc;
                            break;
                        }
                        else if(c == 2)
                            {
                            cout<<"\nEnter city index"<<endl;
                            cin>>index;
        
                            cout<<"Enter 1 for hospitals and 2 for restaurants"<<endl;
                            cin>>x;
                            if(x==1)
                            {
                                Hospitals objecth[10];
                                string hospName,cityName;
                                ifstream myfile("hospitals.csv");
                                for(int i=0;i<10;i++)
                                {
                                    getline(myfile,cityName,',');
                                    getline(myfile,hospName,'\n');
                                    objecth[i].get(hospName,cityName);
                                }
                                objecth[index].display();
                            }
                            else if(x==2)
                            {
                                Restaurants objectr[10];
                                string resName,cityName;
                                ifstream myfile("restraunts.csv");
                                for(int i=0;i<10;i++)
                                {
                                    getline(myfile,cityName,',');
                                    getline(myfile,resName,'\n');
                                    objectr[i].get(resName,cityName);
                                }
                                objectr[index].display();
                            }
                            else {
                                cout<<"Invalid Choice !!!";
                                cout<<"Press any key to Try Again...\n";
                                getchar(); getchar();
                            }
                            goto abc;
                        }
                        else {
                                
                                cout<<"Invalid Choice !!!";
                                cout<<"Press any key to Try Again...\n";
                                getchar();  getchar();                      
                        }
                        break;
            case 0:
                    while(1)
                    {
                        system("CLEAR");
                        cout<<"\n Are you sure, you want to exit? y | n \n";
                        char ex;
                        cin>>ex;
                        if(ex == 'y' || ex == 'Y')
                            exit(0);
                        else if(ex == 'n' || ex == 'N')
                         {
                             break;
                         }
                        else{

                            cout<<"\n Invalid choice !!!";
                            getchar();
                         } 
                     }  break;

            default: cout<<"\n Invalid choice. Enter again ";
                     getchar();

        }
    }
    return 0;
}
