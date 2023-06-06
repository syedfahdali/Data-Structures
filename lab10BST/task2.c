#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode; 
}

struct Node *insert(struct Node *root, int data)
{
    if (root == NULL)
    {
        return createNode(data);
    }
    if (data < root->data)
    {
        root->left = insert(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = insert(root->right, data);
    }
    return root;
}

struct Node *findMinimum(struct Node *root)
{
    if (root->left == NULL)
    {
        return root;
    }
    return findMinimum(root->left);
}

struct Node *findMaximum(struct Node *root)
{
    if (root->right == NULL)
    {
        return root;
    }
    return findMaximum(root->right);
}

struct Node *deleteElement(struct Node *root, int data)
{
    if (root == NULL)
    {
        return root;
    }
    if (data < root->data)
    {
        root->left = deleteElement(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = deleteElement(root->right, data);
    }
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            root = NULL;
        }
        else if (root->left == NULL)
        {
            struct Node *temp = root;
            root = root->right;
            free(temp);
        }
        else if (root->right == NULL)
        {
            struct Node *temp = root;
            root = root->left;
            free(temp);
        }
        else
        {
            struct Node *minRight = findMinimum(root->right);
            root->data = minRight->data;
            root->right = deleteElement(root->right, minRight->data);
        }
    }
    return root;
}

void postOrderTraversal(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    printf("%d ", root->data);
}

void preOrderTraversal(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }
    printf("%d ", root->data);
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

void inOrderTraversal(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }
    inOrderTraversal(root->left);
    printf("%d ", root->data);
    inOrderTraversal(root->right);
}

int calculateHeight(struct Node *root)
{
    if (root == NULL)
    {
        return -1;
    }
    int leftHeight = calculateHeight(root->left);
    int rightHeight = calculateHeight(root->right);
    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

int main()
{
    struct Node *root = NULL;

    // Creation and Insertion
    root = insert(root, 50);
    root = insert(root, 60);
    root = insert(root, 80);
    root = insert(root, 90);
    root = insert(root, 70);
    root = insert(root, 120);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 10);
    // Find minimum and maximum
    struct Node *minimumNode = findMinimum(root);
    struct Node *maximumNode = findMaximum(root);
    printf("Minimum value: %d\n", minimumNode->data);
    printf("Maximum value: %d\n", maximumNode->data);

    // Delete Element
    root = deleteElement(root, 30);

    // Post order traversal
    printf("Post order traversal: ");
    postOrderTraversal(root);
    printf("\n");

    // Pre order traversal
    printf("Pre order traversal: ");
    preOrderTraversal(root);
    printf("\n");

    // In order traversal
    printf("In order traversal: ");
    inOrderTraversal(root);
    printf("\n");

    // Height of the tree
    int height = calculateHeight(root);
    printf("Height of the tree: %d\n", height);

    return 0;
}