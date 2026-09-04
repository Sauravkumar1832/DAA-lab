#include <stdio.h>

// Swap two numbers
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition the array
int partition(int a[], int low, int high)
{
    int pivot = a[high];
    int i = low - 1;
    int j;

    for (j = low; j < high; j++)
    {
        if (a[j] < pivot)
        {
            i++;
            swap(&a[i], &a[j]);
        }
    }

    swap(&a[i + 1], &a[high]);

    return i + 1;
}

// Find kth smallest element
int quickSelect(int a[], int low, int high, int k)
{
    int pos;

    if (low == high)
        return a[low];

    pos = partition(a, low, high);

    if (k == pos)
        return a[pos];

    if (k < pos)
        return quickSelect(a, low, pos - 1, k);

    return quickSelect(a, pos + 1, high, k);
}

int main()
{
    int a[100], n, i;
    int m1, m2;
    float median;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    if (n % 2 != 0)
    {
        // k is zero-based
        median = quickSelect(a, 0, n - 1, n / 2);
    }
    else
    {
        m1 = quickSelect(a, 0, n - 1, n / 2 - 1);
        m2 = quickSelect(a, 0, n - 1, n / 2);

        median = (m1 + m2) / 2.0;
    }

    printf("Median = %.2f\n", median);

    return 0;
}