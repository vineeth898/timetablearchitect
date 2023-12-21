#include<iostream>
#include<string>
#include<fstream>
using namespace std;
//common
#include"generalinfo.cpp"
//make a fstream object
fstream teacherdata;
//a counter to count number of teachers
int noofteachers=0;
// teacher object
class teacher{
    public:
        string name;//name of teacher
        string designation;//desegnation of teacher
        string department;//department of teacher
        string specialisation;//specialisation of teacher. maybe removed
        int hourstoteach=0;//hours teacher willt each. keep -1 to default based on desegnation
        int schedule[number_of_days][number_of_days][2];//a matrix of order defined in generalinfo.cpp .Elements of the matrix is a list [0 or 1, class if 0] 1 indicates tteaaher is free. if 0 then which class by teacher is necessary. class is a number assigned by the program.
        teacher(){
            
        }//need a non-parameteric constructor because of parameterised constrructor
        teacher(string name,string designation,string department,string specialisation,int hourstoteach,int schedule[number_of_days][number_of_days][2]);//parameterised constructor just in case
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
//parseTeacher function returns a pointer to a array of teacher objects that contain their info as entered in the teacherdata.csv file
teacher* parseTeachers(string fileDestination){
    teacherdata.open(fileDestination);//opening the file
    string prev,curr;//conparing strings to find last entry
    teacher *teacherList= new teacher[1];//Initialising a teacherlist with 1 teacher
    while(true){
        teacherdata>>curr;//read entry
        if(curr==prev){
            break;
         }//the last entry will be read repeatedly oince endo of file is reached. Should upgrade to EOF function and remove this in future
        if(noofteachers>0){//since 1 teacher object is already there in the space teacherList wen skip it once
            teacher *temp=new teacher[noofteachers+1];//Make new pointer
            for(int k=0;k<noofteachers;k++){//asssign old pointer values to new pointer
                temp[k].name=teacherList[k].name;
                temp[k].designation=teacherList[k].designation;
                temp[k].department=teacherList[k].department;
                temp[k].specialisation=teacherList[k].specialisation;
                temp[k].hourstoteach=teacherList[k].hourstoteach;
                for(int i=0;i<generalinfo::numberOfDays;i++){
                    for(int j=0;j<generalinfo::numberOfPeriods;j++){
                        temp[k].schedule[i][j][0]=teacherList[k].schedule[i][j][0];
                        temp[k].schedule[i][j][1]=teacherList[k].schedule[i][j][1];
                    }
                }
            }
            delete []teacherList;//delete old pointer
            teacherList=temp;//assign new pointer adress to old pointer
        }
        prev=curr;//reset prev
        int commacount=0;//a counter to accunt for the commas encountered
        enum states{name,desegnation,branch,specialisation,hourstoteach,schedule};//the datafields that are BEFORE after each comma 
        for(int i=0;i<curr.size();i++){
            if(curr[i]==','){
                commacount++;
                continue;
            }//count commas and skip the comparison when commas are encountered
            switch (commacount)
            {//if not comma, then execute seperate functions based 0on which datafield it is reading
            case name:
                    teacherList[noofteachers].name.push_back(curr[i]);
                break;
            //push letters to name field
            case desegnation:
                    teacherList[noofteachers].designation.push_back(curr[i]);
                break;
            //push letters to desegnation
            case branch:
                    teacherList[noofteachers].department.push_back(curr[i]);
                break;
            //push letters to Branch
            case specialisation:
                    teacherList[noofteachers].specialisation.push_back(curr[i]);
                break;
            //push letters to Specialisation
            case hourstoteach:
                    teacherList[noofteachers].hourstoteach=teacherList[noofteachers].hourstoteach*10+int(curr[i]-'0');
                break;
            //hours to teach 
            case schedule:  
                {
                    int iterator=i;//an iterator to traverese throught the rest of the list.
                    int level=-1;//how deep we are in the matrix
                    int count[3];//stores adress of our current element
                    count[0]=0;count[1]=0;count[2]=0;//initialise all to the first leement
                    do{//convert schedulee tecxt to a matrix
                        if(curr[iterator]=='['){
                            level++;//go one level deeper
                        }
                        else if(curr[iterator]==']'){
                            count[level]=0;
                            level--;//go one level shallower
                        }
                        else if(curr[iterator]==','){
                            count[level]++;//increase our element count
                        }
                        else{
                            teacherList[noofteachers].schedule[count[0]][count[1]][count[2]]=teacherList[noofteachers].schedule[count[0]][count[1]][count[2]]*10+curr[iterator]-'0';
                        }//puts appropriate number in appropriate position
                        iterator++;//go to next letter
                    }while(level>=0);//get out of loop when level becomes -1 again
                    i=iterator;//jump i to iterator.
                }
                break;//done.
                default:
                    cout<<"smothin aint right on teacher "<<noofteachers+1;//error if extra entry is there
                break;
            }
        }
        // cout<<" teacher name: "<<teacherList[noofteachers].name;
        // cout<<"\n teacher desegantion: "<<teacherList[noofteachers].designation;
        // cout<<"\n teacher department: "<<teacherList[noofteachers].department;
        // cout<<"\n teacher specialisation: "<<teacherList[noofteachers].specialisation;
        // cout<<"\n teacher noofhours: "<<teacherList[noofteachers].hourstoteach<<endl<<endl;
        noofteachers++;//go to next teacher.
    }
    teacherdata.close();//close file
    return teacherList;//return pointer to list ofteacher objects
}
int main(){
    teacher *teacherList=new teacher[noofteachers];
    teacherList=parseTeachers("teacherdata.csv");
    cout<<teacherList[3].schedule[0][0][0];
}   
