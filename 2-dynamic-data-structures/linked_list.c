#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define REPETITIONS 10

int ns[] = {100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000, 60000, 70000};


struct Node {
    int id;
    struct Node *next;
};

typedef struct TStudent {
    int index;
    char first_name[12];
    char last_name[12];
} Student;


/// LINKED LIST FUNCTIONS

void printList(struct Node* n) {
    while (n != NULL) {
        printf("%d\n", n->id);
        n = n->next;
    }
}


void sortedInsert(struct Node** head_ref, struct Node* new_node) {
    struct Node* current;
    /* Special case for the head end */
    if (*head_ref == NULL || (*head_ref)->id >= new_node->id) {
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else {
        /* Locate the node before the point of insertion */
        current = *head_ref;
        while (current->next != NULL && current->next->id < new_node->id) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

bool searchList(struct Node** head, int x){
    struct Node* current = *head;  // Initialize current
    while (current != NULL){
        if (current->id == x)
            return true;
        if (current->id > x)
            return false;
        current = current->next;
    }
    return false;
}

void deleteNode(struct Node** head_ref, int key){
    // Store head node
    struct Node *temp = *head_ref, *prev;

    // If head node itself holds the key to be deleted
    if (temp != NULL && temp->id == key) {
        *head_ref = temp->next; // Changed head
        free(temp); // free old head
        return;
    }

    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (temp != NULL && temp->id != key) {
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in linked list
    if (temp == NULL)
        return;

    // Unlink the node from linked list
    prev->next = temp->next;

    free(temp); // Free memory
}

/// DATA FUNCTIONS

void printstudents(Student students[], int n){
    for(int i = 0; i < n; i++)
        printf("%d %s %s\n", students[i].index, students[i].first_name, students[i].last_name);
}

void deletedata(Student students[], int key, int n){
    for(int i = 0; i < n; i++) {
        if(key == students[i].index) {
            students[i].index = 0;
            strcpy(students[i].first_name, "deleted");
            strcpy(students[i].last_name, "deleted");
        }
    }
}

void searchdata(Student students[], int key, int n){
    for(int i = 0; i < n; i++)
        if(key == students[i].index)
            printf("found student: %d %s %s\n", students[i].index, students[i].first_name, students[i].last_name);
}


void shuffle(Student students[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % i;
        Student temp = students[i];
        students[i] = students[j];
        students[j] = temp;
    }
}

int main(){

    FILE *fp = fopen("list_output_bigdata.txt", "w");
    printf("%-10s %-12s %-12s %-12s\n", "n", "insert", "search", "delete");
    fprintf(fp, "%-10s %-12s %-12s %-12s\n", "n", "insert", "search", "delete");

    for (unsigned int j = 0; j < sizeof(ns) / sizeof(*ns); j++){
        int n = ns[j];
        clock_t insertion_time_total = 0;
        clock_t search_time_total = 0;
        clock_t deletion_time_total = 0;

        char str[20];
        snprintf(str, 20, "students%d.txt", n);

        for (int k = 0; k < REPETITIONS; k++){
            FILE *f = fopen(str, "r");
            if(!f) {
                perror("File opening failed");
                return EXIT_FAILURE;
            }

            int index;
            char fname[12];
            char lname[12];
            Student students[n];

            //read data into structure of students
            for(int i = 0; i < n; i ++) {
                fscanf(f, "%d %s %s", &index, fname, lname);
                students[i].index = index;
                strcpy(students[i].first_name, fname);
                strcpy(students[i].last_name, lname);
            }

            // create a new list
            struct Node* head = NULL;//(struct Node*)malloc(sizeof(struct Node));

            // insert elements in the correct order
            clock_t insertion_time = clock();
            for (int l = 0; l < n; l++) {
                struct Node *x = calloc(sizeof(*x), 1);
                x->id = students[l].index;
                sortedInsert(&head, x);
            }
            insertion_time_total += clock() - insertion_time;

            // reorder array elements before searching
            shuffle(students, n);

            // search for every element in the order present in array `A`
            clock_t search_time = clock();
            for (int l = 0; l < n; l++)
                searchList(&head, students[l].index);

            search_time_total += clock() - search_time;

            // reorder array elements before deleting
            shuffle(students, n);

            // delete every element in the order present in array `A`
            clock_t deletion_time = clock();
            for (int l = 0; l < n; l++)
                deleteNode(&head, students[l].index);

            deletion_time_total += clock() - deletion_time;

            assert(head == NULL);  // after all deletions, the list's head is NULL

            fclose(f);
        }

        printf("%-10d %-12f %-12f %-12f\n", n,
        (double)insertion_time_total / CLOCKS_PER_SEC / REPETITIONS,
        (double)search_time_total / CLOCKS_PER_SEC / REPETITIONS,
        (double)deletion_time_total / CLOCKS_PER_SEC / REPETITIONS);

        fprintf(fp, "%-10d %-12f %-12f %-12f\n", n,
        (double)insertion_time_total / CLOCKS_PER_SEC / REPETITIONS,
        (double)search_time_total / CLOCKS_PER_SEC / REPETITIONS,
        (double)deletion_time_total / CLOCKS_PER_SEC / REPETITIONS);
    }


    return 0;
}
