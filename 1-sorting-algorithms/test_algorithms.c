#include <assert.h> //header file, preprocessor macro
#include <limits.h> //defines values properties for types
#include <stdbool.h> //macros for boolean data type
#include <stdio.h> //basic c library, defines size_t, FILE, fpos_t ...
#include <stdlib.h> //basic c library, defines ... for performing general functions
#include <string.h> //used for manipulating arrays of characters
#include <time.h> //used to measure time

//int ns[] = { 1000, 5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
int ns[] = {100};

void fill_random(int *A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % n;
    }
}

    void fill_constant(int *A, int n){
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
            A[n/2+i]=2*i;
        }
    }


//used in BS and HS and...
void swap(int *x, int *y){
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void bubbleSort(int *A, int n){
   for (int i = 0; i < n-1; i++)
       for (int j = 0; j < n-i-1; j++)
           if (A[j] > A[j+1])
              swap(&A[j], &A[j+1]);
}


void heapify(int *A, int n, int i) {
    // find greatest among root, left (l) child and right (r) child
    int greatest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && A[l] > A[greatest])
      greatest = l;

    if (r < n && A[r] > A[greatest])
      greatest = r;

    // Swap and continue heapifying if root is not greatest
    if (greatest != i) {
      swap(&A[i], &A[greatest]);
      heapify(A, n, greatest);
    }
  }

  void heapSort(int *A, int n) {
    // build heap
    for (int i = n / 2 - 1; i >= 0; i--)
      heapify(A, n, i);

    // take elements 1 by 1
    for (int i = n - 1; i >= 0; i--) {
      swap(&A[0], &A[i]);
      heapify(A, i, 0);
    }
  }

void countingSort(int *A, int n){
    int result[n], i;
    int range = n;
    int count[range];

    // setting all elements of arrays to 0
    for (i = 0; i < n ; i++) {
        result[i] = 0;
        count[i] = 0;
    }

    // count occurences of each number
    for (i = 0; i < n ; i++)
        count[A[i]]++;

    // change count[i] to positions of numbers
    for (i = 1; i < range; i++)
        count[i] += count[i - 1];

    // output array
    for (i = 0; i < n; i++) {
        result[count[A[i]] - 1] = A[i];
        count[A[i]]--;
    }

    // copy results
    for (i = 0; i < n; i++)
        A[i] = result[i];
}


void shellSort(int *A, int n) {
  // rearrange elements at n/2, n/4,  ... intervals
  for (int interval = n / 2; interval > 0; interval /= 2) {
    for (int i = interval; i < n; i += 1) {
      int tmp = A[i];
      int j;
      // insertion sort for every interval
      for (j = i; j >= interval && A[j - interval] > tmp; j -= interval) {
        A[j] = A[j - interval];
      }
      A[j] = tmp;
    }
  }
}

void selectSort(int *A, int n) {
    int k;
    for (int i = 0; i < n - 1; i++) {
        k = i;
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[k])
                k = j;
        }
        swap(&A[k], &A[i]);
    }
}

void insertSort(int *A, int n) {
    int check, j;
    for (int i = 1; i < n; i++){
        check = A[i];
        j = i - 1;
        /*Move elements of A[0..i-1], that are
          greater than checkto 1 position ahead*/
        while (j >= 0 && A[j] > check){
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = check;
    }
}

void quick_sort(int *A, int left, int right) {
    int i = left;
    int j = right;
    int x = A[(left+right) / 2 ]; //pivot value equals to the value of the element laying in the middle of an array
    do
    {
        //searching for the element that is respectively bigger/smaller than x
        while( A[i] < x ) i++;
        while( A[j] > x ) j--;

        //swapping previously selected elements if possible (no point in swapping if i>j)
        if( i <= j )
        {
            swap(&A[i], &A[j] );
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

void merge (int start, int end, int A[], int temp[],int N){
    int i, j, k, middle = (start + end) / 2;
    i = start;
    j = middle + 1;
    k = start;

    /*reading and comparing values of the elements from two previously sorted subarrays placed in the range of some part of temp array
    and putting them in their right places (with respect to each other) in A  */
    while(i <= middle && j <= end) {
        if(temp[i] < temp[j]) {
            A[k] = temp[i];
            i++;
        }
        else {
            A[k] = temp[j];
            j++;
        }
        k++;
    }
    if(i < middle) {
        while(i <= middle) {
            A[k] = temp[i];
            i++;
            k++;
        }
    }
    else {
        while(j <= end) {
            A[k] = temp[j];
            j++;
            k++;
        }
    }
}

void mergesort_all (int left, int right, int A[], int temp[], int n){
    int middle;
    if(left < right) {
        //divide an array into two equinumerous subarrays and perform margesort on them
        middle = (left + right) / 2;
        mergesort_all(left, middle, A, temp, n);
        mergesort_all(middle+1, right, A, temp, n);

        //merging two previously sorted arrays
        merge(left, right, A, temp, n);
    }
}

void merge_sort(int *A, int n){
    int *temp[n];
    for(int i = 0; i < n; i++)
        temp[i] = &A[i]; //creating a supplementary array needed to perform mergesort
    mergesort_all (0, n-1, A, *temp, n);
    free(temp);
}
/*
void show(int *A, int n, file) {
    for(int i = 0; i < n; i++) {
        fprintf(file, "%d ", A[i]);
    }
    fprintf(file, "\n");

}*/

void (*fill_functions[])(int *, int) = { fill_random, fill_constant, fill_increasing, fill_decreasing, fill_ashape, fill_vshape };
void (*sort_functions[])(int *, int) = { quick_sort_all, heapSort, merge_sort, bubbleSort, shellSort, countingSort, insertSort, selectSort };
char *fill_names[] = { "Random", "Constant", "Increasing", "Decreasing","A-shape", "V-Shape" };
char *sort_names[] = {"QuickSort", "HeapSort", "MergeSort", "BubbleSort", "ShellSort", "CountingSort", "InsertSort", "SelectSort" };

int main() {

    FILE *file = fopen("sorts100elementsXX.txt", "w");

    //choose i according to desired algorithm

    for (unsigned int i = 0; i < 8; i++) {
            void (*sort)(int *, int) = sort_functions[i];

            for (unsigned int j = 0; j < 6; j++) {
                void (*fill)(int *, int) = fill_functions[j];


                for (unsigned int k = 0; k < 1; k++) {
                    int n = ns[k];
                    int *A = calloc(n, sizeof(*A));

                    fprintf(file, "%s %s\n", sort_names[i], fill_names[j]);

                    fill(A, n);

                    for(int i = 0; i < n; i++) {
                        fprintf(file, "%d ", A[i]);
                    }
                    fprintf(file, "\n");


                    //show(A, n, file);
                    sort(A, n);

                    fprintf(file, "%s\n", "sorted array:");

                    for(int i = 0; i < n; i++) {
                        fprintf(file, "%d ", A[i]);
                    }

                    fprintf(file, "\n");
                    fprintf(file, "\n");

                    free(A); //releasing previously allocated blocks of memory

                    //printf("%-20s %-11s %-10d\n", sort_names[i], fill_names[0], n);
                    //fprintf(file, "%s;%s;%d;%g\n", sort_names[i], fill_names[0], n, avg_time);

                    }
            }

        }
    fclose(file);
    return 0;
}
