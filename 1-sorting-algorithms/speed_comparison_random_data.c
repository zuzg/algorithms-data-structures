#include <assert.h> //header file, preprocessor macro
#include <limits.h> //defines values properties for types
#include <stdbool.h> //macros for boolean data type
#include <stdio.h> //basic c library, defines size_t, FILE, fpos_t ...
#include <stdlib.h> //basic c library, defines ... for performing general functions
#include <string.h> //used for manipulating arrays of characters
#include <time.h> //used to measure time

int ns[] = { 1000, 5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};

void fill_random(int *A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % n;
    }
}

//used in BS and HS
void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void bubbleSort(int *A, int n) {
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

    // swap and continue heapifying if root is not greatest
    if (greatest != i) {
      swap(&A[i], &A[greatest]);
      heapify(A, n, greatest);
    }
  }

void heapSort(int *A, int n) {
    // build heap
    for (int i = n/2 - 1; i >= 0; i--)
      heapify(A, n, i);

    // take elements 1 by 1
    for (int i = n - 1; i >= 0; i--) {
      swap(&A[0], &A[i]);
      heapify(A, i, 0);
    }
  }

void countingSort(int *A, int n) {
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

void sort(int *A, int n, int x) {
    if(x == 0) {
        bubbleSort(A, n);
    }
    else if (x == 1) {
        heapSort(A, n);
    }
    else if (x == 2) {
        countingSort(A, n);
    }
    else {
        shellSort(A, n);
    }

}


char *sort_names[] = { "BubbleSort", "HeapSort", "CountingSort", "ShellSort" };

int main() {

    FILE *f = fopen("dataXXXX.txt", "w");

    for(int i = 0; i < 4; i++) {

        printf("%d\n", i);
        for(int k = 0; k < 15; k++){
            //running 10 times for each number of elements to take average
            int n;
            double seconds_sum = 0.0;
            for(int r = 0; r < 10; r++) {
                n = ns[k];
                int *A = calloc(n, sizeof(*A));
                fill_random(A, n);

                clock_t begin = clock();
                sort(A, n, i);
                clock_t end = clock();
                seconds_sum += (double)(end - begin) / (double) CLOCKS_PER_SEC;//macro - clock ticks per second

                free(A);
            }
            double average_seconds = seconds_sum / 10;
            fprintf(f, "%s %d %g\n", sort_names[i], n, average_seconds);
            printf("%s %d %g\n", sort_names[i], n, average_seconds);
        }
    }

    fclose(f);
    return 0;
}
