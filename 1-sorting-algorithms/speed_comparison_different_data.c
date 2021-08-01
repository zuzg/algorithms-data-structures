#include <assert.h> //header file, preprocessor macro
#include <limits.h> //defines values properties for types
#include <stdio.h> //basic c library, defines size_t, FILE, fpos_t ...
#include <stdlib.h> //basic c library, defines ... for performing general functions
#include <string.h> //used for manipulating arrays of characters
#include <time.h> //used to measure time

int ns[] = { 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000,150000, 200000, 250000,300000, 350000,400000,450000,500000};
double avg_time;

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

    void fill_constant(int *A, int n)
    {
        for (int i=0; i<n; i++)
        {
            A[i]=0;
        }
    }

    void fill_increasing(int *A, int n) {
        for (int i=0; i<n; i++)
        {
            A[i]=i;
        }
    }

    void fill_decreasing(int *A, int n) {
       for (int i=0; i<n; i++)
        {
            A[i]=n-1-i;
        }
    }

    void fill_ashape(int *A, int n){
        for(int i=0; i<n/2; i++)
        {
            A[i]=1+2*i;
        }
        for(int i=0; i<n/2; i++)
        {
            A[n/2+i]=n-2-2*i;
        }
    }

    void fill_vshape(int *A, int n) {
        for(int i=0; i<n/2; i++)
        {
            A[i]=n-1-2*i;
        }
        for(int i=0; i<n/2; i++)
        {
            A[n/2+i]=2+2*i;
        }
    }


    void quick_sort(int *A, int left, int right) {
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


  void heapify(int *A, int n, int i) {
    // find the greatest element among root, left (l) child and right (r) child
    int greatest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && A[l] > A[greatest])
      greatest = l;

    if (r < n && A[r] > A[greatest])
      greatest = r;

    // Swap and continue heapifying if root is not the greatest element
    if (greatest != i) {
      swap(&A[i], &A[greatest]);
      heapify(A, n, greatest);
    }
  }

  void heap_sort(int *A, int n) {
    // build heap
    for (int i = n / 2 - 1; i >= 0; i--)
      heapify(A, n, i);

    // take elements 1 by 1
    for (int i = n - 1; i >= 0; i--) {
      swap(&A[0], &A[i]);
      heapify(A, i, 0);
    }
  }

    void merge (int start, int end, int A[], int temp[],int N)
    {
            int i,j,k, middle=(start+end)/2;
            i=start;
            j=middle+1;
            k=start;

            /*reading and comparing values of the elements from two previously sorted subarrays placed in the range of some part of temp array
            and putting them in their right places (with respect to each other) in A  */
            while(i<=middle && j<=end)
                {
                    if(temp[i]<temp[j])
                    {A[k]=temp[i]; i++;}
                    else
                    {A[k]=temp[j]; j++;}
                    k++;
                }
            if(i<middle){while(i<=middle) {A[k]=temp[i]; i++; k++;}}
            else{while(j<=end) {A[k]=temp[j]; j++;k++;}}
    }

    void mergesort_all (int left, int right, int A[], int temp[], int n)
    {
        int middle;
        if(left<right)
        {
            //divide an array into two equinumerous subarrays and perform margesort on them
            middle=(left+right)/2;
            mergesort_all(left,middle,A, temp, n);
            mergesort_all(middle+1,right,A, temp, n);

            //merging two previously sorted arrays
            merge (left,right,A,temp, n);
        }
    }

    void merge_sort(int *A, int n)
    {
        int *temp[n];
        for(int i=0;i<n;i++) {temp[i]=&A[i];} //creating a supplementary array needed to perform mergesort
        mergesort_all (0, n-1, A, *temp, n);
        free(temp);
    }


void (*fill_functions[])(int *, int) = { fill_random, fill_constant, fill_increasing, fill_decreasing, fill_ashape, fill_vshape };
void (*sort_functions[])(int *, int) = { quick_sort_all, heap_sort, merge_sort};
char *fill_names[] = { "Random", "Constant", "Increasing", "Decreasing","A-shape", "V-Shape" };
char *sort_names[] = {"QuickSort", "HeapSort", "MergeSort" };

int main() {

    FILE *file =fopen("results.txt", "w");

    for (unsigned int i = 0; i < 3 ; i++) {
            void (*sort)(int *, int) = sort_functions[i];

            for (unsigned int j = 0; j < 6 ; j++) {
                void (*fill)(int *, int) = fill_functions[j];

                for (unsigned int k = 0; k < 18; k++) {
                    int n = ns[k];
                    avg_time=0.0;

                    //running 10 times for each number of elements to take average
                    for (int run=0; run<10; run++){

                        int *A = calloc(n, sizeof(*A));
                        /*allocating a block of memory for an array of n elements, each of them 4 bytes long*/
                        fill(A, n);
                        clock_t begin = clock();
                        /*number of clock ticks passed since the program was launched*/
                        sort(A, n);
                        clock_t end = clock(); // -||-
                        avg_time += (double)(end - begin) / (double) CLOCKS_PER_SEC; /*the difference between begin and end divided
                        by the number of clock ticks per second gives the actual time spent on sorting an array which is added to the avg_time*/
                        free(A); //releasing previously allocated blocks of memory
                    }

                    avg_time/=10; //taking the average time of 10 runs
                    printf("%-20s %-11s %-10d %g\n", sort_names[i], fill_names[j], n, avg_time);
                    fprintf(file, "%s;%s;%d;%g\n", sort_names[i], fill_names[j], n, avg_time);

                }
            }
        }
    fclose(file);
    return 0;
}
