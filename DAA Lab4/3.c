#include <stdio.h>
#include <stdlib.h>

int a[100];
int n, k, T;

/* Compare function for sorting */
int compare(const void *x, const void *y)
{
    return (*(int *)x - *(int *)y);
}

/* Binary search from index start */
int binarySearch(int start, int end, int target)
{
    while (start <= end)
    {
        int mid = (start + end) / 2;

        if (a[mid] == target)
            return 1;
        else if (a[mid] < target)
            start = mid + 1;
        else
            end = mid - 1;
    }

    return 0;
}

/* Choose k-1 elements */
int findSum(int index, int count, int sum)
{
    if (count == k - 1)
    {
        int remaining = T - sum;

        /* Search only after the last selected element */
        return binarySearch(index, n - 1, remaining);
    }

    for (int i = index; i < n; i++)
    {
        if (findSum(i + 1, count + 1, sum + a[i]))
            return 1;
    }

    return 0;
}

int main()
{
    printf("Enter n: ");
    scanf("%d", &n);

    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter k: ");
    scanf("%d", &k);

    printf("Enter T: ");
    scanf("%d", &T);

    /* Sort the array */
    qsort(a, n, sizeof(int), compare);

    if (findSum(0, 0, 0))
        printf("YES, %d elements have sum %d\n", k, T);
    else
        printf("NO, such elements do not exist\n");

    return 0;
}
