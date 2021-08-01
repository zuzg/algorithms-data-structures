# names is a library to generate random names
# !sudo pip install names
import names
import random

def generate(n):
  f = open("students%s.txt" %n, 'w')
  idx = list(range(1000000, 1000000 + n)) # since index requires 7 digits
  random.shuffle(idx) # randomize the list
  for id in idx:
    f.write(str(id) + " " + names.get_full_name() + "\n")
  f.close()

# insert needed sizes of students' lists
sizes = [1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000, 13000, 14000, 15000]

for s in sizes:
  generate(s)
  print(str(s) + " elements done\n") # simple print to track progress of generating files

# output format:    
# 1000002 Joseph Alvarez    
