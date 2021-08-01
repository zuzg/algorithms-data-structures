#include <iostream>
#include <string.h>
#include <algorithm>
#include <list>
#include <fstream>
#include <time.h>

#define REPETITIONS 1

using namespace std;

int ns[] = {10, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
double sat[] = {0.2, 0.3, 0.4, 0.6, 0.8, 0.95};

int sptr;
int ** A;                    // Macierz s¹siedztwa
int * S;

void DFSEuler ( int v, int n)
{
  int i;

  for( i = 0; i < n; i++ )   // Przegl¹damy s¹siadów
    while( A [ v ][ i ] )
    {
      A [ v ][ i ] --;       // Usuwamy krawêdŸ
      A [ i ][ v ] --;
      //cout<<A [ v ][ i ]<<endl;
      DFSEuler ( i, n );        // Rekurencja
    }
  S [ sptr++ ] = v;          // Wierzcho³ek v umieszczamy na stosie
}

// Driver program to test above function
int main()
{
    printf("%-10s %-10s %-12s\n","S", "n", "search");
    for (int s=0; s<sizeof(sat)/sizeof(sat[0]); s++)
    {
        ofstream results;
        results.open("saturation" + to_string(s) + ".txt");

        for (unsigned int k = 0; k < sizeof(ns) / sizeof(*ns); k++)
        {
            int m, i ,j;
            //int ** A;                    // Macierz s¹siedztwa
                                 // Stos w tablicy
            int n = ns[k];
            m = 0;
            A = new int * [ n ];       // Tworzymy tablicê wskaŸników
                // Tworzymy stos
            sptr = 0;

            for( i = 0; i < n; i++ )
                A [ i ] = new int [ n ];

            for( i = 0; i < n; i++ )
                for( j = 0; j < n; j++ )
                    A [ i ][ j ] = 0;

            //cout<<" xd "<<"\n";
            clock_t time_total = 0;


            ifstream input;
            input.open("data/gnx" + to_string(n) + "sat" + to_string(s) + ".txt");
            //cout<<"graph"<<to_string(n)<<"sat"<<to_string(s)<<".txt";

            if (!input) {
                cout << "File not opened!";
            }

            int v1, v2;

            input>>v1>>v2;
            /*
            A [ v1 ][ v2 ] ++;
            A [ v2 ][ v1 ] ++;
            */
            //int counter =0;
            while (!input.eof()){
                A [ v1 ][ v2 ] ++;
                A [ v2 ][ v1 ] ++;
                //cout<<v1<<" "<<v2<<endl;
                input>>v1>>v2;
                m++;

                //counter++;
            }
            S = new int [ m + 1 ];
            //cout<<A [ 0 ][ 1 ]<<endl;

            clock_t time_start = clock();

            for (int k = 0; k < REPETITIONS; k++)
                DFSEuler ( 0, n );

            time_total = clock() - time_start;
            double out = double(time_total) / CLOCKS_PER_SEC;

            printf("%-10f %-10d %-12f\n", sat[s], n, out);
            results<<n<<" "<<to_string(out)<<"\n";

            for( i = 0; i < n; i++ ) delete [ ] A [ i ];

            delete [ ] A;
            delete [ ] S;



        }
        results.close();
    }



  return 0;
}
