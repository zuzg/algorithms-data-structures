#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <string>
#define TRIALS 10
using namespace std;

int N[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
double sat[] = {0.2, 0.3, 0.4, 0.6, 0.8, 0.95}; //i.e. 0, 1, 2, 3, 4, 5

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

void printSolution(int path[], int N)
{
    cout << "Solution Exists (following is one Hamiltonian Cycle):\n";
    for (int i = 0; i < N; i++)
        cout << path[i] << " ";

    cout << path[0] << " ";
    cout << endl;
}

bool isSafe(int v, Graph * graph, int path[], int pos)
{
    if (!graph->existEdge(path[pos - 1], v ))
        return false;

    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

bool hamCycle(Graph * graph, int * path, int pos, int N, clock_t time_start)
{
    if ((clock()-time_start)/CLOCKS_PER_SEC >= 300){
        return false;
    }

    if (pos == N)
    {
        if (graph->existEdge(path[pos-1], 0))
            return true;
        else
            return false;
    }

    for (int v = 1; v < N; v++)
    {
        if (isSafe(v, graph, path, pos))
        //if (graph->existEdge(path[pos - 1], v) && !taken[v])
        {
            path[pos] = v;
            //taken[v] = true;
            if (hamCycle (graph, path, pos + 1, N, time_start) == true)
                return true;
            path[pos] = -1;
            //taken[v] = false;
        }
    }
    return false;
}

double GetHamiltonian(Graph * graph, int N)
{
    int *path = new int[N];
    //bool *taken = new bool[N];
    for (int i = 0; i < N; i++){
        path[i] = -1;
        //taken[i] = false;
    }
    path[0] = 0;
    //taken[0] = true;

    clock_t time_total = clock();
    bool ans = hamCycle(graph, path, 1, N, time_total);
    clock_t FINAL = clock() - time_total;
    if (FINAL > 300000)FINAL = 300000;

    //if (ans == false)cout << "Solution does not exist\n";
    //else printSolution(path, N);
    //if (ans==true) cout<<":)\n";

    delete path;
//delete taken;
    return double(FINAL);
}


int main()
{
    for (int T=0; T<TRIALS; T++){
        cout<<"TRIAL NO. " <<T;
        for (int s=0; s<sizeof(sat)/sizeof(sat[0]); s++){

        printf("\n%-10s %-10s %-12s\n","S", "n", "time");
        ofstream results;
        results.open("saturation"+to_string(s)+"_"+to_string(T)+".txt");

        for (int x = 0; x < sizeof(N)/sizeof(N[0]); x++)
        {
            Graph graph(N[x]);
            ifstream file;
            file.open("graph"+to_string(N[x])+"sat"+to_string(s)+"_"+to_string(T)+".txt");

            ///ADDING EDGES
            int vertex1, vertex2;
            double e = double(sat[s]*0.5* N[x]*(N[x]-1));
            for (int temp=0; temp<int(e); temp ++)
            {
                file>>vertex1>>vertex2;
                graph.addEdge(vertex1,vertex2);
                //cout<<vertex1<<" "<<vertex2<<endl;
            }
            file.close();

            //if (N[x]==20) graph.displayAdjacencyMatrix();
            double out = GetHamiltonian(&graph, N[x]);

            printf("%-10f %-10d %-12f\n", sat[s], N[x], out/1000);
            results<<N[x]<<" "<<to_string(out/1000)<<"\n";
            graph.deleteMatrix();
        }
        printf("DONE \n");
        results.close();
        }
    }
    return 0;
}
