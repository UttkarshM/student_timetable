//preprocessor definations
#include<cctype>
#include<iostream>
#include<vector>
#include<unordered_map>
#include<cstring>
#include<fstream>
#include<stdlib.h>
#include<string>

//marcos
#define NameLimit 100
#define NumberOfSubjects 2
#define Periods_perday 5
#define WorkingDaysperWeek 5

class ClassTimetable{
    std::vector<std::vector<std::pair<std::string,int>>> Timetable;
    std::unordered_map<std::string,int> Subject_to_credits={{"english",10}};
    /*this is a vector that contains vectors which contains all the subjects in a day ,
    and the reason why we are using a pairs here is because we wanna map the subject to the course
    , 
    in python you can make a list that contains a list of dictionaries
    */
    public:
        int DaysOccupied(){//returns how many days have already been filled
            return Timetable.size();
        }
        int return_int(std::string str){ //type conversion from character or string to int
            //some problem with stoi so i made this change this later
            int val=0; 
            for(char ch:str){
                if(isdigit(ch)){
                    val=val*10+(ch-'0'); // ascii value of numbers start from 0-48 we are subtracting it to get the actual numbers.
                   // std::cout<<val<<"val+"<<ch<<std::endl;
                }
            }
            return val;
        }
        void is_newline(std::string stre){ // used to check if there is a new line character in your string. //debugging purposes.
            for(char ch:stre){
            if(ch=='\n'){
                std::cout<<"you have an newline character in the string"<<std::endl;
            }
            }
        }
        void parser(std::string stre){ //contains information about the credit weightage of each subject
            std::string temp="";
            std::pair<std::string,std::string> pir;
            for(auto it:stre){
            if(it==' '){
                pir.first=temp;temp="";
            }
            else{
                temp+=it;
                }
            }
            pir.second=(temp); // all the words except the last one get reset
            Subject_to_credits[pir.first]=return_int(pir.second);
        }
        void load_info(){// loads information from the file
            std::fstream file;
            file.open("availableLanguages.txt",std::ios::in);
            std::string buffer;
            while(getline(file,buffer)){
                parser(buffer);
            }
            //after this all the subjects have been loaded into the map;
            file.close();
        }
        void displaythetopics(){
            std::unordered_map<std::string,int>::iterator it;
            std::cout<<"subjects that are available:"<<std::endl;
            for(it=Subject_to_credits.begin();it!=Subject_to_credits.end();++it){
                std::cout<<it->first<<"-"<<it->second<<" credits"<<std::endl;
            }
        }
        void TimetableInsert(){
            std::vector<std::pair<std::string,int>> TimetableForDay;
            while(TimetableForDay.size()<Periods_perday){ // we are constraining the number of subjects
            std::pair<std::string,int> subjectsCredit;    
            char subjectname[NameLimit];
            std::cout<<"enter the name of the subject or enter \"exit\" to exit the current day's timetable:\n";
            displaythetopics();
            std::cin>>subjectname; // write a function(standard lib) so that it can even take spaces
            if(strcmp("exit",subjectname)==0){
                std::cout<<"exited the current timetable\n";
                break;
            }
            subjectsCredit.first=subjectname;
            subjectsCredit.second=Subject_to_credits[subjectname];
            TimetableForDay.push_back(subjectsCredit);
        }
        Timetable.push_back(TimetableForDay);
        }
        void DisplayTimetable(){
            if(!Timetable.empty()){
            for(auto it:Timetable){
                int sum=0;
                for(auto iter:it){
                    sum+=iter.second;
                    std::cout<<iter.first<<"-("<<iter.second<<") || ";
                }
                std::cout<<"("<<sum<<")"<<std::endl;

                std::cout<<std::endl;
                std::cout<<std::endl;
            }
            }
            else{
                std::cout<<"table is empty"<<std::endl;
            }
        }
        void automaticInsert(){

        }
};
int main(){
    int choice;
    ClassTimetable B_section;
    B_section.load_info(); // make it a construct later so that it happens automatically.
    // for(int i=0;i<WorkingDaysperWeek;i++){
    //     std::cout<<"DAY "<<i+1<<":\n";
    //     B_section.TimetableInsert();
    // }
    // B_section.DisplayTimetable();
    while(1){
    std::cout<<"Choose one option out of these:\n1.)Insert another day\t2.)Display the current weekly timetable)\n3.)exit program\n";
    std::cin>>choice;
    switch(choice){
        case 1:
        if(B_section.DaysOccupied()<=WorkingDaysperWeek){
            B_section.TimetableInsert();
        }
        else{
            std::cout<<"the week has already been occupied completely"<<std::endl;
        }
        break;
        case 2:
            B_section.DisplayTimetable();
            break;
        case 3:
            std::cout<<"program has ended.";
            return 0; // exits the program directly
        default:
            std::cout<<"Invalid choice";
           break;
    }
    }
    return 0;
}