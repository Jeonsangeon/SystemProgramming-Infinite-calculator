#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct Node{
    char data;
    struct Node* next;
}node;

void insert_node(node* head, const int index, const char data);
void delete_node(node* head, const int index);
int search(node* head, const int val);
int get_data(node* head, const int index);
int size(node* head);
void print_ll(node* head);
int store(node *head);

void push(char x);
char pop();
int priority(char x);

char exp_[100000];
int exp_int[100000];
char num[10000][10000];
int brak,need;
int top;
char stack[1000];