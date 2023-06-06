#include <stdio.h>
#include <stdlib.h>
#define SIZE 10
struct Node
{
    int key;
    int value;
    struct Node *next;
};
struct Node *table[SIZE];
int hashfunction(int key)
{
    return key %SIZE;
}
void insert(int key, int value)
{
    int index=hashfunction(key);
    struct Node *newNode=(struct Node *)malloc(sizeof(struct Node));
    newNode->key=key;
    newNode->value=value;
    newNode->next=NULL;
    if(table[index]==NULL){
        table[index]=newNode;
    }
    else{
        struct Node *curr=table[index];
        while(curr->next != NULL){
            curr= curr->next;
        }
        curr->next= newNode;
    }
}
void delete(int key){
    int index = hashfunction(key);

    struct Node *curr=table[index];
    struct Node *prev = NULL;

    while( curr != NULL && curr->key != key){
        prev = curr;
        curr = curr->next;
    }
    if(curr == NULL){
        return; 
    }
    if(prev == NULL){
        table[index]= curr->next;
    }
    else{
        prev->next = curr->next;
    }
    free(curr);
}
int search(int key){
    
}

int main()
{

    return 0;
}