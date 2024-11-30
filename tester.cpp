/// preprocessor definations
#include <algorithm>
#include <climits>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
// pybindings
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// marcos//change the value of the constants later.

#define WorkingDaysperWeek 5
#define MinCreditsPerday   3
#define MaxCreditsPerday   30
#define MaxPeriods         4

using namespace std;

namespace py = pybind11;

class ClassTimetable {
public:
  std::vector<std::string> Subjects;
  // std::vector<std::vector<std::vector<std::string>>> College_timetable;
  std::vector<std::vector<std::pair<std::string, int>>> Timetable;

  std::unordered_map<std::string, int> Subject_to_credits;
  std::unordered_map<std::string, int> TotalNumberofTeachers;
  char section;

  std::vector<std::vector<std::string>>
    AutoTimetable;  // for automatic timetable generation.

  /*this is a vector that contains vectors which contains all the subjects in a
  day , and the reason why we are using a pairs here is because we wanna map the
  subject to the course
  ,
  in python you can make a list that contains a list of dictionaries
  */
  // empty constructor
  ClassTimetable() { }
  int timetable_compare(string stre)
  {
    std::fstream file;
    file.open("Timetables/" + stre, ios::in);
    std::string buffer;
    std::vector<std::vector<std::string>> prev;
    while (getline(file, buffer)) {
      // cout<<buffer<<endl;
      vector<string> vtemp;
      string temp = "";
      for (char buff : buffer) {
        if (isalpha(buff) || buff == '+') {
          temp += buff;
        }
        else {
          if (temp.length() != 0) {
            vtemp.push_back(temp);
            temp = "";
          }
        }
      }
      if (vtemp.size() != 0) {
        prev.push_back(vtemp);
      }
    }

    // for(auto it:prev){
    //     for(auto iter:it){
    //         std::cout<<iter<<" ";
    //     }
    // }
    // cout<<prev.size()<<"-"<<Auto.size()<<endl;
    if (prev == AutoTimetable) {
      return 1;
    }
    return 0;
  }

  bool no_teachers_available()
  {
    unordered_map<std::string, int>::iterator iter;
    for (iter = TotalNumberofTeachers.begin();
         iter != TotalNumberofTeachers.end();
         iter++) {
      if (iter->second != 0) {
        return false;
      }
    }
    std::cout << "no teachers available";
    return true;
  }
  bool compare_tt(vector<vector<string>> autott)
  {
    DIR* dr;
    vector<string> files;
    struct dirent* en;
    dr = opendir("Timetables");  // open all or present directory
    if (dr) {
      while ((en = readdir(dr)) != NULL) {
        if (en->d_name[0] != '.') {  // dot means secret files
                                     // files.push_back(en->d_name);
          if (timetable_compare(en->d_name)) {
            return true;  // i.e duplicate
          }
        }
      }
      closedir(dr);  // close all directory
    }
    return false;  // i.e unique timetable
  }
  bool is_in(std::vector<std::vector<std::string>> large,
             std::vector<std::string> smallvec)
  {
    for (std::vector<std::string> it : large) {
      if (smallvec == it) {
        return true;
      }
    }
    return false;
  }
  int random_number(int max, int min = 0)
  {
    usleep(900000);
    srand(time(NULL));
    int random = rand() % (max - min + 1) + min;
    return random;
  }
  int DaysOccupied()
  {  // returns how many days have already been filled
    return Timetable.size();
  }
  int return_int(std::string str)
  {  // type conversion from character or string to int
    // some problem with stoi so i made this change this later
    int val = 0;
    for (char ch : str) {
      if (isdigit(ch)) {
        val = val * 10 +
              (ch - '0');  // ascii value of numbers start from 0-48 we are
                           // subtracting it to get the actual numbers.
                           // std::cout<<val<<"val+"<<ch<<std::endl;
      }
    }
    return val;
  }
  void is_newline(std::string stre)
  {  // used to check if there is a new line character in
     // your string. //debugging purposes.
    for (char ch : stre) {
      if (ch == '\n') {
        std::cout << "you have an newline character in the string" << std::endl;
      }
    }
  }
  std::unordered_map<std::string, int> parser(std::string stre)
  {  // contains information about the credit weightage
     // of each subject
    // TODO: can try to use a modern and more safer approach using the find()
    // method
    std::unordered_map<std::string, int> temp_map;
    std::string temp = "";
    std::pair<std::string, std::string> pir;
    for (auto it : stre) {
      if (it == ' ') {
        pir.first = temp;
        temp = "";
      }
      else {
        temp += it;
      }
    }
    pir.second = (temp);  // all the words except the last one get reset
    temp_map[pir.first] = return_int(pir.second);
    return temp_map;
  }
  void load_info()
  {  // loads information from the file
    std::fstream file;
    file.open("file_transfers/availableLanguages.txt", std::ios::in);
    std::string buffer;
    while (getline(file, buffer)) {
      for (auto it : parser(buffer)) {
        Subject_to_credits[it.first] = it.second;
      }
    }
    std::fstream file1;
    file1.open("file_transfers/availableteacher.txt", std::ios::in);
    std::string buffer1;
    while (getline(file1, buffer1)) {
      // cout<<buffer1<<endl;
      for (auto it : parser(buffer1)) {
        // cout<<it.first<<"-"<<it.second<<endl;
        TotalNumberofTeachers[it.first] = it.second;
      }
    }
    file1.close();
    // after this all the subjects have been loaded into the map;
    file.close();
  }

  void subjectEntry()
  {
    string buffer;
    std::fstream file1;
    file1.open("file_transfers/subject_transfer.txt");
    buffer = "";
    while (getline(file1, buffer)) {
      if (buffer[0] == '#') {
        section = buffer[1];
      }
      else {
        Subjects.push_back(buffer);
      }
    }
  }
  int i = 0;

  vector<vector<string>> automaticInsert_perday()
  {
    int day = 0, iter = 0;
    if (Subjects.empty()) {
      return { {} };
    }
    while (day < WorkingDaysperWeek && iter < 1000) {  // Limit iterations
      iter++;
      int creditsperday = 0;
      std::vector<std::string> currentDay;
      std::unordered_set<int> sets;
      int limit = std::min(static_cast<int>(Subjects.size()), MaxPeriods);

      std::random_device rd;
      std::shuffle(Subjects.begin(), Subjects.end(), rd);

      for (int i = 0; i < limit && creditsperday < MaxCreditsPerday; ++i) {
        if (no_teachers_available()) {
          std::cout << "No teachers are available." << std::endl;
          return AutoTimetable;
        }
        if (TotalNumberofTeachers[Subjects[i]] > 0) {
          TotalNumberofTeachers[Subjects[i]]--;
          currentDay.push_back(Subjects[i]);
          creditsperday += Subject_to_credits[Subjects[i]];
        }
      }

      if (creditsperday >= MinCreditsPerday) {
        day++;
        AutoTimetable.push_back(currentDay);
      }
    }

    if (Subjects.size() > 3 && compare_tt(AutoTimetable)) {
      std::cout << "Duplicate timetable." << std::endl;
    }

    return AutoTimetable;
  }

  void printauto()
  {
    for (auto it : AutoTimetable) {
      int sum = 0;
      for (auto iter : it) {
        sum += Subject_to_credits[iter];
        std::cout << iter << " ";
      }
    }
  }
  void insert_into_file(string section = "A")
  {
    std::fstream file;
    std::string name = "Timetables/" + (section) + "_section.txt";
    file.open(name, std::ios::out);
    for (auto it : AutoTimetable) {
      int sum = 0;
      for (auto iter : it) {
        sum += Subject_to_credits[iter];
        file << iter << " ";
      }
      file << "\n";
    }
  }
  void file_transplant()
  {
    fstream file, file1;
    file1.open("file_transfers/availableteacher.txt", ios::out);
    file1.close();
    file.open("file_transfers/availableteacher.txt", ios::app);
    unordered_map<string, int>::iterator it;
    for (it = TotalNumberofTeachers.begin(); it != TotalNumberofTeachers.end();
         ++it) {
      file << it->first << " " << it->second << "\n";
    }
  }
};
// int main(){
//     int choice;
//     ClassTimetable B_section;
//     //B_section.load_info();
//     cout<<B_section.TotalNumberofTeachers["c"]<<B_section.Subject_to_credits["c++"];
//     //make it a construct later so that it happens automatically.
//     B_section.subjectEntry();
//     auto vec=B_section.automaticInsert_perday();

//     B_section.printauto();
//     B_section.insert_into_file();
//     //it needs time for the inserting text to the file
//     //without a delay it would check an empty file
//     cout<<B_section.timetable_compare("Timetables/LL_section.txt");
//     cout<<B_section.compare_tt(vec);
//     B_section.file_transplant();
//     return 0;
// }

PYBIND11_MODULE(tester, handle)
{
  handle.doc() = "this is a module for creating a student timetable program";
  py::class_<ClassTimetable>(  // defining the class
    handle,
    "cpp_class")
    .def(py::init<>())  // for constructor
    // this is to expose the functions.
    .def("loader", &ClassTimetable::load_info)
    .def("parser", &ClassTimetable::parser)
    .def("subject_entry", &ClassTimetable::subjectEntry)
    .def("int_return", &ClassTimetable::return_int)
    .def("rand", &ClassTimetable::random_number)
    .def("in_side", &ClassTimetable::is_in)
    .def("auto_tt", &ClassTimetable::automaticInsert_perday)
    .def("auto_insert", &ClassTimetable::insert_into_file)
    .def("printer", &ClassTimetable::printauto)
    .def("compare", &ClassTimetable::compare_tt)
    .def("tt_compare", &ClassTimetable::compare_tt)
    .def("file__", &ClassTimetable::file_transplant)
    .def("NoTeachers", &ClassTimetable::no_teachers_available);
  ;
}
