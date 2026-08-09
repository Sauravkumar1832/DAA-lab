#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int key;
    struct Node *prev;
    struct Node *next;
};

// Search
struct Node* search(struct Node *head, int key)
{
    struct Node *temp = head;

    while(temp != NULL)
    {
        if(temp->key == key)
            return temp;

        temp = temp->next;
    }

    return NULL;
}

// Insert at beginning
void insert(struct Node **head, int key)
{
    struct Node *newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->key = key;
    newNode->prev = NULL;
    newNode->next = *head;

    if(*head != NULL)
        (*head)->prev = newNode;

    *head = newNode;
}

// Delete
void deleteNode(struct Node **head, struct Node *node)
{
    if(node == NULL)
        return;

    if(node->prev != NULL)
        node->prev->next = node->next;
    else
        *head = node->next;

    if(node->next != NULL)
        node->next->prev = node->prev;

    free(node);
}

// Minimum
struct Node* minimum(struct Node *head)
{
    struct Node *temp = head;
    struct Node *minNode = head;

    while(temp != NULL)
    {
        if(temp->key < minNode->key)
            minNode = temp;

        temp = temp->next;
    }

    return minNode;
}

// Maximum
struct Node* maximum(struct Node *head)
{
    struct Node *temp = head;
    struct Node *maxNode = head;

    while(temp != NULL)
    {
        if(temp->key > maxNode->key)
            maxNode = temp;

        temp = temp->next;
    }

    return maxNode;
}

// Predecessor
struct Node* predecessor(struct Node *head, int key)
{
    struct Node *temp = head;
    struct Node *pred = NULL;

    while(temp != NULL)
    {
        if(temp->key < key)
        {
            if(pred == NULL || temp->key > pred->key)
                pred = temp;
        }

        temp = temp->next;
    }

    return pred;
}

// Successor
struct Node* successor(struct Node *head, int key)
{
    struct Node *temp = head;
    struct Node *succ = NULL;

    while(temp != NULL)
    {
        if(temp->key > key)
        {
            if(succ == NULL || temp->key < succ->key)
                succ = temp;
        }

        temp = temp->next;
    }

    return succ;
}

// Display
void display(struct Node *head)
{
    struct Node *temp = head;

    while(temp != NULL)
    {
        printf("%d ", temp->key);
        temp = temp->next;
    }

    printf("\n");
}

int main()
{
    struct Node *head = NULL;
    struct Node *result;
    int key;

    // Insert elements
    insert(&head, 30);
    insert(&head, 10);
    insert(&head, 50);
    insert(&head, 20);
    insert(&head, 40);

    printf("Doubly Linked List: ");
    display(head);

    // Search
    printf("\nEnter key to search: ");
    scanf("%d", &key);

    result = search(head, key);

    if(result != NULL)
        printf("Element found: %d\n", result->key);
    else
        printf("Element not found\n");

    // Delete
    printf("\nEnter key to delete: ");
    scanf("%d", &key);

    result = search(head, key);

    if(result != NULL)
    {
        deleteNode(&head, result);
        printf("After deletion: ");
        display(head);
    }
    else
    {
        printf("Element not found\n");
    }

    // Minimum
    result = minimum(head);
    printf("\nMinimum = %d\n", result->key);

    // Maximum
    result = maximum(head);
    printf("Maximum = %d\n", result->key);

    // Predecessor
    printf("\nEnter key for predecessor: ");
    scanf("%d", &key);

    result = predecessor(head, key);

    if(result != NULL)
        printf("Predecessor = %d\n", result->key);
    else
        printf("Predecessor does not exist\n");

    // Successor
    printf("\nEnter key for successor: ");
    scanf("%d", &key);

    result = successor(head, key);

    if(result != NULL)
        printf("Successor = %d\n", result->key);
    else
        printf("Successor does not exist\n");

    return 0;
}