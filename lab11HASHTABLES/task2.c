#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

struct Node
{
    int key;
    int value;
    struct Node *next;
};

struct Node *table[SIZE]; // creates an array of size =10

// Hash function
int hashFunction(int key)
{
    return key % SIZE; // This produces an index value in the array where value of Node is assigned like 30/10=3 3 is index key
}

// Insertion
void insert(int key, int value)
{                                  // key is the position at which the value will be inserted
    int index = hashFunction(key); // This line produces an index

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node)); // memory allocation
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
      
    if (table[index] == NULL)
    {
        table[index] = newNode;
    }
    else
    {
        struct Node *curr = table[index];
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = newNode;
    }
}

// Deletion
void delete(int key)
{
    int index = hashFunction(key);

    struct Node *curr = table[index];
    struct Node *prev = NULL;

    while (curr != NULL && curr->key != key)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
    {
        return;
    }

    if (prev == NULL)
    {
        table[index] = curr->next;
    }
    else
    {
        prev->next = curr->next;
    }

    free(curr);
}

// Searching
int search(int key)
{
    int index = hashFunction(key);

    struct Node *curr = table[index];

    while (curr != NULL)
    {
        if (curr->key == key)
        {
            return curr->value;
        }
        curr = curr->next;
    }

    return -1; // Key not found
}

// Rehashing
void rehash()
{
    struct Node *newTable[SIZE * 2];
    int i;

    for (i = 0; i < SIZE * 2; i++)
    {
        newTable[i] = NULL;
    }

    for (i = 0; i < SIZE; i++)
    {
        struct Node *curr = table[i];

        while (curr != NULL)
        {
            struct Node *next = curr->next;
            int index = curr->key % (SIZE * 2);

            if (newTable[index] == NULL)
            {
                curr->next = NULL;
                newTable[index] = curr;
            }
            else
            {
                curr->next = newTable[index];
                newTable[index] = curr;
            }

            curr = next;
        }
    }

    // Copy the new table to the original table
    for (i = 0; i < SIZE * 2; i++)
    {
        table[i] = newTable[i];
    }
}

int main()
{
    int i;

    // Initialize table
    for (i = 0; i < SIZE; i++)
    {
        table[i] = NULL;
    }

    // Insertion
    insert(5, 10);
    insert(15, 20);
    insert(25, 30);
    insert(60, 30);

    // Searching
    int value = search(60);
    if (value != -1)
    {
        printf("Value found: %d\n", value);
    }
    else
    {
        printf("Value not found.\n");
    }

    // Deletion
    delete (15);

    // Rehashing
    rehash();

    return 0;
}
