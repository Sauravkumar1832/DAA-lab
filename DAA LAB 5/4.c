#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify
void heapify(int a[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[largest])
        largest = left;

    if (right < n && a[right] > a[largest])
        largest = right;

    if (largest != i)
    {
        swap(&a[i], &a[largest]);
        heapify(a, n, largest);
    }
}

// Heap Sort
void heapSort(int a[], int n)
{
    int i;

    // Build max heap
    for (i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    // Move largest element to end
    for (i = n - 1; i > 0; i--)
    {
        swap(&a[0], &a[i]);

        heapify(a, i, 0);
    }
}

int main()
{
    FILE *fp;
    int a[100], n, i;

    srand(time(NULL));

    printf("Enter number of elements: ");
    scanf("%d", &n);

    // Open file for writing
    fp = fopen("numbers.txt", "w");

    if (fp == NULL)
    {
        printf("File cannot be opened\n");
        return 1;
    }

    // Generate random numbers
    for (i = 0; i < n; i++)
    {
        a[i] = rand() % 100;
        fprintf(fp, "%d ", a[i]);
    }

    fclose(fp);

    // Open file for reading
    fp = fopen("numbers.txt", "r");

    if (fp == NULL)
    {
        printf("File cannot be opened\n");
        return 1;
    }

    for (i = 0; i < n; i++)
        fscanf(fp, "%d", &a[i]);

    fclose(fp);

    printf("\nElements before sorting:\n");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    heapSort(a, n);

    printf("\n\nElements after Heap Sort:\n");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    return 0;
}