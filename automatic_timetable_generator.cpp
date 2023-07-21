//preprocessor definations
#include<cctype>
#include<iostream>
#include<vector>
#include<unordered_map>
#include<cstring>
#include<fstream>
#include<stdlib.h>
#include<string>
#include<unistd.h>
#include<unordered_set>
#include<algorithm>
#include<random>
//marcos
#define NameLimit 100
#define NumberOfSubjects 2
#define Periods_perday 5
#define WorkingDaysperWeek 5

class ClassTimetable{
    std::vector<std::string>Subjects;
    std::vector<std::vector<std::pair<std::string,int>>> Timetable;
    
    std::unordered_map<std::string,int> Subject_to_credits;
    std::unordered_map<std::string,int> TotalNumberofTeachers;
    
    std::vector<std::vector<std::string>> AutoTimetable;
    /*this is a vector that contains vectors which contains all the subjects in a day ,
    and the reason why we are using a pairs here is because we wanna map the subject to the course
    , 
    in python you can make a list that contains a list of dictionaries
    */
    public:
    bool is_in(int num,std::vector<int> v){
        for(auto it:v){
            if(num==it){
                return true;
            }
        }
        return false;
    }
        int random_number(int max,int min=0){
            sleep(1);
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
            file1.open("availableLanguages.txt",std::ios::in);
            std::string buffer1;
            while(getline(file,buffer1)){
                for(auto it:parser(buffer1)){
                    TotalNumberofTeachers[it.first]=it.second;
                }
            }
            file1.close();
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
            if(strncmp("exit",subjectname,4)==0){
                std::cout<<"exited the current timetable\n";
                break;
            }
            subjectsCredit.first=subjectname;
            subjectsCredit.second=Subject_to_credits[subjectname];
            TimetableForDay.push_back(subjectsCredit);
        }
        Timetable.push_back(TimetableForDay);
        }
        void subjectEntry(){
            std::string input;

            std::cout<<"enter the subject"<<std::endl;
            displaythetopics();
            std::cin>>input;
            while(input!="exit"){
                Subjects.push_back(input);
                std::cout<<"enter your subject or press \"exit\" if your done"<<std::endl;
                displaythetopics();
                std::cin>>input;
            }
            for(auto it:Subjects){
                std::cout<<it<<std::endl;
            }
                std::cout<<std::endl;
                std::cout<<std::endl;
                std::cout<<std::endl;
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

                std::cout<<"\\"<<std::endl;
                std::cout<<"\\"<<std::endl;
            }
            }
            else{
                std::cout<<"table is empty"<<std::endl;
            }
        }
        int i=0;
        void automaticInsert_perday(int i=0){
            std::vector<std::string> currentDay;
            std::unordered_set<int> sets;
            int randnum=random_number(Subjects.size()-1,0);
            //int n=Subjects.size();

        //     while(sets.size()<=n){
        //         int num=random_number(n);
        //        // std::cout<<num<<std::endl;
        //         sets.insert(num);
        //     }
        // for(auto it:sets){
        //         int i=it;
        //         std::cout<<i<<"-"<<Subjects[i]<<std::endl;
        //     }
        // for(int i=0;i<n;i++){
        //     std::cout<<i<<"-"<<Subjects[i]<<std::endl;
        // }
            std::random_device rd;
            std::shuffle(Subjects.begin(), Subjects.end(), rd);
            //std::shuffle(Subjects.begin(),Subjects.end(), std::default_random_engine(0));
            std::vector<std::string>::iterator iter;
            //int index=0;
            // for(iter=Subjects.begin();iter!=Subjects.end();++iter){
            //     if(TotalNumberofTeachers[*iter]!=0){
            //         currentDay.push_back(*iter);
            //         index++;
            //     }
            for(int i=0;i<=randnum;i++){
                currentDay.push_back(Subjects[i]);
            }
            if(i<5){
                i++;
                AutoTimetable.push_back(currentDay);
                automaticInsert_perday(i);
            }
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
    // while(1){
    // std::cout<<"Choose one option out of these:\n1.)Insert another day\t2.)Display the current weekly timetable)\n3.)exit program\n";
    // std::cin>>choice;
    // switch(choice){
    //     case 1:
    //     if(B_section.DaysOccupied()<=WorkingDaysperWeek){
    //         B_section.TimetableInsert();
    //     }
    //     else{
    //         std::cout<<"the week has already been occupied completely"<<std::endl;
    //     }
    //     break;
    //     case 2:
    //         B_section.DisplayTimetable();
    //         break;
    //     case 3:
    //         std::cout<<"program has ended.";
    //         return 0; // exits the program directly
    //     default:
    //         std::cout<<"Invalid choice";
    //        break;
    // }
    // }
    B_section.subjectEntry();
    B_section.automaticInsert_perday();
    B_section.printauto();
    return 0;
}
