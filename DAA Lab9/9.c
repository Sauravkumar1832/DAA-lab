
#include <stdio.h>
#include <limits.h>

#define MAX 105

int main() {
    int n, i, j, k, len;
    long long w[MAX], prefix[MAX];
    long long dp[MAX][MAX];

    printf("Enter number of weights: ");
    scanf("%d", &n);

    if (n < 1 || n >= MAX) {
        printf("Invalid number of weights\n");
        return 1;
    }

    printf("Enter the weights in order:\n");

    prefix[0] = 0;

    for (i = 1; i <= n; i++) {
        scanf("%lld", &w[i]);

        if (w[i] < 0) {
            printf("Weights must be nonnegative\n");
            return 1;
        }

        prefix[i] = prefix[i - 1] + w[i];
        dp[i][i] = 0;
    }

    for (len = 2; len <= n; len++) {
        for (i = 1; i + len - 1 <= n; i++) {
            j = i + len - 1;
            dp[i][j] = LLONG_MAX / 2;

            long long sum = prefix[j] - prefix[i - 1];

            for (k = i; k < j; k++) {
                long long cost = dp[i][k] + dp[k + 1][j] + sum;

                if (cost < dp[i][j])
                    dp[i][j] = cost;
            }
        }
    }

    printf("Minimum weighted path length = %lld\n", dp[1][n]);

    return 0;
}
