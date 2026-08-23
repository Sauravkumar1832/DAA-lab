#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int binarySearch(int arr[], int n, int x)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (arr[mid] == x)
            return 1;

        if (arr[mid] < x)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return 0;
}

int main()
{
    int n, x;

    /* --------- MAIN PROGRAM --------- */

    printf("Enter size of both sets: ");
    scanf("%d", &n);

    int S1[n], S2[n];

    printf("Enter elements of S1:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &S1[i]);

    printf("Enter elements of S2:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &S2[i]);

    printf("Enter x: ");
    scanf("%d", &x);

    /* Sort S2 */
    qsort(S2, n, sizeof(int), compare);

    /* Search for the required element */
    for (int i = 0; i < n; i++)
    {
        int required = x - S1[i];

        if (binarySearch(S2, n, required))
        {
            printf("\nPair exists: %d + %d = %d\n",
                   S1[i], required, x);

            break;
        }

        if (i == n - 1)
            printf("\nNo such pair exists.\n");
    }
    return 0;
}