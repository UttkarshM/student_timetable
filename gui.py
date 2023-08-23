from build.tester import *
from tkinter import *

app=Tk()
app.minsize(width=666, height=666)
app.maxsize(width=666, height=666)
def funct():
    var1.set('generating..')
    frame=Frame(app,width=500,height=500,bg='#ff6e40')
    frame.grid(row=3,column=5,padx=10,pady=10)
    Label(frame,text='').grid(row=0,column=0)
    canvas=Canvas(frame,height=500,width=500,bg='#f5f0e1')
    canvas.grid(row=0,column=0,padx=10,pady=10)
    # b['state']=DISABLED
    py_obj=cpp_class() #making an object
    py_obj.loader()
    py_obj.subject_entry()
    list=py_obj.auto_tt()
    var1.set('generated..')
    row=0
    column=0
    for l in list:
        row+=1
        column=0
        for ind in l:
            Label(canvas,text=ind,fg='orange').grid(row=row,column=column)
            column+=1

def input_fn():
    frame1 = Frame(app,width=500,height=700,bg='#ff6e40')
    frame1.grid(row=3,column=5,padx=10,pady=10)
    Label(frame1,)
    frame=Canvas(frame1,height=400,width=500,bg='#f5f0e1')
    frame.grid(row=0,column=0,padx=10,pady=5)
    section = Entry(frame,width=75)
    items = []
    row=0;column=0
    def insert_into_entry(input):
        current=section.get()
        section.delete(0,END)
        if(len(current)!=0):
            section.insert(0,str(current)+","+str(input))
        else:
            section.insert(0,str(input))

    def insert_button(data,row,column):
        Button(frame,text=data,command=lambda:insert_into_entry(data)).grid(row=row,column=column)
    def load_subs():
        global variable
        row=0
        with open('file_transfers/availableLanguages.txt','r') as file:
            data=file.read()
        data=data.split('\n')
        i=3
        for index in data:
            column=i%3
            row=int(i/3)
            dru = (index.split(' '))[0]
            items.append((index.split(' '))[0])
            insert_button(dru,row,column)
            i+=1
            variable = StringVar()
        variable.set('done')
        b=Button(frame,textvariable=variable,command=insert_into_file)
        b.grid(row=row+1,column=1)
    def insert_into_file():
        list=section.get()
        list=list.split(',')
        list=set(list)
        variable.set('inserted!!')
        file=open('file_transfers/subject_transfer.txt','w')
        file1=open('file_transfers/subject_transfer.txt','a')
        for sub in list:
            file1.write(str(sub)+'\n')
        file.close()
        file1.close()
    # section.place(height=100,width = 200,x=11,y=1)
    section.grid(columnspan=3)

    load_subs()

var1=StringVar()
var1.set('generate the timetable.')
gen=Button(app,textvariable=var1,command=funct,state="normal")
gen.grid(row=0,column=0,columnspan=1)
file_inp = Button(app,text="subjects list?",command=input_fn)
file_inp.grid(row=1,column=0,columnspan=1)
#py_obj.auto_insert('K')

app.mainloop()