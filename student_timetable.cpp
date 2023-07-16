#include<iostream>
#include<vector>
#include<unordered_map>
#include<cstring>

#define NameLimit 100
#define NumberOfSubjects 2

class ClassTimetable{
    std::vector<std::vector<std::pair<std::string,int>>> Timetable;
    /*this is a vector that contains vectors which contains all the subjects in a day ,
    and the reason why we are using a pairs here is because we wanna map the subject to the course
    , 
    in python you can make a list that contains a list of dictionaries
    */
    public:
        void TimetableInsert(){
            std::vector<std::pair<std::string,int>> TimetableForDay;
        for(int i=0;i<NumberOfSubjects;i++){
            std::pair<std::string,int> subjectsCredit;    
            char subjectname[NameLimit];
            int n=0,credits_;
            std::cout<<"enter the name of the subject:";
            std::cin>>subjectname; // write a function(standard lib) so that it can even take spaces
            std::cout<<"enter the credits for "<<subjectname<<":";
            std::cin>>credits_;
            subjectsCredit.first=subjectname;
            subjectsCredit.second=credits_;
            // memset(subjectname,'0',sizeof(subjectname));
            TimetableForDay.push_back(subjectsCredit);
        }
            Timetable.push_back(TimetableForDay);
        }
        void DisplayTimetable(){
            if(Timetable.size()>0){
            for(auto it:Timetable){
                for(auto iter:it){
                    std::cout<<iter.first<<"-"<<iter.second<<std::endl;
                }
                std::cout<<std::endl;
                std::cout<<std::endl;
            }
            }
        }
};

int main(){
    ClassTimetable B_section;
    B_section.TimetableInsert();
    B_section.DisplayTimetable();
    return 0;
}