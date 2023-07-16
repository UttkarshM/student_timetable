class Database:
    def __init__(self):
        self.no_of_subs = ""
        self.sub_name = ""
        self.credits = ""


def input_details():
    global it
    d1 = Database()
    d1.no_of_subs = int(input("Enter the number of subjects: "))
    for subs in range(d1.no_of_subs):
        d1.sub_name = input("Enter the subject name: ")
        d1.credits = int(input("Enter the credit of the subject: "))
    return d1


input_details()
