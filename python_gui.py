from tkinter import *
from tkinter import filedialog

app = Tk()

app.title("Timetable")

def insert_frame(data,column,row,window=app):
    frame=LabelFrame(window,fg="white",bg="#ecc384")
    button=Button(frame,text=str(data),fg="#000000",bg="#ecc384")
    button.pack()
    frame.grid(row=row,column=column)
    # pass

def read_file(path=""):
    window1=Toplevel()
    if(path==""):
        name=input('enter the name of the section you wanna see:')
        path='Timetables/'+name+'_section.txt'
    with open(path) as file:
        data=file.readlines()
        row=0
        for day in data:
            column=0
            temp=day.split('||')
            temp.pop()
            # temp.pop() if len(temp)>0 else 0
            for period in temp:
                period.replace(" ","")
                insert_frame(period,column,row,window1)
                column+=1 #to insert in the next column
            row+=1

def subjectentry_console():
    pass
def file_explorer():
    name=filedialog.askopenfilename(initialdir="Timetables/", title="select the timetable:",filetypes=(("jpg files","*.jpg"),("all files","*.*")))
    name=name.split('/')
    var=[]
    var.append(name[-2])
    var.append(name[-1])
    name='/'.join(var)
    return name

read_file(file_explorer())


app.mainloop()