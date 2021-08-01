#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <time.h>
#include<bits/stdc++.h>

#define REPETITIONS 50

using namespace std;

int ns[] = {10, 100, 150, 200, 250, 300, 350, 400, 500, 600, 700, 800, 900, 1000};

class Graph {
    int V;
    list<int>* adj;

public:
    Graph(int V);
    void addEdge(int u, int v);
    void topologicalSort();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
}

void Graph::topologicalSort()
{
    // Create a vector to store indegrees of all vertices.
    // Initialize all indegrees as 0.
    vector<int> in_degree(V, 0);

    // Traverse adjacency lists to fill indegrees of vertices.
    // This step takes O(V+E) time
    for (int u = 0; u < V; u++) {
        list<int>::iterator itr;
        for (itr = adj[u].begin(); itr != adj[u].end(); itr++)
            in_degree[*itr]++;
    }

    // Create an queue and enqueue  all vertices with indegree 0
    queue<int> q;
    for (int i = 0; i < V; i++)
        if (in_degree[i] == 0)
            q.push(i);

    // Initialize count of visited vertices
    int cnt = 0;

    // Create a vector to store result (A topological ordering of the vertices)
    vector<int> top_order;

    // One by one dequeue vertices from queue and enqueue
    // adjacents if indegree of adjacent becomes 0
    while (!q.empty()) {
        // Extract front of queue (or perform dequeue)
        // and add it to topological order
        int u = q.front();
        q.pop();
        top_order.push_back(u);

        // Iterate through all its neighbouring nodes of dequeued node u and
        // decrease their in-degree  by 1
        list<int>::iterator itr;
        for (itr = adj[u].begin(); itr != adj[u].end(); itr++)

            // If in-degree becomes zero,
            // add it to queue
            if (--in_degree[*itr] == 0)
                q.push(*itr);

        cnt++;
    }

    // Check if there was a cycle

    if (cnt != V) {
        cout << "There exists a cycle in the graph\n";
        return;
    }

    // Print topological order
    /*
    for (int i = 0; i < top_order.size(); i++)
        cout << top_order[i] << " ";
    cout << endl;*/

}

// Driver Code
int main()
{
    ofstream output("DAGresults.txt");
    //FILE *fp = fopen("DAG_output.txt", "w");
    cout<<"n    time\n";
    //output<<"n  time\n";

    for (unsigned int j = 0; j < sizeof(ns) / sizeof(*ns); j++)
    {
        int n = ns[j];
        clock_t time_total = 0;

        Graph g(n);

        char str[30];
        snprintf(str, 30, "data/NEWinputDAG%d.txt", n);
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

        printf("%d %lf\n", n, result);

        cout<<n<<" "<<result<<"\n";
        output<<n<<" "<<to_string(result)<<"\n";
        input.close();
        //g.printGraph(n);
    }
    output.close();
    return 0;
}

