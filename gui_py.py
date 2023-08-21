from tkinter import *
from tkinter import filedialog
import subprocess
app=Tk()

app.geometry('8000x6000')
app.minsize(width=666, height=666)
app.maxsize(width=666, height=666)
subjects=[]

def insert_subs_frame(): # initializes subjects list and also sends the information for c++ file.
    # global subjects
    frame = Frame(app,width=300,height=200,bg='white')
    frame.pack(fill='both',expand=1)
    insert__ = Entry(frame)
    insert__.grid(row=0,column=15, columnspan=10)
    stree=StringVar(frame,"enter the section in the box:")
    section = Entry(frame)
    Label(frame,textvariable=stree,fg="#f7d26a").grid(row=16,column=0,columnspan=2)
    section.grid(row=16,column=5,columnspan=2,padx=5)
    def entry(data=0):
        # global insert__
        current=insert__.get()
        insert__.delete(0,END)
        if(len(current)!=0):
            insert__.insert(0,str(current)+","+str(data))
        else:
            insert__.insert(0,str(data))
    def insert_button(frame,data,column=0,row=0):
            b=Button(frame,text=str(data),fg="black",bg="#f7d26a",padx=10,pady=10,command=lambda:entry(data))
            b.grid(row=row,column=0)
    frame.pack()
    available_subs=[]

    with open('student_timetable/availableLanguages.txt','r') as file:
        data=file.readlines()    
    row=1
    for subject in data:
        subject=subject[:-1]
        subject=subject.split(' ')
        subjects.append(subject[0])
        insert_button(frame,subject[0],0,row)
        row+=1
    def print():
        file1 = open('file_transfers/subject_transfer.txt','w') # to create a an empty file if it doesnt exist
        # to clear the file if anything is written
        sec = section.get()
        current=insert__.get()
        current=current.split(',')
        current=set(current)
        filep=open('file_transfers/subject_transfer.txt','a')
        for subs in current:
            filep.write(str(subs)+'\n')
        filep.write('#'+str(sec))
        #Label(frame,text=current).grid(row=16,column=0)
        Status.set('Processing')
        #//subprocess.run(["echo", "Geeks for geeks"],capture_output=True)
        subprocess.run('bash test.sh',shell=True)
        b1['state']=DISABLED # disables the button so that u cant generate it again.
        Status.set('Done')
    Status = StringVar(frame,'Process')
    b1=Button(frame,textvariable=Status,command=print)
    b1.grid(row=13,column=0)
    Button(frame,text="entry done.",command=frame.destroy).grid(row=14,column=0)

def display_Timetable():
    frame=Frame(app,width=5000,height=4000,bg='black')
    frame.pack(fill='both',expand=1)
    def file_explorer():
        if filedialog.askopenfilename(initialdir="Timetables/", title="select the timetable:",filetypes=(("all files","*.*"),("text","*.text"))):
            print(name)
            name=name.split('/')
            var=[]
            var.append(name[-2])
            var.append(name[-1])
            name='/'.join(var)
            return name
        else:
            return '0'
    name=file_explorer()
    if(name!='0'):
        with open() as file:
            data=file.readlines()
        #Label(frame,text=data,anchor='w',justify="left",fg='white').pack()
        row=0
        for day in data:
            Label(frame,text=day,anchor='w',justify="left",fg='white',bg='black').pack()
            row+=1
    Button(frame,text="exit.?",command=frame.destroy).pack()

def print():
    Label(app,text=subjects).pack()
Button(app,text="Insert subjects",bg='#032457',fg="white",cursor="hand2",activebackground="grey",activeforeground='black',command=insert_subs_frame).pack()
Button(app,text="display subjects",bg='#032457',fg="white",command=display_Timetable).pack()
Button(app,text="generate subjects",bg='#032457',fg="white").pack()
Button(app,text="exit frame",bg='#032457',fg="white",command=app.destroy).pack()

app.mainloop()
