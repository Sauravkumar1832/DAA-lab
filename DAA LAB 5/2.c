#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

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
    int a[100], n, k, i;
    int answer;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter K: ");
    scanf("%d", &k);

    if (k < 1 || k > n)
    {
        printf("Invalid K\n");
        return 0;
    }

    // Convert Kth smallest into zero-based index
    answer = quickSelect(a, 0, n - 1, k - 1);

    printf("%dth smallest element = %d\n", k, answer);

    return 0;
}