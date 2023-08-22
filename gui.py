from build.tester import *
import tkinter as tk

app=tk.Tk()
app.minsize(width=666, height=666)
app.maxsize(width=666, height=666)
def funct():
    global b
    py_obj=cpp_class() #making an object
    py_obj.loader()
    py_obj.subject_entry()
    list=py_obj.auto_tt()
    row=0
    column=0
    for l in list:
        row+=1
        column=0
        for ind in l:
            tk.Label(app,text=ind).grid(row=row,column=column)
            column+=1
b=tk.Button(app,text="call the function?",command=funct,state="normal")
b.grid(row=7,column=0)
#py_obj.auto_insert('K')

app.mainloop()