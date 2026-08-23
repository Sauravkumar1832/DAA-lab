#include <stdio.h>
#include <stdlib.h>

struct Interval
{
    int start;
    int end;
};

int compare(const void *a, const void *b)
{
    struct Interval *x = (struct Interval *)a;
    struct Interval *y = (struct Interval *)b;

    return x->start - y->start;
}

int main()
{
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    struct Interval arr[n];

    printf("Enter intervals:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &arr[i].start, &arr[i].end);
    }

    // Sort according to starting time
    qsort(arr, n, sizeof(struct Interval), compare);

    printf("\nMerged intervals:\n");

    int start = arr[0].start;
    int end = arr[0].end;

    for (int i = 1; i < n; i++)
    {
        // If intervals overlap
        if (arr[i].start <= end)
        {
            if (arr[i].end > end)
                end = arr[i].end;
        }
        else
        {
            // Print previous interval
            printf("(%d, %d) ", start, end);

            start = arr[i].start;
            end = arr[i].end;
        }
    }

    // Print last interval
    printf("(%d, %d)\n", start, end);

    return 0;
}