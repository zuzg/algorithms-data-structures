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

    // adjacency matrix
    vector< vector<int> > matrix;

public:
    // constructor
    Graph(int x)
    {
        v = x;
        matrix.resize(v); //rows
        for(int i = 0 ; i < v ; ++i)
        {
            matrix[i].resize(v); //columns
        }


        // initializing each element of the adjacency matrix to zero
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                matrix[i][j] = 0;
            }
        }
    }

    void displayAdjacencyMatrix()
    {
        cout << "\n Adjacency Matrix:";
        // displaying the 2D array
        for (int i = 0; i < v; i++) {
            cout << "\n";
            for (int j = 0; j < v; j++) {
                cout << " " << matrix[i][j];
            }
        }
        cout<<endl;
    }

    void addEdge(int x, int y)
    {
        // connecting the vertices (zakladamy ze input jest dobry)
        matrix[y][x] = 1;
        matrix[x][y] = 1;
    }

    bool existEdge (int x, int y)
    {
        return (matrix [x][y] == 1) ? true : false;
    }

    void deleteMatrix ()
    {
        for (int i = 0; i < v; i++)
        {
            matrix[i].clear();
            matrix[i].shrink_to_fit();
        }
        matrix.clear();
        matrix.shrink_to_fit();
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
    results.open("Vertex Matrix.txt");

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

        if (N[x]==10) graph.displayAdjacencyMatrix(); //mozna sobie zobaczyc jak wyglada matrix

        double totalTime = SearchTime(&graph, N[x]);
        printf("%-10d %-12f\n", N[x], totalTime);
        results<<N[x]<<" "<<to_string(totalTime)<<"\n";
        graph.deleteMatrix();
    }

    results.close();
    return 0;
}
