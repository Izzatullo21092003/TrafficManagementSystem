#include <iostream>
#include <string>
using namespace std;

//Program 1.
class Education{
protected:
    string h_p_q;
    void setH_P_Q(){
        cout<<"Input highest professional qualification: "; cin>>h_p_q;
    }
    string getH_P_Q(){
        return h_p_q;
    }
};

class Staff{
public:
    string code, name;
    void setCode(){
        cout<<"Input code: "; cin>>code;
    }
    string getCode(){
        return code;
    }
    void setName(){
        cout<<"Input name: "; cin>>name;
    }
    string getName(){
        return name;
    }
};

class Teacher:public Staff, public Education{
public:
    string subject, publication;
    void setInfo(){
        setName();
        setCode();
        cout<<"Input subject: "; cin>>subject;
        cout<<"Input publicatrion: "; cin>>publication;
        setH_P_Q();
    }
    void Display(){
        cout<<"name       : "<<getName()<<endl;
        cout<<"code       : "<<getCode()<<endl;
        cout<<"subject    : "<<subject<<"\n";
        cout<<"publication: "<<publication<<"\n";
        cout<<getH_P_Q()<<endl;
    }
};

class Typist:public Staff{
public:
    int speed;
    void Inherited(){
        setName();
        setCode();
    }
    void setInfo(){
        cout<<"Input speed: "; cin>>speed;
    }
    void D_inherited(){
        cout<<"name  : "<<getName()<<endl;
        cout<<"code  : "<<getCode()<<endl;
    }
    void Display(){
        cout<<"speed  : "<<speed<<"\n";
    }
};

class Officer:public Staff, public Education{
public:
    float grade;
    void setInfo(){
        setName();
        setCode();
        cout<<"Input subject: "; cin>>grade;
        setH_P_Q();
    }
    void Display(){
        cout<<"name  : "<<getName()<<endl;
        cout<<"code  : "<<getCode()<<endl;
        cout<<"grade : "<<grade<<"\n";
        cout<<getH_P_Q()<<endl;
    }
};

class Regular:public Typist{
public:
    float m_salary;
    void setInfo(){
        setInfo();
        cout<<"Input salary: "; cin>>m_salary;
    }
    void Display(){
        Display();
        cout<<"salary : "<<m_salary<<endl;
    }
};

class Casual:public Typist{
public:
    float d_wages;
    void setInfo(){
        setInfo();
        cout<<"Input salary: "; cin>>d_wages;
    }
    void Display(){
        Display();
        cout<<"salary : "<<d_wages<<endl;
    }
};

//Program 2.
class Person{
public:
    string name, code;
    void setData(){
        cout<<"Input name: "; cin>>name;
        cout<<"Input code: "; cin>>code;
    }
    void getData(){
        cout<<"name: "<<name<<endl;
        cout<<"code: "<<code<<endl;
    }
};

class Account:public Person{
public:
    int pay;
    void setPay(){
        setData();
        cout<<"Input payment: "; cin>>pay;
    }
    void getPay(){
        getData();
        cout<<"payment: "<<pay<<endl;
    }
};

class Admin:public Person{
public:
    float experience;
    void setExperience(){
        cout<<"Input experience: "; cin>>experience;
    }
    void getExperience(){
        cout<<"experience: "<<experience<<endl;
    }
};

class Master:public Account, public Admin{
public:
    void Set(){
        setPay();
        setExperience();
    }
    void Get(){
        getPay();
        getExperience();
    }
};

int main()
{
    Teacher te;
    te.setInfo();    te.Display();
    Typist ty;
    ty.Inherited();    ty.setInfo();    ty.D_inherited();    ty.Display();
    Officer of;
    of.setInfo();    of.Display();
    Regular re;
    re.setInfo();    re.Display();
    Casual ca;
    ca.setInfo();    ca.Display();
    Master ma;
    ma.Set();    ma.Get();

    return 0;
}