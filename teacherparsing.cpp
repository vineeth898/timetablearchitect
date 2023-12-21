#include<iostream>
#include<string>
#include<fstream>
#include"generalinfo.cpp"
using namespace std;
fstream teacherdata;
int noofteachers=0;
class teacher{
    public:
        string name;
        string designation;
        string department;
        string specialisation;
        int hourstoteach=0;
        int schedule[6][6][2];
        teacher(){
            for(int i=0;i<generalinfo::numberOfDays;i++){
                for(int j=0;j<generalinfo::numberOfPeriods;j++){
                    this->schedule[i][j][0]=0;
                    this->schedule[i][j][1]=0;
                }
            }
        }
        teacher(string name,string designation,string department,string specialisation,int hourstoteach,int schedule[number_of_days][number_of_days][2]);
};

teacher::teacher(string name,string designation,string department,string specialisation,int hourstoteach,int schedule[number_of_days][number_of_periods][2]){
    this->name=name;
    this->designation=designation;
    this->department=department;
    this->specialisation=specialisation;
    this->hourstoteach=hourstoteach;
    for(int i=0;i<generalinfo::numberOfDays;i++){
        for(int j=0;j<generalinfo::numberOfPeriods;j++){
            this->schedule[i][j][0]=schedule[i][j][0];
            this->schedule[i][j][1]=schedule[i][j][1];
        }
    }
}
void parseTeachers(string fileDestination){
    teacherdata.open(fileDestination);
    string prev,curr;
    teacher teacherlist[2];
    teacher *teacherList= new teacher[1];
    while(true){
        teacherdata>>curr;
        if(curr==prev){
            break;
         }
        if(noofteachers>0){
            teacher *temp=new teacher[noofteachers+1];
        }
        prev=curr;
        int commacount=0;
        enum states{name,desegnation,branch,specialisation,hourstoteach,schedule};
        for(int i=0;i<curr.size();i++){
            if(curr[i]==','){
                commacount++;
                continue;
            }
            switch (commacount)
            {
            case name:
                    teacherlist[noofteachers].name.push_back(curr[i]);
                break;
            
            case desegnation:
                    teacherlist[noofteachers].designation.push_back(curr[i]);
                break;
            
            case branch:
                    teacherlist[noofteachers].department.push_back(curr[i]);
                break;
            
            case specialisation:
                    teacherlist[noofteachers].specialisation.push_back(curr[i]);
                break;
            
            case hourstoteach:
                    teacherlist[noofteachers].hourstoteach=teacherlist[noofteachers].hourstoteach*10+int(curr[i]-'0');
                break;
            case schedule:  
                {
                    int iterator=i;
                    int level=-1;
                    int count[3];
                    count[0]=0;count[1]=0;count[2]=0;
                    do{
                        if(curr[iterator]=='['){
                            level++;
                        }
                        else if(curr[iterator]==']'){
                            count[level]=0;
                            level--;
                        }
                        else if(curr[iterator]==','){
                            count[level]++;
                        }
                        else{
                            teacherlist[noofteachers].schedule[count[0]][count[1]][count[2]]=teacherlist[noofteachers].schedule[count[0]][count[1]][count[2]]*10+curr[iterator]-'0';
                        }
                        iterator++;
                    }while(level>=0);
                    goto s;
                }
                break;
            default:
                break;
            }
        }
        s:
        cout<<" teacher name: "<<teacherlist[noofteachers].name;
        cout<<"\n teacher desegantion: "<<teacherlist[noofteachers].designation;
        cout<<"\n teacher department: "<<teacherlist[noofteachers].department;
        cout<<"\n teacher specialisation: "<<teacherlist[noofteachers].specialisation;
        cout<<"\n teacher noofhours: "<<teacherlist[noofteachers].hourstoteach<<endl<<endl;
        noofteachers++;
    }
    teacherdata.close();
    cout<<noofteachers;
}
int main(){
    parseTeachers("teacherdata.csv");
}   
