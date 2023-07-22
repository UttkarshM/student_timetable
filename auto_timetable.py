import random
class timetable:
    def __init__(self,subjects,Timetable,subject_to_credit):
        self.subjects=subjects
        self.Timetable=Timetable
        self.subject_to_credit=subject_to_credit
        self.i=0
    def get_subjects(self):
        with open('availableLanguages.txt','r') as file:
            data=(file.readlines())
            for subject in data:
                subject=subject[:-1].split() #removing the last element and converting it into a list
                self.subject_to_credit[subject[0]]=subject[1]
        print('available subjects are:')
        for index in self.subject_to_credit:
            print(index,end="  ")

        self.subjects=input('enter the subjects:').split()
        #file handling

        # print(self.subject_to_credit)
        for sub in self.subjects: # removes invalid subjects
            if sub not in self.subject_to_credit.keys():
                self.subjects.remove(sub) 
        
    def TimetablePerday(self,day=0):
        currentTimetable=[]
        size=len(self.subjects)-1
        randnum=random.random()%(size-0+1)+0
        random.shuffle(self.subjects)
        sum=0
        for i in range(size):
            sum+=int(self.subject_to_credit[self.subjects[i]])
            currentTimetable.append(self.subjects[i])        

        if(day<5):
            if(sum<100):
                self.TimetablePerday(0)
            day+=1
            self.TimetablePerday(day)
            self.Timetable.append(currentTimetable)
    
    def printtable(self):
        for day in self.Timetable:
            sum=0
            for period in day:
                sum+=int(self.subject_to_credit[period])
                print(f'{period} ',end=' || ')
            print(sum)

            

subject_to_credit={}
Timetable=[] # a list of lists
Subjects=[]
B_section = timetable(Subjects,Timetable,subject_to_credit)
B_section.get_subjects()
B_section.TimetablePerday()
B_section.printtable()