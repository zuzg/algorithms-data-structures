#include <bits/stdc++.h>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;

//dla wiekszych danych jest terminate "bad alloc", pamiec sie konczy ale nw jak to ogarnac xd
//chyba tyle wystarczy...

int ns[] = {10, 50, 100, 500, 1000, 2000, 5000, 10000, 15000, 20000};
int Ws[] = {10, 50, 100, 500, 1000, 2000, 5000, 10000, 15000, 20000};

int max(int a, int b)
{
    return (a > b) ? a : b;
}


int dynamic(int W, int *wt, int *val, int n)
{
    int i, w;
    vector<vector<int>> K(n+1, vector<int> (W+1));


    for(i = 0; i <= n; i++)
    {
        for(w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i-1] <= w)
                K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]], K[i-1][w]);
            else
                K[i][w] = K[i-1][w];
        }
    }
    return K[n][W];
}


int main()
{
    ofstream output("results/dynamic3d.txt");
    cout<<"n W time\n";

    for (unsigned int i = 0; i < sizeof(ns) / sizeof(*ns); i++)
    {
        int n = ns[i];
        int wt[n];
        int val[n];

        ifstream input;
        input.open("data/items" + to_string(n) + ".txt");
        if (!input) {
            cout << "File not opened!";
        }

        for(unsigned int j = 0; j < n; j++)
        {
            input>>wt[j]>>val[j];
        }
        input.close();

        for (unsigned int j = 0; j < sizeof(Ws) / sizeof(*Ws); j++)
        {
            int W = Ws[j];
            clock_t time_total = 0;

            clock_t time_start = clock();
            dynamic(W, wt, val, n);
            time_total = clock() - time_start;

            cout<<n<<" "<<W<<" "<<time_total<<"\n";
            output<<n<<" "<<W<<" "<<to_string(time_total)<<"\n";

        }
    }

    output.close();
    return 0;
}
