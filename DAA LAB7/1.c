#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int row;
    int col;
} Point;

int main()
{
    int n;
    printf("Enter number of rows: ");
    scanf("%d", &n);

    int total = n * (n + 1) / 2;

    int k = (n + 2) / 3;
    int rowShift = k - 1;
    int colShift = -((n - k + 1) / 2);

    int size = 3 * n + 10;
    int offset = n + 2;

    char *original = calloc(size * size, sizeof(char));
    char *target = calloc(size * size, sizeof(char));

    Point *from = malloc(total * sizeof(Point));
    Point *to = malloc(total * sizeof(Point));

    int fromCount = 0;
    int toCount = 0;

    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c <= r; c++)
        {
            int index = (r + offset) * size + (c + offset);
            original[index] = 1;
        }
    }

    for (int r = 0; r < n; r++)
    {
        for (int c = r; c < n; c++)
        {
            int nr = r + rowShift;
            int nc = c + colShift;

            int index = (nr + offset) * size + (nc + offset);
            target[index] = 1;
        }
    }

    for (int r = -n; r <= 2 * n; r++)
    {
        for (int c = -n; c <= n; c++)
        {
            int index = (r + offset) * size + (c + offset);

            if (original[index] && !target[index])
            {
                from[fromCount].row = r;
                from[fromCount].col = c;
                fromCount++;
            }

            if (!original[index] && target[index])
            {
                to[toCount].row = r;
                to[toCount].col = c;
                toCount++;
            }
        }
    }

    printf("\nTotal coins = %d\n", total);
    printf("Base row selected = %d\n", k);
    printf("Minimum moves = %d\n", fromCount);

    printf("\nMoves:\n");

    for (int i = 0; i < fromCount; i++)
    {
        printf("Move coin from (%d,%d) to (%d,%d)\n",
               from[i].row, from[i].col,
               to[i].row, to[i].col);
    }

    int formulaMoves = n * (n + 1) / 6;

    printf("\nFormula result = %d\n", formulaMoves);

    if (fromCount == formulaMoves)
        printf("Minimum solution verified.\n");
    else
        printf("Verification failed.\n");

    free(original);
    free(target);
    free(from);
    free(to);

    return 0;
}