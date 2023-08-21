from build.tester import *

print(dir(cpp_class))
py_obj=cpp_class() #making an object
py_obj.loader()
py_obj.subject_entry()
list=py_obj.auto_tt()
for l in list:
    for ind in l:
        print(ind,end=' ')
    print()

py_obj.auto_insert()


