#include <stdio.h>

void reverse(int p[], int i, int j)
{
    int temp;

    while (i < j)
    {
        temp = p[i];
        p[i] = p[j];
        p[j] = temp;

        i++;
        j--;
    }
}

int main()
{
    int p[100];
    int n, i, j, position;

    printf("Enter n: ");
    scanf("%d", &n);

    printf("Enter permutation:\n");

    for (i = 0; i < n; i++)
        scanf("%d", &p[i]);

    for (i = 0; i < n - 1; i++)
    {
        /* Find the position of i+1 */
        position = i;

        for (j = i; j < n; j++)
        {
            if (p[j] == i + 1)
            {
                position = j;
                break;
            }
        }

        /* Reverse to put i+1 at position i */
        if (position != i)
            reverse(p, i, position);
    }

    printf("Sorted permutation:\n");

    for (i = 0; i < n; i++)
        printf("%d ", p[i]);

    printf("\n");

    return 0;
}