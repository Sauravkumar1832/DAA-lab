#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int key;
    struct Node *next;
};

// Search
struct Node* search(struct Node *head, int key)
{
    struct Node *temp = head;

    while(temp != NULL && temp->key <= key)
    {
        if(temp->key == key)
            return temp;

        temp = temp->next;
    }

    return NULL;
}

// Insert in sorted order
void insert(struct Node **head, int key)
{
    struct Node *newNode;
    struct Node *temp;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->key = key;
    newNode->next = NULL;

    // Insert at beginning
    if(*head == NULL || (*head)->key >= key)
    {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    temp = *head;

    // Find correct position
    while(temp->next != NULL && temp->next->key < key)
    {
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

// Delete
void deleteNode(struct Node **head, int key)
{
    struct Node *temp = *head;
    struct Node *prev = NULL;

    while(temp != NULL && temp->key != key)
    {
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL)
    {
        printf("Element not found\n");
        return;
    }

    if(prev == NULL)
        *head = temp->next;
    else
        prev->next = temp->next;

    free(temp);
}

// Minimum
struct Node* minimum(struct Node *head)
{
    return head;
}

// Maximum
struct Node* maximum(struct Node *head)
{
    struct Node *temp = head;

    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    return temp;
}

// Predecessor
struct Node* predecessor(struct Node *head, int key)
{
    struct Node *temp = head;
    struct Node *pred = NULL;

    while(temp != NULL && temp->key < key)
    {
        pred = temp;
        temp = temp->next;
    }

    return pred;
}

// Successor
struct Node* successor(struct Node *head, int key)
{
    struct Node *temp = head;

    while(temp != NULL && temp->key <= key)
    {
        temp = temp->next;
    }

    return temp;
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

    printf("Sorted List: ");
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

    deleteNode(&head, key);

    printf("After deletion: ");
    display(head);

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