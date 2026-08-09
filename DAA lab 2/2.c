#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Merge two sorted parts
void merge(int a[], int low, int mid, int high)
{
    int i = low;
    int j = mid + 1;
    int k = 0;

    int size = high - low + 1;
    int *temp = (int *)malloc(size * sizeof(int));

    while(i <= mid && j <= high)
    {
        if(a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while(i <= mid)
        temp[k++] = a[i++];

    while(j <= high)
        temp[k++] = a[j++];

    for(i = low, k = 0; i <= high; i++, k++)
        a[i] = temp[k];

    free(temp);
}

// Normal Merge Sort
void mergeSort(int a[], int low, int high)
{
    if(low < high)
    {
        int mid = (low + high) / 2;

        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);

        merge(a, low, mid, high);
    }
}

// Merge three sorted parts
void mergeThree(int a[], int low, int mid1, int mid2, int high)
{
    int i = low;
    int j = mid1 + 1;
    int k = mid2 + 1;
    int p = 0;

    int size = high - low + 1;

    int *temp = (int *)malloc(size * sizeof(int));

    while(i <= mid1 || j <= mid2 || k <= high)
    {
        int value;
        int choice = 0;

        if(i <= mid1)
        {
            value = a[i];
            choice = 1;
        }

        if(j <= mid2 && (choice == 0 || a[j] < value))
        {
            value = a[j];
            choice = 2;
        }

        if(k <= high && (choice == 0 || a[k] < value))
        {
            value = a[k];
            choice = 3;
        }

        temp[p++] = value;

        if(choice == 1)
            i++;
        else if(choice == 2)
            j++;
        else
            k++;
    }

    for(i = low, p = 0; i <= high; i++, p++)
        a[i] = temp[p];

    free(temp);
}

// Modified Three-Way Merge Sort
void threeWayMergeSort(int a[], int low, int high)
{
    if(low < high)
    {
        int n = high - low + 1;

        int mid1 = low + n / 3 - 1;
        int mid2 = low + (2 * n) / 3 - 1;

        // For small arrays, use normal merge sort
        if(n < 3)
        {
            mergeSort(a, low, high);
            return;
        }

        threeWayMergeSort(a, low, mid1);
        threeWayMergeSort(a, mid1 + 1, mid2);
        threeWayMergeSort(a, mid2 + 1, high);

        mergeThree(a, low, mid1, mid2, high);
    }
}

// Generate random numbers
void generateArray(int a[], int n)
{
    for(int i = 0; i < n; i++)
        a[i] = rand();
}

int main()
{
    int sizes[] = {1000, 5000, 10000, 20000, 50000};
    int count = 5;

    srand(time(NULL));

    printf("n\tNormal Merge Sort\t3-Way Merge Sort\n");
    printf("-----------------------------------------------\n");

    for(int s = 0; s < count; s++)
    {
        int n = sizes[s];

        int *a = (int *)malloc(n * sizeof(int));
        int *b = (int *)malloc(n * sizeof(int));

        // Generate same input for both algorithms
        generateArray(a, n);

        for(int i = 0; i < n; i++)
            b[i] = a[i];

        clock_t start, end;

        // Normal Merge Sort
        start = clock();

        mergeSort(a, 0, n - 1);

        end = clock();

        double normalTime =
            (double)(end - start) / CLOCKS_PER_SEC;

        // Three-Way Merge Sort
        start = clock();

        threeWayMergeSort(b, 0, n - 1);

        end = clock();

        double threeWayTime =
            (double)(end - start) / CLOCKS_PER_SEC;

        printf("%d\t%lf\t\t%lf\n",
               n, normalTime, threeWayTime);

        free(a);
        free(b);
    }

    return 0;
}