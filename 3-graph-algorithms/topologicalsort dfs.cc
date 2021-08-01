#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <time.h>
#include<bits/stdc++.h>
#define REPETITIONS 100

using namespace std;

int ns[] = {10, 100, 150, 200, 250, 300, 350, 400, 500, 600, 700, 800, 900, 1000};


// Class to represent a graph
class Graph {
    // No. of vertices'
    int V;

    // Pointer to an array containing adjacency listsList
    list<int>* adj;

    // A function used by topologicalSort
    void topologicalSortUtil(int v, bool visited[], stack<int>& Stack);

public:
    // Constructor
    Graph(int V);

    // function to add an edge to graph
    void addEdge(int v, int w);

    // prints a Topological Sort ofthe complete graph
    void topologicalSort();

    void printGraph(int V);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    // Add w to v’s list.
    adj[v].push_back(w);
}

// A recursive function used by topologicalSort
void Graph::topologicalSortUtil(int v, bool visited[], stack<int>& Stack)
{
    // Mark the current node as visited.
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            topologicalSortUtil(*i, visited, Stack);

    // Push current vertex to stack which stores result
    Stack.push(v);
}

// The function to do Topological Sort.
// It uses recursive topologicalSortUtil()
void Graph::topologicalSort()
{
    stack<int> Stack;

    // Mark all the vertices as not visited
    bool* visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Call the recursive helper function to store Topological Sort starting from all vertices one by one
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            topologicalSortUtil(i, visited, Stack);

    // Print contents of stack
    /*
    while (Stack.empty() == false) {
        cout << Stack.top() << " ";
        Stack.pop();
    }*/

}
//int v: graph.adjList[i]
void Graph::printGraph(int V)
{
    for (int v = 0; v < V; ++v)
    {
        cout << "\n Adjacency list of vertex " << v << "\n head ";
        for (int x : adj[v])
           cout << "-> " << x;
        printf("\n");
    }
}

// Driver Code
int main()
{
    //FILE *fp = fopen("DAG_output.txt", "w");
    cout<<"n    time\n";
    //output<<"n  time\n";

    for (int TRIAL = 0; TRIAL < 10; TRIAL++){
    ofstream output("DFSresults_"+to_string(TRIAL)+".txt");
    for (unsigned int j = 0; j < sizeof(ns) / sizeof(*ns); j++)
    {
        int n = ns[j];
        clock_t time_total = 0;

        Graph g(n);

        char str[40];
        snprintf(str, 30, "data/DAG%d_%d.txt", n, TRIAL);
        //FILE *f = fopen(str, "r");
        ifstream input(str);
        if (!input) {
            cout << "File not opened!";
        }

        int ed = int(n * (n-1) * 0.5 * 0.3);
        //int ed = 13;
        int v1, v2;

        for(int i = 0; i < ed; i ++)
        {
            input>>v1;
            input>>v2;
            //cout<<v1<<" "<<v2<<endl;;
            g.addEdge(v1, v2);

        }
        clock_t time_start = clock();

        for (int k = 0; k < REPETITIONS; k++)
            g.topologicalSort();

        time_total = clock() - time_start;

        double result = time_total;

        //printf("%d %lf\n", n, result);

        cout<<n<<" "<<result<<"\n";
        output<<n<<" "<<to_string(result)<<"\n";
        input.close();
        //g.printGraph(n);
    }
    output.close();
    }
    return 0;
}
