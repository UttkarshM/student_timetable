class MyStructure:
    def __init__(self, sub_name, sub_credit):
        self.subName = sub_name
        self.subCredit = sub_credit


# Function to take input from the user
def get_input():
    sub_name = input("Enter the subject name: ")
    sub_credit = int(input("Enter the credits of the subject: "))
    return sub_name, sub_credit


# Create a list of MyStructure instances
table = []
num_subs = int(input("Enter the number of subjects you want to add: "))

for i in range(num_subs):
    name, credit = get_input()
    table.append(MyStructure(name, credit))

# Print values for each instance
for j in table:
    print()
    print(f"Sub name: {j.subName.upper()}")
    print(f"Sub credit: {j.subCredit}")
