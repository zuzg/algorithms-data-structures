#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <string>
using namespace std;

int N[] = {10, 20, 30 , 40, 50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};

class Graph{

public:
    int V;                  //number of vertices
    vector<int> *arr;       //array of list pointers

    Graph(int vertices){
        this->V = vertices;
        arr = new vector<int>[vertices];
    }

    void addEdge (int x, int y)
    {
        arr[x].push_back(y);
        arr[y].push_back(x);
    }

    bool existEdge (int x, int y)
    {
        for (int i=0; i<arr[x].size(); i++)
        {
            if (arr[x][i] == y) return true;
            if (arr[y][i] == x) return true;
        }
        return false;
    }

    void printAdjList(){
        for(int i=0; i<V; i++){
            cout<<"Vertex "<<i<<"-> ";
            for(int nbr: arr[i])
            {
                cout<<nbr<<", ";
            }
            cout<<endl;
        }
    }

    void DeleteGraph ()
    {
        for(int i=0; i<V; i++)
        {
            arr[i].clear();
        }
        delete arr;
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
    results.open("Incidence List.txt");

    for (int x=0; x<sizeof(N)/sizeof(N[0]); x++)
    {
        Graph graph(N[x]);
        ifstream file;
        file.open("data/graph"+to_string(N[x])+".txt");

        int vertex1, vertex2;
        file>>vertex1>>vertex2;

        //int counter =0;
        while (!file.eof()){
            //cout<<"pair "<<counter<<": "<<vertex1<<", "<<vertex2<<endl;
            graph.addEdge(vertex1,vertex2);
            file>>vertex1>>vertex2;
            //counter++;
        }
        file.close();
        if (N[x]==10) graph.printAdjList();

        double totalTime = SearchTime(&graph, N[x]);
        printf("%-10d %-12f\n", N[x], totalTime);
        results<<N[x]<<" "<<to_string(totalTime)<<"\n";
        graph.DeleteGraph();
    }
}
