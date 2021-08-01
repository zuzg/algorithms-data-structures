import matplotlib.pyplot as plt

label = ["topological search"]
x = [10, 100, 150, 200, 250, 300, 350, 400, 500, 600, 700, 800, 900, 1000]


def readxdata(filename):
  data = []
  f = open(filename)
  for no in x:
    temp = f.readline()
    temp = float(temp[temp.find(" ") + 1:temp.find("\n")])
    # print(temp)
    data.append(temp/20)
  f.close()
  return data

def read_data(filename):
  data = []
  f = open(filename, 'r')
  for x in f:
    skip, val = x.split()
    data.append(float(val)/50)
  f.close()
  return data


DAG = read_data("DAGresults.txt")
fig, ax = plt.subplots(figsize = (12,8))
ax.plot(x, DAG, label = label[0])
ax.set_xlabel("n")
ax.set_ylabel("time expressed in ms")
plt.legend(bbox_to_anchor=(1.05,1), loc='upper left', borderaxespad = 0.)
plt.grid(True)
ax.set_title("topological search in DAG")
plt.show
plt.savefig("DAGchart5.png")