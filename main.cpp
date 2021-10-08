#include <iostream>
#include<bits/stdc++.h>
#include <ctime>

using namespace std;


int ParseInt(string str)
{
    stringstream sti(str);
    int num = 0;
    sti >> num;
    return num;
}
vector<string> split(string str, char s)
{
     vector <string> tokens;

    stringstream sstm(str);
    string token;

    while(getline(sstm, token, s))
    {
        tokens.push_back(token);
    }
    return tokens;
}
vector<int> getDateVector(string str)
{
    vector<int> ans;
    vector<string> v=split(str,'/');
    for(int i=0;i<v.size();i++){
        ans.push_back(ParseInt(v[i]));
    }
    return ans;
}
class Date
{
    private:
        int day;
        int month;
        int year;
    public:
        Date();
        Date(int d,int m,int y);
        int getDay();
        int getMonth();
        int getYear();
        void showDate();
};
int Date::getDay()
{
	return day;
}
int Date::getMonth()
{
	return month;
}
int Date::getYear()
{
	return year;
}
void Date::showDate(){
    cout<<day<<"/"<<month<<"/"<<year<<endl;
}
Date ::Date()
{
    day=0;
    month=0;
    year=0;
}
Date::Date(int d,int m,int y)
{
    day=d;
    month=m;
    year=y;
}
// Person
class Person
{
private:
    string _name;
    Date _DOB;
public:
    Person();
    Person(string name,Date &d);
    string getName();
    int getAge();
    void showName();
    void showDOB();
    void showAge();
    void showDetails();
};
string Person::getName()
{
    return _name;
}
void Person::showName()
{
    cout<<"Name : "<<_name<<endl;
}
void Person::showDOB()
{
    _DOB.showDate();
}
void Person::showDetails()
{
    showName();
    cout<<"DOB : ";
    _DOB.showDate();
}
Person::Person()
{
	_name ="";
    Date _DOB;
}
Person::Person(string name,Date &d)
{
    _name=name;
    _DOB=d;
}
class pRecord
{
    private:
        string diseaseType;
        Date date;
        int assignedDoctorId;
        float feePaid;
    public:
        pRecord();
        pRecord(string disType,Date d,int doctorId,float fee);
        void showRecord();
};
pRecord::pRecord()
{
	diseaseType="";
	assignedDoctorId=0;
	feePaid=0;

}
pRecord::pRecord(string disType,Date d, int doctorId,float fee)
{
    diseaseType=disType;
    date=d;
    assignedDoctorId=doctorId;
    feePaid=fee;
}
void pRecord::showRecord()
{
    if(diseaseType!="" && assignedDoctorId>0)
    {
        cout<<"Disease Type : "<<diseaseType<<endl;
        cout<<"Date of Visit : ";
        date.showDate();
        cout<<"Assign Doctor Id : "<<assignedDoctorId<<endl;
        cout<<"Paid Fee : "<<feePaid<<endl;
    }
}
class Appointment
{
    private:
        string _diseaseType;
        int _pId;
        int _dId;
        Date _appointmentDate;
        int _tokenNumber;
        float _fee;
        bool _status;
    public:
        Appointment();
        Appointment(int pId,int dId,int tNo,float fee,string distype);
        void showAppointmentDetails();
        int getTokenNumber();
        int getDoctorId();
        bool getStatus();
        bool setStatus(bool status);
};
bool Appointment::getStatus()
{
    return _status;
}
int Appointment::getDoctorId()
{
    return _dId;
}
bool Appointment::setStatus(bool status)
{
    _status=status;
    return true;
}
int Appointment::getTokenNumber()
{
    return _tokenNumber;
}
void Appointment::showAppointmentDetails()
{
    cout<<"Token No : "<<_tokenNumber<<endl;
    cout<<"Patient id : "<<_pId<<endl;
    cout<<"Doctor Id : "<<_dId<<endl;
    cout<<"Fee : "<<_fee<<endl;
    cout<<"Disease Type : "<<_diseaseType<<endl;
    cout<<"Status : "<<_status<<endl;
}
Appointment::Appointment()
{
    _pId=0;
    _dId=0;
}
Appointment::Appointment(int pId,int dId,int tNo,float fee,string distype )
{

    _pId=pId;
    _dId=dId;
    _tokenNumber=tNo;
    _fee=fee;
    _diseaseType=distype;
    _status=false;
    //time_t t=time(0);
    //tm* now=localtime(&t);
    //string currentDate=to_string(now->tm_mday)+"/"+to_string(now->tm_mon+1)+"/"+to_string(now->tm_year+1900);
    //_appointmentDate=currentDate;
}
class Patient : public Person
{
    private:
        int _id;
        vector<pRecord> _recordHistory; //Maintain and Update history of patient on each visit.
    public:
        Patient();
        Patient(int Id,string name,Date &d);
        void showPatientDetails();
};
void Patient::showPatientDetails()
{
    cout<<"Patient Id : "<<_id<<endl;
    showDetails();
}
Patient ::Patient():Person()
{
    _id=0;
}
Patient::Patient(int Id,string name,Date &d):Person(name,d)
{
	_id=Id;
}

class Doctor : public Person
{
    private:
        int _id;
        string _specialization; //General Physician, Child Specialist etc.
        vector<int> _patientIds;
    public:
        Doctor(int Id,string name,string spec,Date &d);
        void showDoctorDetails();
        bool assignPatient(int pId);
        void showAssignPatient();
        bool processAppointment(Appointment *appointment);
};
bool Doctor::processAppointment(Appointment *appointment)
{
    (*appointment).setStatus(true);
    return true;

}
void Doctor::showAssignPatient()
{
    for(int i=0;i<_patientIds.size();i++)
    {
        cout<<_patientIds[i]<<" ";
    }
    cout<<endl;
}
bool Doctor::assignPatient(int pId)
{
    _patientIds.push_back(pId);
}
void Doctor::showDoctorDetails()
{
    cout<<"Doctor Id : "<<_id<<endl;
    showDetails();
    cout<<"Specialization : "<<_specialization<<endl;
}
Doctor::Doctor(int id,string name,string spec,Date &d):Person(name,d)
{
    _id=id;
    _specialization=spec;
}

class hospital
{
    private:
        map<int,Doctor*> _doctors;
        map<int,Patient*> _patients;
        string _hospitalName;
        vector<Appointment*> _appointment;
    public:
        hospital();
        ~hospital();
        string getHospitalName();
        bool addPatient();
        void showPatientById(int id);
        void showAllPatients();
        bool addDoctor();
        void showDoctorById(int id);
        void showAllDoctors();
        bool addAppointment();
        void showAppointmentByTokenNo(int tNo);
        void showAllAppointment();
        void processAppointmentByDoctor(int dId);
};
void hospital::processAppointmentByDoctor(int dId)
{
    if(_doctors.find(dId)==_doctors.end()){
        cout<<"Invalid Doctor Id"<<endl;
        return;
    }
    bool isAppointmentAvailable=false;
    for(int i=0;i<_appointment.size();i++)
    {
        if((*_appointment[i]).getDoctorId()==dId && !(*_appointment[i]).getStatus())
        {
            isAppointmentAvailable=true;
            (*_appointment[i]).showAppointmentDetails();
            cout<<"Enter 1 to process this Appointment : "<<endl;
            int responce=0;
            cin>>responce;
            if(responce==1)
            {
                (*_doctors[dId]).processAppointment(_appointment[i]);
                cout<<"Patient checked by Doctor"<<endl;
            }
            else
            {
                cout<<"Doctor skipped this Appointment"<<endl;
            }
        }
    }
    if(!isAppointmentAvailable)
    {
        cout<<"You don't have any Appointment Today"<<endl;
    }

}
void hospital::showAllAppointment()
{
    for(int i=0;i<_appointment.size();i++)
    {
        (*_appointment[i]).showAppointmentDetails();
        cout<<endl;
    }
}

void hospital::showAppointmentByTokenNo(int tNo)
{
    for(int i=0;i<_appointment.size();i++){
        if((*_appointment[i]).getTokenNumber()==tNo){
            (*_appointment[i]).showAppointmentDetails();
            return;
        }
    }
    cout<<"Invalid Token Number"<<endl;
}
bool hospital::addAppointment()
{
    bool result=false;
    try
    {
        string disType;
        int pId,dId;
        float fee;
        cout<<"Enter Patient Id : ";
        cin>>pId;
        cout<<"Enter Doctor Id : ";
        cin>>dId;
        cout<<"Enter Fee : ";
        cin>>fee;
        cin.ignore();
        cout<<"Enter Disease Type : ";
        getline(cin,disType);
        int tokenNumber=_appointment.size()+1;
        if(_patients.find(pId)==_patients.end())
        {
            cout<<"Invalid Patient Id"<<endl;
        }
        else if(_doctors.find(dId)==_doctors.end())
        {
            cout<<"Invalid Doctor Id"<<endl;
        }
        else
        {
          _appointment.push_back(new Appointment(pId,dId,tokenNumber,fee,disType));
          cout<<"Appointment added Successfully and token Number is : "<<tokenNumber<<endl;
          (*_doctors[dId]).assignPatient(pId);
          result=true;
        }
    }
    catch(exception ex)
    {
        cout<<"Invalid Input try again .."<<endl;
    }
    return result;
}
string hospital::getHospitalName()
{
    return _hospitalName;
}
bool hospital::addPatient()
{
    try
    {
        string name,dob;
        cout<<"Enter Patient Name : ";
        cin.ignore();
        getline(cin,name);
        cout<<"Enter Patient Date of Birth(dd/mm/yyyy) : ";
        getline(cin,dob);
        int id=_patients.size()+1;
        vector<int> d=getDateVector(dob);
        Date date(d[0],d[1],d[2]);
        _patients[id]=new Patient(id,name,date);
        cout<<"Patient : "<<name<<" Added successfully and Patient id is "<<id<<endl;
        return true;
    }
    catch(exception ex){
        cout<<"Invalid Input try again .."<<endl;
        return false;
    }
}
void hospital::showAllPatients()
{
    for( map<int,Patient*>::iterator ii=_patients.begin(); ii!=_patients.end(); ++ii)
    {
        cout<<endl;
       (*(*ii).second).showPatientDetails();
    }
    cout<<endl;
}
void hospital::showPatientById(int id)
{
    if(_patients.find(id)!=_patients.end())
    {
        (*_patients[id]).showPatientDetails();
    }
    else
    {
        cout<<"Wrong Patient id = "<<id<<" Please enter a valid Patient Id"<<endl;
    }
}
bool hospital::addDoctor()
{
    try
    {
        string name,spec,dob;
        cout<<"Enter Doctor Name : ";
        cin.ignore();
        getline(cin,name);
        cout<<"Enter Doctor Date of Birth(dd/mm/yyyy) : ";
        getline(cin,dob);
        cout<<"Enter Doctor specialization : ";
        getline(cin,spec);
        int id=_doctors.size()+1;
        vector<int> d=getDateVector(dob);
        Date date(d[0],d[1],d[2]);
        _doctors[id]=new Doctor(id,name,spec,date);
        cout<<"Doctor : "<<name<<" Added successfully and Doctor id is "<<id<<endl;
        return true;
    }
    catch(exception ex){
        cout<<"Invalid Input try again .."<<endl;
        return false;
    }
}
void hospital::showDoctorById(int id)
{
    if(_doctors.find(id)!=_doctors.end())
    {
        (*_doctors[id]).showDoctorDetails();
    }
    else
    {
        cout<<"Wrong Doctor id = "<<id<<" Please enter a valid doctor Id"<<endl;
    }
}
void hospital::showAllDoctors()
{
    for( map<int,Doctor*>::iterator ii=_doctors.begin(); ii!=_doctors.end(); ++ii)
    {
        cout<<endl;
       (*(*ii).second).showDoctorDetails();
    }
    cout<<endl;
}
hospital::hospital()
{
    _hospitalName="AMAR SINGH HOSPITAL";
    // init. Patient Details
    ifstream fin;
	fin.open("Patient.txt");
	if(!fin)
	{
		cout<<"Parient.txt file does not exist"<<endl;
	}
	else
	{
		while(!fin.eof())
		{
		  	string s;
			getline(fin,s);
			vector<string> row=split(s,',');
			int id=ParseInt(row[0]);
            vector<int> d=getDateVector(row[2]);
            Date date(d[0],d[1],d[2]);
            _patients[id]=new Patient(id,row[1],date);
		}
		fin.close();
	}
	 // init. Doctor Details
	fin.open("Doctor.txt");
	if(!fin)
	{
		cout<<"Doctor.txt file does not exist"<<endl;
	}
	else
	{
		while(!fin.eof())
		{
		  	string s;
			getline(fin,s);
			vector<string> row=split(s,',');
			int id=ParseInt(row[0]);
            vector<int> d=getDateVector(row[2]);
            Date date(d[0],d[1],d[2]);
            _doctors[id]=new Doctor(id,row[1],row[3],date);
		}
		fin.close();
	}
}
hospital::~hospital()
{
    for( map<int,Doctor*>::iterator ii=_doctors.begin(); ii!=_doctors.end(); ++ii)
    {
       delete (*ii).second;
    }
    for( map<int,Patient*>::iterator ii=_patients.begin(); ii!=_patients.end(); ++ii)
    {
       delete (*ii).second;
    }
    for(int i=0;i<_appointment.size();i++)
    {
        delete _appointment[i];
    }
}
void showMenu()
{
    cout<<"Enter Negative Value for Exit"<<endl;
    cout<<"Enter 0 to show Menu"<<endl;
    cout<<"Enter 1 to add a new Patient"<<endl;
    cout<<"Enter 2 to add a new Doctor"<<endl;
    cout<<"Enter 3 to Book an appointment"<<endl;
    cout<<"Enter 4 show patient Details by id"<<endl;
    cout<<"Enter 5 show Doctor Details by id"<<endl;
    cout<<"Enter 6 show all Patient"<<endl;
    cout<<"Enter 7 show all Doctors"<<endl;
    cout<<"Enter 8 show Appointment Details by token Number"<<endl;
    cout<<"Enter 9 show all appointment"<<endl;
    cout<<"Enter 10 Doctor Login Panel(Only for Doctor)"<<endl;
}
int main(){

    hospital hospital;
    int choice,id;
    cout<<"\n\n\t\t\tWELCOME IN "<<hospital.getHospitalName()<<endl<<endl;
    showMenu();
    while(true)
    {
        cout<<"Enter Your Choice ";
        cin>>choice;
        if(choice<0){
            break;
        }
        switch(choice)
        {
            case 0:
                showMenu();
                break;
            case 1:
                hospital.addPatient();
                break;
            case 2:
                hospital.addDoctor();
                break;
            case 3:
                hospital.addAppointment();
                break;
            case 4:
                cout<<"Enter Patient Id : ";
                cin>>id;
                hospital.showPatientById(id);
                break;
            case 5:
                cout<<"Enter Doctor Id : ";
                cin>>id;
                hospital.showDoctorById(id);
                break;
            case 6:
                hospital.showAllPatients();
                break;
            case 7:
                hospital.showAllDoctors();
                break;
            case 8:
                cout<<"Enter Token Number : ";
                cin>>id;
                hospital.showAppointmentByTokenNo(id);
                break;
            case 9:
                hospital.showAllAppointment();
                break;
            case 10:
                cout<<"Enter Doctor Id :";
                cin>>id;
                hospital.processAppointmentByDoctor(id);
                break;
            default:
                cout<<"Invalid Choice Please Enter Valid Choice"<<endl;
        }
    }
    return 0;
}
