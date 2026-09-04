#include <stdio.h>
#include <limits.h>

int main()
{
    int n, i, j, k, L;
    int arr[100];
    int dp[100][100];
    int cost;

    printf("Enter N: ");
    scanf("%d", &n);

    printf("Enter array elements:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // Cost of multiplying one matrix is 0
    for (i = 1; i < n; i++)
        dp[i][i] = 0;

    // L is chain length
    for (L = 2; L < n; L++)
    {
        for (i = 1; i < n - L + 1; i++)
        {
            j = i + L - 1;
            dp[i][j] = INT_MAX;

            for (k = i; k < j; k++)
            {
                cost = dp[i][k]
                     + dp[k + 1][j]
                     + arr[i - 1] * arr[k] * arr[j];

                if (cost < dp[i][j])
                    dp[i][j] = cost;
            }
        }
    }

    printf("Minimum number of scalar multiplications = %d\n",
           dp[1][n - 1]);

    return 0;
}