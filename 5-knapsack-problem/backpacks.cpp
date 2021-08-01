#include <bits/stdc++.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#define CAPACITY 20

/* SETTINGS */
#define SPECIAL_DATA false
#define CONSTANT_CAPACITY false
#define BIG_DATA true

using namespace std;

int set1[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
int set2[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};

struct Item{
    int value;
    int weight;
};

bool cmp(struct Item a, struct Item b)
{
    double r1 = (double)a.value / (double)a.weight;
    double r2 = (double)b.value / (double)b.weight;
    return r1 > r2;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int dynamic(int W, Item * arr, int n)
{
    int i, w;
    vector<vector<int>> K(n+1, vector<int> (W+1));


    for(i = 0; i <= n; i++)
    {
        for(w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (arr[i-1].weight <= w)
                K[i][w] = max(arr[i-1].value + K[i-1][w-arr[i-1].weight], K[i-1][w]);
            else
                K[i][w] = K[i-1][w];
        }
    }
    return K[n][W];
}

int greedy(int W, Item * arr, int n)
{
    int result = 0;
    int no_item = n-1;

    while (no_item >= 0 && W > 0)
    {
        if (arr[no_item].weight <= W)
        {
            result += arr[no_item].value;
            W -= arr[no_item].weight;
        }
        no_item--;
    }
    return result;
}

int BF(int W, Item * arr, int n)
{

    // Base Case
    if (n == 0 || W == 0)
        return 0;

    // If weight of the nth item is more than Knapsack capacity W, then
    // this item cannot be included in the optimal solution
    if (arr[n - 1].weight > W)
        return BF(W, arr, n - 1);

    // Return the maximum of two cases:
    // (1) nth item included
    // (2) not included
    else
        return max(arr[n - 1].value + BF(W - arr[n - 1].weight, arr, n - 1), BF(W, arr, n - 1));
}

int main()
{
    int ns[10];
    if(BIG_DATA) copy(begin(set2), end(set2), begin(ns));
    else copy(begin(set1), end(set1), begin(ns));

    ofstream output;
    ofstream output2;
    ofstream output3;

    if (BIG_DATA)
    {
        output.open("results/DP_big.txt");
        output2.open("results/BF_big.txt");
        output3.open("results/GA_big.txt");
    }

    else if (!SPECIAL_DATA){
        output.open("results/DP.txt");
        output2.open("results/BF.txt");
        output3.open("results/GA.txt");
    }

    else {
        output.open("results/DP_special.txt");
        output2.open("results/BF_special.txt");
        output3.open("results/GA_special.txt");
    }


    cout<<"\tn\ttime\tperformence\n";
    int cap_pom = CAPACITY;

    for (unsigned int i = 0; i < sizeof(ns) / sizeof(*ns); i++)
    {
        int n = ns[i];
        Item arr[n];

        ///DATA READER
        ifstream input;
        if (SPECIAL_DATA)
            input.open("data_special/items" + to_string(n) + ".txt");
        else
            input.open("data/items" + to_string(n) + ".txt");

        if (!input) {
            cout << "File not opened!";
        }

        for(unsigned int j = 0; j < n; j++)
        {
            input>>arr[j].weight>>arr[j].value;
            //cout<<arr[j].weight<<" "<<arr[j].value<<endl;
        }
        input.close();

        int result;
        clock_t time_total;
        clock_t time_start;


        ///DYNAMIC
        time_start = clock();
        result = dynamic(cap_pom, arr, n);
        time_total = clock() - time_start;

        cout<<"DYN:\t"<<n<<"\t"<<time_total<<"\t"<<result<<"\n";
        output<<n<<" "<<result<<" "<<time_total<<"\n";

        ///BRUTE FORCE
        if (!BIG_DATA){
        time_start = clock();
        result = BF(cap_pom, arr, n);
        time_total = clock() - time_start;

        cout<<"BF:\t"<<n<<"\t"<<time_total<<"\t"<<result<<"\n";
        output2<<n<<" "<<result<<" "<<time_total<<"\n";
        }

        ///GREEDY
        time_start = clock();
        sort(arr, arr + n, cmp);
        result = greedy(cap_pom, arr, n);
        time_total = clock() - time_start;

        cout<<"GR:\t"<<n<<"\t"<<time_total<<"\t"<<result<<"\n";
        output3<<n<<" "<<" "<<result<<" "<<time_total<<"\n";

        if(!CONSTANT_CAPACITY) cap_pom+=CAPACITY;
    }
    output.close();
    output2.close();
    output3.close();
    return 0;
}
