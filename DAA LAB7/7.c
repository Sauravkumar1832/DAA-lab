#include <stdio.h>
#include <limits.h>

int m[100][100];
int split[100][100];

void printOrder(int i, int j)
{
    if (i == j)
    {
        printf("A%d", i);
        return;
    }

    printf("(");
    printOrder(i, split[i][j]);
    printOrder(split[i][j] + 1, j);
    printf(")");
}

int main()
{
    int n;
    int p[100];
    int i, j, k, length;
    int cost;

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    printf("Enter the dimensions:\n");

    for (i = 0; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }

    for (i = 1; i <= n; i++)
    {
        m[i][i] = 0;
    }

    for (length = 2; length <= n; length++)
    {
        for (i = 1; i <= n - length + 1; i++)
        {
            j = i + length - 1;
            m[i][j] = INT_MAX;

            for (k = i; k < j; k++)
            {
                cost = m[i][k]
                     + m[k + 1][j]
                     + p[i - 1] * p[k] * p[j];

                if (cost < m[i][j])
                {
                    m[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    printf("\nMinimum number of scalar multiplications = %d\n",
           m[1][n]);

    printf("Optimal parenthesization = ");
    printOrder(1, n);
    printf("\n");

    return 0;
}