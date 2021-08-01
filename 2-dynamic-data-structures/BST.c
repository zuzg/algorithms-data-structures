#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define REPETITIONS 10
int ns[] = {100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000, 13000, 14000, 15000};

typedef struct Student {
    int index;
    char first_name[12];
    char last_name[12];
} Student;

struct Node {
    int key;
    struct Node * left;
    struct Node * right;
    //int height; //potrzebne tylko do AVL
    int balance_factor;
};

///BST
struct Node * Create_Node (int data)
{
    struct Node * new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->key = data;
    new_node->left = NULL;
    new_node->right = NULL;
    //new_node->height = 1; //AVL
    return new_node;
}

bool Search_Node (struct Node * root, int key)
{
    struct Node * current = root;
    while(current != NULL && current->key != key)
    { (key < current->key) ? (current = current->left) : (current = current->right); }
    if (current == NULL) return false;
    else return true;
}

struct Node * Find_Min_Node (struct Node * root)
{
    while (root->left != NULL) root = root->left;
    return root;
}

struct Node * Insert_Node (struct Node * root, int key)
{
    if (root == NULL)
        return Create_Node(key);
    if (key < root->key)
        root->left = Insert_Node(root->left, key);
    else if (key > root->key)
        root->right = Insert_Node(root->right, key);
    return root;
}

struct Node * Delete (struct Node * root, int key)
{
    if (root == NULL) return NULL;
    else if (key < root->key) root->left = Delete(root->left, key);
    else if (key > root->key) root->right = Delete(root->right, key);
    else
    {
        //printf("\nZOSTANIE USUNETY: %d\n", temp_root->key); ///jak sie czasem pokazuja dwa/wiecej to to jest od tego (*)
        //no child
        if (root->left == NULL && root->right == NULL)
        {
            free (root);
            root = NULL;
        }
        //1 child
        else if (root->left == NULL)
        {
            struct Node * temp = root;
            root = root->right;
            free(temp);
        }
        else if (root->right == NULL)
        {
            struct Node * temp = root;
            root = root->left;
            free(temp);
        }
        //2 children
        else
        {
            struct Node * min_node = Find_Min_Node(root->right);
            root->key = min_node->key;
            root->right = Delete(root->right, min_node->key); //(*)
        }
    }
    return root;
}

///DATA
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

///MAIN
int main(){

    printf("%-10s %-12s %-12s %-12s\n", "n", "insert", "search", "delete");

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
            struct Node* root = NULL;//(struct Node*)malloc(sizeof(struct Node));

            // insert elements in the correct order
            clock_t insertion_time = clock();
            for (int l = 0; l < n; l++)
                root = Insert_Node(root, students[l].index);

            insertion_time_total += clock() - insertion_time;

            // reorder array elements before searching
            shuffle(students, n);

            // search for every element in the order present in array `A`
            clock_t search_time = clock();
            for (int l = 0; l < n; l++)
                Search_Node(root, students[l].index);

            search_time_total += clock() - search_time;

            // reorder array elements before deleting
            shuffle(students, n);

            // delete every element in the order present in array `A`
            clock_t deletion_time = clock();
            for (int l = 0; l < n; l++)
                root = Delete(root, students[l].index);

            deletion_time_total += clock() - deletion_time;

            assert(root == NULL);  // after all deletions, the list's head is NULL

            free(root);
            fclose(f);
        }

        printf("%-10d %-12f %-12f %-12f\n", n,
            (double)insertion_time_total / CLOCKS_PER_SEC / REPETITIONS,
            (double)search_time_total / CLOCKS_PER_SEC / REPETITIONS,
            (double)deletion_time_total / CLOCKS_PER_SEC / REPETITIONS);
    }

    return 0;
}
