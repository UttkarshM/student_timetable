echo -p "Do you want to execute the python gui file"
read answer
if (($answer=="yes"))
then
    python gui_py.py
else
    echo "you chose not to execute the python file"
fi