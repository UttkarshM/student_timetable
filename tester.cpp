///preprocessor definations
#include<iostream>
#include<vector>
#include<unordered_map>
#include<fstream>
#include<stdlib.h>
#include<string>
#include<unistd.h>
#include<unordered_set>
#include<algorithm>
#include<random>
#include<pybind11/stl.h>
#include<pybind11/pybind11.h>

//marcos//change the value of the constants later.

#define WorkingDaysperWeek 5
#define MinCreditsPerday 45
#define MaxCreditsPerday 180

using namespace std;
namespace py=pybind11;

class ClassTimetable{ 
    public:
    std::vector<std::string>Subjects;
    std::vector<std::vector<std::vector<std::string>>> College_timetable;
    std::vector<std::vector<std::pair<std::string,int>>> Timetable;
    
    std::unordered_map<std::string,int> Subject_to_credits;
    std::unordered_map<std::string,int> TotalNumberofTeachers;
    char section;
    
    std::vector<std::vector<std::string>> AutoTimetable; // for automatic timetable generation.

    /*this is a vector that contains vectors which contains all the subjects in a day ,
    and the reason why we are using a pairs here is because we wanna map the subject to the course
    , 
    in python you can make a list that contains a list of dictionaries
    */
   
    ClassTimetable(){}
    bool compare_tt(){

        return false;
    }
    bool is_in(std::vector<std::vector<std::string>>large,std::vector<std::string> smallvec){
        for(std::vector<std::string> it:large){
            if(smallvec==it){
                return true;
            }
        }
        return false;
    }
        int random_number(int max,int min=0){
            usleep(900000);
            srand(time(NULL));
            int random=rand()%(max-min+1)+min;
            return random;
        }
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
        std::unordered_map<std::string,int> parser(std::string stre){ //contains information about the credit weightage of each subject
            std::unordered_map<std::string,int> temp_map;
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
            temp_map[pir.first]=return_int(pir.second);
            return temp_map;
        }
        void load_info(){// loads information from the file
            std::fstream file;
            file.open("availableLanguages.txt",std::ios::in);
            std::string buffer;
            while(getline(file,buffer)){
                for(auto it:parser(buffer)){
                    Subject_to_credits[it.first]=it.second;
                }
            }
            std::fstream file1;
            file1.open("availableteacher.txt",std::ios::in);
            std::string buffer1;
            while(getline(file1,buffer1)){
                // cout<<buffer1<<endl;
                for(auto it:parser(buffer1)){
                    // cout<<it.first<<"-"<<it.second<<endl;
                    TotalNumberofTeachers[it.first]=it.second;
                }
            }
            file1.close();
            //after this all the subjects have been loaded into the map;
            file.close();
        }

        void subjectEntry(){

            string buffer;
            std::fstream file1;
            file1.open("file_transfers/subject_transfer.txt");
            buffer="";
            while(getline(file1,buffer)){
                if(buffer[0]=='#'){
                    section=buffer[1];
                }
                else{
                Subjects.push_back(buffer);
            }
            }
        }
        int i=0;
        vector<vector<string>> automaticInsert_perday(){
            // Subjects={"python","c++","maths","bash"};
            int day=0;
            while(day<6){
            int creditsperday=0;
            std::vector<std::string> currentDay;
            std::unordered_set<int> sets;
            int randnum=random_number(Subjects.size(),1);
            int randum=Subjects.size();
            std::random_device rd;
            std::shuffle(Subjects.begin(), Subjects.end(), rd);
            std::vector<std::string>::iterator iter;
            int i=0;
            while(i<randnum && currentDay.size()<randnum){
                if(TotalNumberofTeachers[Subjects[i]]!=0){
                    currentDay.push_back(Subjects[i]);
                    creditsperday+=Subject_to_credits[Subjects[i]];
                }
                i++;
            }
            if(creditsperday>20 && creditsperday<280){
                day++;
                AutoTimetable.push_back(currentDay);
                currentDay.clear();
            }
        }
            return AutoTimetable;
        }
            void printauto(){
                for(auto it:AutoTimetable){
                    int sum=0;
                    for(auto iter:it){
                        sum+=Subject_to_credits[iter];
                        std::cout<<iter<<"  ||  ";
                    }
                    std::cout<<sum<<std::endl;
                }
            }
            void insert_into_file(){
                std::fstream file;
                std::string name="Timetables/"+to_string(section)+"_section.txt";
                file.open(name,std::ios::out);
                for(auto it:AutoTimetable){
                    int sum=0;
                    for(auto iter:it){
                        sum+=Subject_to_credits[iter];
                        file<<iter<<" || ";
                    }
                    file<<sum<<"\n"<<std::endl;
                }
            }
};
// int main(){
//     int choice;
//     ClassTimetable B_section;
//     B_section.load_info();
//     //cout<<B_section.TotalNumberofTeachers["c"]<<B_section.Subject_to_credits["c++"];
//     //make it a construct later so that it happens automatically.
//     B_section.subjectEntry();
//     B_section.automaticInsert_perday();
//     B_section.printauto();
//     B_section.insert_into_file();
//     return 0;
// }

PYBIND11_MODULE(tester,handle){
    handle.doc()="this is a module for creating a student timetable program";
    py::class_<ClassTimetable>( // defining the class
        handle,"cpp_class"
    )
    .def(py::init<>()) // for constructor
    .def("loader",&ClassTimetable::load_info)
    .def("parser",&ClassTimetable::parser)
    .def("subject_entry",&ClassTimetable::subjectEntry)
    .def("int_return",&ClassTimetable::return_int)
    .def("rand",&ClassTimetable::random_number)
    .def("in_side",&ClassTimetable::is_in) 
    .def("auto_tt",&ClassTimetable::automaticInsert_perday)
    .def("auto_insert",&ClassTimetable::insert_into_file)
    .def("printer",&ClassTimetable::printauto)
    ;
}