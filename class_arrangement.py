import random

string_val = ['Chinese', 'English', 'Chinese',  'Math', 'English', 'Math', 'Chinese', 'English', 'Math', 'Chinese', 'English','Chinese', 'English', 'Math', 'Chinese', 'English',  'Math',  'Art', 'Art', 'Music', 'Painting']

new_class = []

print(string_val)
#print("total classes: ", len(my_classes))
while (len(string_val) > 0):

    ind = random.randint(0, len(string_val) - 1)
    #print(ind)
    #print(string_val[ind])
    new_class.append(string_val[ind])
    del string_val[ind]

print(new_class)
