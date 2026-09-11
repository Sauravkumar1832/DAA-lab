#include <stdio.h>
#include <stdlib.h>

void shoot(int shot, int possible[], int n)
{
    int next[1000] = {0};
    int i;

    /* Target at the shot position is hit */
    possible[shot] = 0;

    /* Target moves to an adjacent position */
    for (i = 1; i <= n; i++)
    {
        if (possible[i])
        {
            if (i > 1)
                next[i - 1] = 1;

            if (i < n)
                next[i + 1] = 1;
        }
    }

    for (i = 1; i <= n; i++)
        possible[i] = next[i];
}

int main()
{
    int n;
    int *possible;
    int i;
    int valid = 1;
    int shotCount = 0;

    printf("Enter number of hiding spots: ");
    scanf("%d", &n);

    if (n <= 1)
    {
        printf("Number of hiding spots must be greater than 1.\n");
        return 0;
    }

    possible = calloc(n + 1, sizeof(int));

    /* Initially target can be in any spot */
    for (i = 1; i <= n; i++)
        possible[i] = 1;

    printf("\nShooting sequence:\n");

    /* First go from left to right */
    if (n == 2)
    {
        printf("1 ");
        shotCount++;
        shoot(1, possible, n);

        /* Movement after the first shot */
        printf("1 ");
        shotCount++;
        possible[1] = 0;
    }
    else
    {
        for (i = 2; i <= n - 1; i++)
        {
            printf("%d ", i);
            shotCount++;

            /* Shoot and then target moves */
            if (i != n - 1)
                shoot(i, possible, n);
            else
                possible[i] = 0;
        }

        /* Now go from right to left */
        for (i = n - 1; i >= 2; i--)
        {
            printf("%d ", i);
            shotCount++;

            if (i != 2)
                shoot(i, possible, n);
            else
                possible[i] = 0;
        }
    }

    /* Check whether any target position is still possible */
    for (i = 1; i <= n; i++)
    {
        if (possible[i] == 1)
        {
            valid = 0;
            break;
        }
    }

    printf("\n\nTotal shots = %d\n", shotCount);

    if (valid)
        printf("The strategy guarantees hitting the target.\n");
    else
        printf("The strategy does not guarantee hitting the target.\n");

    free(possible);

    return 0;
}