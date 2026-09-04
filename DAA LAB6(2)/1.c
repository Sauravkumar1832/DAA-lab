#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* (i) Maximum */
int findMax(int a[], int n)
{
    int max = a[0];
    int i;

    for (i = 1; i < n; i++)
    {
        if (a[i] > max)
            max = a[i];
    }

    return max;
}

/* (ii) First and second largest */
void firstSecondLargest(int a[], int n)
{
    int largest, second;
    int i;

    if (a[0] > a[1])
    {
        largest = a[0];
        second = a[1];
    }
    else
    {
        largest = a[1];
        second = a[0];
    }

    for (i = 2; i < n; i++)
    {
        if (a[i] > largest)
        {
            second = largest;
            largest = a[i];
        }
        else if (a[i] > second)
        {
            second = a[i];
        }
    }

    printf("Largest = %d\n", largest);
    printf("Second Largest = %d\n", second);
}

/* (iii) Mean */
float findMean(int a[], int n)
{
    int i;
    float sum = 0;

    for (i = 0; i < n; i++)
        sum = sum + a[i];

    return sum / n;
}

/* Used for median */
void sort(int a[], int n)
{
    int i, j;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
                swap(&a[j], &a[j + 1]);
        }
    }
}

/* (iv) Median */
float findMedian(int a[], int n)
{
    int b[100];
    int i;

    for (i = 0; i < n; i++)
        b[i] = a[i];

    sort(b, n);

    if (n % 2 == 1)
        return b[n / 2];
    else
        return (b[n / 2 - 1] + b[n / 2]) / 2.0;
}

/* (v) Standard deviation */
float findStandardDeviation(int a[], int n)
{
    float mean = findMean(a, n);
    float sum = 0;
    float variance;
    int i;

    for (i = 0; i < n; i++)
    {
        sum = sum + (a[i] - mean) * (a[i] - mean);
    }

    variance = sum / n;

    return sqrt(variance);
}

/* (vi) Mode */
int findMode(int a[], int n)
{
    int maxCount = 0;
    int mode = a[0];
    int count;
    int i, j;

    for (i = 0; i < n; i++)
    {
        count = 0;

        for (j = 0; j < n; j++)
        {
            if (a[j] == a[i])
                count++;
        }

        if (count > maxCount)
        {
            maxCount = count;
            mode = a[i];
        }
    }

    return mode;
}

/* (vii) Display duplicates */
void findDuplicates(int a[], int n)
{
    int i, j, k;
    int alreadyPrinted;

    printf("Duplicates: ");

    for (i = 0; i < n; i++)
    {
        alreadyPrinted = 0;

        for (k = 0; k < i; k++)
        {
            if (a[k] == a[i])
            {
                alreadyPrinted = 1;
                break;
            }
        }

        if (alreadyPrinted)
            continue;

        for (j = i + 1; j < n; j++)
        {
            if (a[i] == a[j])
            {
                printf("%d ", a[i]);
                break;
            }
        }
    }

    printf("\n");
}

/* (viii) Reverse array */
void reverse(int a[], int n)
{
    int i;

    for (i = 0; i < n / 2; i++)
        swap(&a[i], &a[n - 1 - i]);
}

/* (ix) Partition around random pivot */
int partition(int a[], int n)
{
    int pivotIndex;
    int pivot;
    int i, j;

    pivotIndex = rand() % n;
    pivot = a[pivotIndex];

    swap(&a[pivotIndex], &a[n - 1]);

    i = 0;

    for (j = 0; j < n - 1; j++)
    {
        if (a[j] < pivot)
        {
            swap(&a[i], &a[j]);
            i++;
        }
    }

    swap(&a[i], &a[n - 1]);

    return i;
}

int main()
{
    int a[100];
    int n, i;
    int position;

    srand(time(NULL));

    printf("Enter n: ");
    scanf("%d", &n);

    printf("Enter elements:\n");

    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("\nMaximum = %d\n", findMax(a, n));

    firstSecondLargest(a, n);

    printf("Mean = %.2f\n", findMean(a, n));

    printf("Median = %.2f\n", findMedian(a, n));

    printf("Standard Deviation = %.2f\n",
           findStandardDeviation(a, n));

    printf("Mode = %d\n", findMode(a, n));

    findDuplicates(a, n);

    reverse(a, n);

    printf("Reversed array: ");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");

    /* Partition */
    position = partition(a, n);

    printf("After partition: ");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\nPivot position = %d\n", position);

    return 0;
}