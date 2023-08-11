from tkinter import *
from tkinter import filedialog
app=Tk()
app.geometry('8000x6000')
subjects=[]


def insert_subs_frame(): # initializes subjects list and also sends the information for c++ file.
    global subjects
    frame = Frame(app,width=300,height=200,bg='yellow')
    frame.pack(fill='both',expand=1)
    insert__ = Entry(frame)
    insert__.grid(row=0,column=15, columnspan=10)

    def entry(data=0):
        # global insert__
        current=insert__.get()
        insert__.delete(0,END)
        if(len(current)!=0):
            insert__.insert(0,str(current)+","+str(data))
        else:
            insert__.insert(0,str(data))
    def insert_button(frame,data,column=0,row=0):
            b=Button(frame,text=str(data),fg="red",bg="yellow",padx=10,pady=10,command=lambda:entry(data))
            b.grid(row=row,column=0)

    frame.pack()
    available_subs=[]

    with open('availableLanguages.txt','r') as file:
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
        file1.write('')
        current=insert__.get()
        current=current.split(',')
        filep=open('file_transfers/subject_transfer.txt','a')
        for subs in current:
            filep.write(str(subs)+'\n')
        #Label(frame,text=current).grid(row=16,column=0)
    
    Button(frame,text="printer",command=print).grid(row=13,column=0)
    Button(frame,text="done",command=frame.destroy).grid(row=14,column=0)

def display_Timetable():
    frame=Frame(app,width=5000,height=4000,bg='black')
    frame.pack(fill='both',expand=1)
    def file_explorer():
        name=filedialog.askopenfilename(initialdir="Timetables/", title="select the timetable:",filetypes=(("jpg files","*.jpg"),("all files","*.*")))
        print(name)
        name=name.split('/')
        var=[]
        var.append(name[-2])
        var.append(name[-1])
        name='/'.join(var)
        return name
    with open(file_explorer()) as file:
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
