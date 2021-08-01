import random
import networkx as nx
import time

TRIALS = 1
k = [(0.2, 0), (0.3, 1), (0.4, 2), (0.6, 3), (0.8, 4), (0.95, 5)]
#n = [10]
n = [10, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]


# n_ver, n_edg = total no of vertices and edges respectively
def generate(n_ver, saturation, trial):
    graph = nx.Graph()
    n_edg = int(saturation[0] * 0.5 * n_ver * (n_ver - 1))
    #print(n_ver, n_edg)
    if (n_edg < n_ver - 1):
        n_edg = n_ver - 1

    for i in range(1, n_edg + 1):  # bc we start from 1
        if (i < n_ver):
            a = random.randint(0, i - 1)
            b = i
        else:
            a = random.randint(0, n_ver - 1)
            b = random.randint(0, n_ver - 1)

        if (b != n_ver - 1):
            b += (b == a)
        else:
            if (b == a):
                a -= random.randint(1, n_ver - 1)

        if (a < b):  # (x, y) x < y
            graph.add_edges_from([(a, b)])
            #f.write(str(a) + " " + str(b) + "\n")
        else:
            graph.add_edges_from([(a, b)])
            #f.write(str(b) + " " + str(a) + "\n")

    return graph
# TO DO
# handle nodes with deg 1 - check before an connect

#doesnt work
def eulerize(G):
    odd = []
    even = []
    deg1 = []

    for v in G.nodes():
        if G.degree[v] == 1:
            deg1.append(v)
            #print(v)
    if deg1:
        for i in range(0, len(deg1)-1, 2):
            g.add_edge(deg1[i], deg1[i+1])
        if len(deg1) % 2 == 1:
            g.add_edge(deg1[len(deg1)-1], deg1[0])

    for v in G.nodes():
        if G.degree[v] % 2 == 0:
            even.append(v)
        else:
            odd.append(v)

    if len(odd) % 2 == 0:
        half = int(len(odd)/2)
    else:
        half = int(len(odd)/2) + 1

    #print(half)

    count = 0

    for i in range(len(odd)):
        for j in range(i+1, len(odd)):
            if count < half and i < len(odd) and j < len(odd):
                # if G.has_edge(odd[i], odd[j]) == True:
                if odd[i] in G[odd[j]] == True and G.degree[i] > 2 and G.degree[j] > 2:
                    a, b = odd[i], odd[j]
                    G.remove_edge(a, b)
                    odd.remove(a)
                    odd.remove(b)
                    count += 1


    if count < half and len(odd) % 2 == 1:
        G.add_edges_from([(a, b)])
        odd.append(a)
        odd.append(b)

    k = 0
    while k < len(odd):
        #a, b = odd.pop(i), odd.pop(j)
        if odd[k] in G[odd[k+1]] == False:
            G.add_edges_from([(odd[k], odd[k+1])])
        k += 2

    for v in G.nodes():
        if G.degree[v] % 2 == 1:
            print("fuck")



def write(g, n_ver, saturation, trial):
    f = open("data/gnx" + str(n_ver) + "sat" + str(saturation[1]) + ".txt", 'w')

    for v in g.nodes():
        if g.degree[v] % 2 == 1:
            print("fuck")

    for e in g.edges():
        f.write(str(e[0]) + " " + str(e[1]) + "\n")
    f.close()

for sat in k:
    f = open("saturation" + str(sat[1]) + ".txt", 'w')
    for ver in n:
        for trial in range(1, TRIALS + 1):
            g = generate(ver, sat, trial)
            G = nx.eulerize(g)
            #write(G, ver, sat, trial)
            #print ("DONE ", ver, sat)
            start = time.time()
            list(nx.eulerian_circuit(G))
            end = time.time()
            f.write(str(ver) + " " + str(end - start))

