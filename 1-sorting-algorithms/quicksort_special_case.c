#include <assert.h> //header file, preprocessor macro
#include <limits.h> //defines values properties for types
#include <stdio.h> //basic c library, defines size_t, FILE, fpos_t ...
#include <stdlib.h> //basic c library, defines ... for performing general functions
#include <string.h> //used for manipulating arrays of characters
#include <time.h> //used to measure time

int ns[] = { 99999, 100000, 100001};
int ile_liczb=3;
double T_time;

    void swap(int *a, int *b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    void fill_random(int *A, int n) {
        for (int i = 0; i < n; i++) {
            A[i] = rand() % n;
        }
    }

  void fill_ashape(int *A, int n){

        for(int i=0; i<=n/2; i++)
        {
            A[i]=1+2*i;
        }
        if (n%2==0){
        for(int i=0; i<n/2; i++)
        {
            A[n/2+i]=n-2-2*i;
        }}

        else{
            for(int i=0; i<=n/2; i++)
        {
            A[n/2+i]=n-1-2*i;
        }
        }
    }

       void fill_vshape(int *A, int n) {

        if (n%2==0){
        for(int i=0; i<n/2; i++)
        {
            A[i]=n-1-2*i;
        }}
        else {
        for(int i=0; i<n/2; i++)
        {
            A[i]=n-2-2*i;
        }}

        for(int i=0; i<=n/2; i++)
        {
            A[n/2+i]=2*i;
        }
    }

    void quick_sort(int *A, int left, int right) {
        if (right<=left) return;
        int i = left;
        int j = right;
        int x = A[(left+right) / 2 ]; //pivot value equals to the value of the element laying in the middle of an array
        do
        {
            //searching for the element that is respectively bigger/smaller than x
            while( A[ i ] < x ) i++;
            while( A[ j ] > x ) j--;

            //swapping previously selected elements if possible (no point in swapping if i>j)
            if( i <= j )
            {
                swap(&A[ i ], &A[ j ] );
                i++;
                j--;
            }
        } while( i <= j );

        //sorting two subarrays limited by the indices i, j
        if( left < j ) quick_sort( A, left, j );
        if( right > i ) quick_sort( A, i, right );
    }

    void quick_sort_all(int *A, int n) {
        quick_sort(A, 0, n - 1);
    }

void (*fill_functions[])(int *, int) = { fill_random, fill_ashape, fill_vshape };
char *fill_names[] = {"Random", "A-shape", "V-Shape" };

int main() {

    FILE *file =fopen("results.txt", "w");

            for (unsigned int j = 0; j < 3 ; j++) {
                void (*fill)(int *, int) = fill_functions[j];

                for (unsigned int k = 0; k < ile_liczb; k++) {
                    int n = ns[k];
                    T_time=0.0;

                        int *A = calloc(n, sizeof(*A));
                        /*allocating a block of memory for an array of n elements, each of them 4 bytes long*/
                        fill(A, n);
                        clock_t begin = clock();
                        /*number of clock ticks passed since the program was launched*/
                        quick_sort_all(A, n);
                        clock_t end = clock(); // -||-
                        T_time += (double)(end - begin) / (double) CLOCKS_PER_SEC; /*the difference between begin and end divided
                        by the number of clock ticks per second gives the actual time spent on sorting an array*/
                        free(A); //releasing previously allocated blocks of memory

                    printf("%-11s %-10d %g\n",  fill_names[j], n, T_time);
                    fprintf(file, "%s;%d;%g\n", fill_names[j], n, T_time);

                }
            }
    fclose(file);
    return 0;
}
