#include "node.h"

int top = -1;

void insert_node(node* head, const int index, const char data) {
    int k = index;
    node* pre_node = head;
    node* insert = (node*)malloc(sizeof(node));
    insert->data = data;

    while (k-- && pre_node != NULL)
        pre_node = pre_node->next; 
    
    if (pre_node == NULL) {
        free(insert);
        return;
    } 

    insert->next = pre_node->next;
    pre_node->next = insert;
}

void delete_node(node* head, const int index) {
    int k = index;
    node* temp = head;
    node* garbage = NULL;

    while (k-- && temp != NULL)
        temp = temp->next;

    if (temp == NULL || temp->next == NULL)
        return;

    garbage = temp->next;
    temp->next = garbage->next;
    free(garbage);
}

int search(node* head, const int val) {
    if (head->next == NULL) return -1;
    
    int index = 0;
    node* temp = head->next;
    
    while (temp->data != val) {
        ++index;
        temp = temp->next;

        if (temp == NULL) return -1;
    }
    return index; // index return
}

int get_data(node* head, const int index) {
    if (head->next == NULL) return -1;
    
    int k = index;
    node* temp = head->next;
    
    while(k--) temp = temp->next;
    return temp->data; // data return
}

int size(node* head){
    node* temp = head->next;		
    int len = 0;
    while(temp != NULL) {
        ++len;
        temp = temp->next;
    }
    return len;
}

void print_ll(node* head) {
    if (head->next == NULL) return; // 다음 노드가 NULL이라면 return

    node* temp = head->next;
    while(temp != NULL) { // temp가 NULL이 아닐때 까지
    	if (temp->data>=40 && temp->data<=45 && temp->data!=40)
    		printf("\n");
        printf("%c", temp->data); // 공백으로 구분하여 출력
        if (temp->data>=40 && temp->data<=45 && temp->data!=41)
    		printf("\n");
        temp = temp->next; // 다음 노드로 이동
    }
    printf("\n"); // 개행
}

int store(node* head) {
    if (head->next == NULL) return 0; // 다음 노드가 NULL이라면 return
	int num=0,blank=0;
	need=0;
    node* temp = head->next;
    while(temp != NULL) { // temp가 NULL이 아닐때 까지
    	if (48<=temp->data && temp->data<=57 && blank==0){
    		exp_[need++]='0'+num%10;
    		num++;
    		blank=1;
		}
		else if (48<=temp->data && temp->data<=57){
//    		need++;
		}
    	else if (temp->data>=40 && temp->data<=45){
    		blank=0;
    		exp_[need++]=temp->data;
    	}
        temp = temp->next; // 다음 노드로 이동
    }
    return need;
}

void push(char x)
{
    stack[++top] = x;
}

char pop()
{
    if(top == -1)
        return -1;
    else
        return stack[top--];
}

int priority(char x)
{
    if(x == '(')
        return 0;
    if(x == '+' || x == '-')
        return 1;
    if(x == '*' || x == '/')
        return 2;
    return 0;
}