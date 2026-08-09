#include <stdio.h>

#define MAX 100

// Binary Search
int search(int a[], int n, int key)
{
    int low = 0, high = n - 1;

    while(low <= high)
    {
        int mid = (low + high) / 2;

        if(a[mid] == key)
            return mid;
        else if(a[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

// Insert while maintaining sorted order
void insert(int a[], int *n, int value)
{
    int i = *n - 1;

    while(i >= 0 && a[i] > value)
    {
        a[i + 1] = a[i];
        i--;
    }

    a[i + 1] = value;
    (*n)++;
}

// Delete an element
void deleteElement(int a[], int *n, int key)
{
    int pos = search(a, *n, key);

    if(pos == -1)
    {
        printf("Element not found\n");
        return;
    }

    for(int i = pos; i < *n - 1; i++)
    {
        a[i] = a[i + 1];
    }

    (*n)--;
}

// Minimum
int minimum(int a[])
{
    return a[0];
}

// Maximum
int maximum(int a[], int n)
{
    return a[n - 1];
}

// Predecessor
int predecessor(int a[], int n, int key)
{
    int pos = search(a, n, key);

    if(pos <= 0)
        return -1;

    return a[pos - 1];
}

// Successor
int successor(int a[], int n, int key)
{
    int pos = search(a, n, key);

    if(pos == -1 || pos == n - 1)
        return -1;

    return a[pos + 1];
}

// Display array
void display(int a[], int n)
{
    for(int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
}

int main()
{
    int a[MAX] = {10, 20, 30, 40, 50};
    int n = 5;
    int key, value, pos;

    printf("Initial sorted array: ");
    display(a, n);

    // Search
    printf("\nEnter key to search: ");
    scanf("%d", &key);

    pos = search(a, n, key);

    if(pos != -1)
        printf("Element found at position %d\n", pos);
    else
        printf("Element not found\n");

    // Insert
    printf("\nEnter value to insert: ");
    scanf("%d", &value);

    insert(a, &n, value);

    printf("After insertion: ");
    display(a, n);

    // Delete
    printf("\nEnter value to delete: ");
    scanf("%d", &key);

    deleteElement(a, &n, key);

    printf("After deletion: ");
    display(a, n);

    // Minimum and Maximum
    printf("\nMinimum = %d\n", minimum(a));
    printf("Maximum = %d\n", maximum(a, n));

    // Predecessor
    printf("\nEnter key for predecessor: ");
    scanf("%d", &key);

    value = predecessor(a, n, key);

    if(value != -1)
        printf("Predecessor = %d\n", value);
    else
        printf("Predecessor does not exist\n");

    // Successor
    printf("\nEnter key for successor: ");
    scanf("%d", &key);

    value = successor(a, n, key);

    if(value != -1)
        printf("Successor = %d\n", value);
    else
        printf("Successor does not exist\n");

    return 0;
}