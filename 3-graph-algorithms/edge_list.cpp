#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <string>

using namespace std;

int N[] = {10, 20, 30 , 40, 50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};

class Graph {
private:
    // number of vertices
    int v;
    int e;
    // adjacency matrix
    vector< pair<int, int> >edges;

public:
    int temp_e; //current no of edges

    // constructor
    Graph(int x)
    {
        v = x;
    }

    void displayEdgeList()
    {
        cout << "\nEdge List:\n";
        for (int i = 0; i < edges.size(); i++) {
            cout<<"("<<edges[i].first<<", "<<edges[i].second<<")\n";
        }
    }

    void addEdge(int x, int y)
    {
        edges.push_back(make_pair(x, y));
    }

    bool existEdge (int x, int y)
    {
        for (int i=0; i<edges.size(); i++)
        {
            if ((edges[i].first == x && edges[i].second ==y)||(edges[i].first == y && edges[i].second ==x)) return true;
        }
        return false;
    }

    void deleteGraph ()
    {
        edges.clear(); //XDDDD
    }
};

double SearchTime (Graph *g, int N)
{
    ifstream file;
    int ver1, ver2;
    int edges[N][2];

    file.open("data/search"+to_string(N)+".txt"); //reading the edges to be searched from a file (beda w liscie parami)
    for (int i=0; i<N; i++)
    {
        file>>edges[i][0]>>edges[i][1];
    }
    file.close();

    clock_t search_time_total = 0;
    clock_t search_time = clock();
    for (int i =0; i<N; i++)
    {
        (*g).existEdge(edges[i][0], edges[i][1]);
    }
    search_time_total += clock() - search_time;
    return (double)search_time_total/CLOCKS_PER_SEC*1000/N;
}

int main()
{
    printf("%-10s %-12s\n", "n", "search");
    ofstream results;
    results.open("Edge List.txt");

    for (int x = 0; x < sizeof(N)/sizeof(N[0]); x++)
    {
        Graph graph(N[x]);
        ifstream file;
        file.open("data/graph"+to_string(N[x])+".txt");

        ///ADDING EDGES
        int vertex1, vertex2;
        file>>vertex1>>vertex2; //pierwsze musi byc zadeklarowane poza bo inaczej ostatnia para jest 2x - na koncu jest enter wiec technically to nie jest eof
        while (!file.eof()){
            graph.addEdge(vertex1,vertex2);
            file>>vertex1>>vertex2;
        }
        file.close();
        if (N[x]==10) graph.displayEdgeList(); //mozna sobie zobaczyc jak wyglada matrix
        double totalTime = SearchTime(&graph, N[x]);

        printf("%-10d %-12f\n", N[x], totalTime);
        results<<N[x]<<" "<<to_string(totalTime)<<"\n";
        graph.deleteGraph();
    }

    results.close();
    return 0;
}
