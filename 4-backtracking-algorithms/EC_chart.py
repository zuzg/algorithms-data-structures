import matplotlib.pyplot as plt
import numpy as np
import random

saturation = [0.2, 0.3, 0.4, 0.6, 0.8, 0.95]
n = [10, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]

def read_data(filename):
  data = []
  f = open(filename + ".txt")
  for no in n:
    temp = f.readline()
    temp = float(temp[temp.find(" ") + 1:temp.find("\n")])
    # print(temp)
    data.append(temp)
  f.close()
  return data

DATA = [[], [], [], [], [], []]


for j in range(6):
    DATA[j].append(read_data("saturation{}".format(j)))

RESULTS = [[], [], [], [], [], []]

for x in range(len(saturation)):
  RESULTS[x] = np.mean(DATA[x], axis=0)

for x in range(6):
  print(RESULTS[x])

f = open("FINAL.txt", 'w')

f.write("sat\t")
for pom in (saturation):
    f.write(str(pom)+"\t")

f.write("\n")
for i in range(len(n)):
    f.write(str(n[i])+"\t")
    for j in range(6):
        f.write(str(round(RESULTS[j][i], 4))+"\t")
    f.write("\n")
f.close()

fig, ax = plt.subplots(figsize=(12, 8))
for i in range(6):
  # print(RESULTS[i])
  # print(n)
  ax.plot(n, RESULTS[i], label=saturation[i])

ax.set_xlabel("n")
ax.set_ylabel("time [s]")
plt.legend(bbox_to_anchor=(0.07, 0.8), loc='upper left', borderaxespad=0.)
# ax.set_yscale("log")
plt.grid(True)
ax.set_title("searching for Eulerian cycle")
plt.show
plt.savefig("euler.png")