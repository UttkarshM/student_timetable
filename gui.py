from build.tester import *
from tkinter import *
from tkinter import ttk

app=Tk()
app.minsize(width=500, height=500)
app.maxsize(width=750, height=500)

section_tmp=''

def funct():
# var1.set('generating..')
    frame=Frame(app,width=500,height=500,bg='#ff6e40')
    frame.place(relx=0.25,rely=0.3)
    Label(frame,text='').grid(row=0,column=0)
    canvas=Canvas(frame,height=500,width=500,bg='#f5f0e1')
    canvas.grid(row=0,column=0,padx=10,pady=10)
    # b['state']=DISABLED
    # frame.grid_propagate(False)
    canvas.grid_propagate(False)
    py_obj=cpp_class() #making an object
    py_obj.loader()
    py_obj.subject_entry()

    list=py_obj.auto_tt()
    print(section_tmp)
    def insert_into_file():
        curr = section__.get()
        py_obj.auto_insert(str(curr))
        frame.destroy()
    # var1.set('generated..')
    # row=0
    # column=0
    # for l in list:
    #     row+=1
    #     column=0
    #     for ind in l:
    #         Label(canvas,text=ind,bg='grey',fg='white').grid(row=row,column=column,columnspan=1,padx=5,pady=2)
    #         column+=1
    # active=0
    # Button(frame,text="destory the frame",command=frame.destroy).grid(row=row+3,column=0)
    column = ('Day','9:30','10:30',"11:30",'12:30','13:30','14:30','15:30','16:30','17:30')
    number_of_columns = []
    for i in range(len(max(list))+2):
        stre= 'd'+str(i)
        number_of_columns.append(stre)
    number_of_columns=tuple(number_of_columns)
    table = ttk.Treeview(canvas,columns=number_of_columns,show='headings') #show is used to arranging the elements
    #table.heading(number_of_columns[1],text=column[1])
    #table.heading(number_of_columns[2],text=column[2])
    #table.heading(number_of_columns[3],text=column[3])
    # table.heading(number_of_columns[4],text=column[4])
    for i in range(len(max(list))+2):
        table.heading(number_of_columns[i],text=column[i])
    table.pack(fill='both',expand=True)
    index=0
    days=['Monday','Tuesday','Wednesday','Thursday','Friday']
    for ind in list:
        tmp=[]
        tmp.append(days[index])
        for i in ind:
            tmp.append(i)
        t=tuple(tmp)
        table.insert(parent='',index=END,values=t)
        index+=1
    active=1
    section__=Entry(frame)
    section__.grid(row=7,column=0)
    #section__.set('A')
    Button(frame,text='want to save the file',command=insert_into_file).grid(row=9,column=0)
    Button(frame,text='exit',command=frame.destroy).grid(row=10,column=0)

def input_fn():
    gen['state']=DISABLED #disables the button so that multiple cannot open simulatinously
    frame1 = Frame(app,width=500,height=700,bg='#ff6e40')
    frame1.place(relx=0.25,rely=0.3)
    frame=Canvas(frame1,height=400,width=500,bg='#f5f0e1')
    frame.grid(row=0,column=0,padx=2,pady=5)
    section = Entry(frame,width=75)
    section__ = Entry(frame,width=12)
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
        gen['state']=NORMAL
        section_tmp = section__.get()
        print(section_tmp)
        file.close()
        file1.close()
        frame1.destroy()
    # section.place(height=100,width = 200,x=11,y=1)
    section.grid(columnspan=3,pady=20)

    load_subs()

var1=StringVar()
active = IntVar()
active.set(0)
var1.set('generate')
gen=Button(app,textvariable=var1,command=funct,state=DISABLED)
gen.place(relx=0.4,rely=0.05)
file_inp = Button(app,text="subjects list?",command=input_fn)
file_inp.place(relx=0.25,rely=0.05)
Button(app,text="exit",command=app.destroy).place(relx=0.55,rely=0.05)

#py_obj.auto_insert('K')
app.mainloop()