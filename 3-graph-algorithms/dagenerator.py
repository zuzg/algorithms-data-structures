import random
import copy
from collections import defaultdict

#to dziala ale to chora rekurencja ktora zabiera b. duzo czasu
#troche kombinowane bylo zeby zrobic wieksza data

class Graph():
    def __init__(self, vertices):
        self.graph = defaultdict(list)
        self.V = vertices

    def addEdge(self, u, v):
        self.graph[u].append(v)

    def isCyclicUtil(self, v, visited, recStack):

        # Mark current node as visited and
        # adds to recursion stack
        visited[v] = True
        recStack[v] = True

        # Recur for all neighbours
        # if any neighbour is visited and in
        # recStack then graph is cyclic
        for neighbour in self.graph[v]:
            if visited[neighbour] == False:
                if self.isCyclicUtil(neighbour, visited, recStack) == True:
                    return True
            elif recStack[neighbour] == True:
                return True

        # The node needs to be poped from
        # recursion stack before function ends
        recStack[v] = False
        return False

    # Returns true if graph is cyclic else false
    def isCyclic(self):
        visited = [False] * self.V
        recStack = [False] * self.V
        for node in range(self.V):
            if visited[node] == False:
                if self.isCyclicUtil(node, visited, recStack) == True:
                    return True
        return False

def generateDAG(e, v):
    i = 0
    g = Graph(v)
    g0 = Graph(v)

    f = open("NEWinputDAG%s.txt" % n, 'w')

    while i < e:
        e1 = random.randint(0, v - 1)
        e2 = random.randint(0, v - 1)

        if e1 != e2:
            g.addEdge(e1, e2)
            if g.isCyclic() == False:
                #print(e1, e2)
                f.write(str(e1) + " " + str(e2) + "\n")
                g0 = copy.deepcopy(g)
                i += 1
                if i % 10000 == 0:
                    print(i)
            else:
                g = copy.deepcopy(g0)
    f.close()
    return i

sizes = [10, 150, 250, 350]

for n in sizes:
    ed = int(n * (n - 1) * 0.5 * 0.3)
    g = generateDAG(ed, n)
    print(str(n) + " elements done\n")





