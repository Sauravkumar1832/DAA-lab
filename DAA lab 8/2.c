#include <stdio.h>
long long countWays(int coins[], int n, int V) {
    long long dp[V + 1];

    // Base case
    dp[0] = 1;

    // Initialize remaining values
    for (int i = 1; i <= V; i++) {
        dp[i] = 0;
    }

    // Process each coin
    for (int i = 0; i < n; i++) {
        int coin = coins[i];

        // Amounts must be processed from coin to V
        for (int j = coin; j <= V; j++) {
            dp[j] = dp[j] + dp[j - coin];
        }
    }

    return dp[V];
}

int main() {
    int n, V;

    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    int coins[n];

    printf("Enter coin denominations:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &coins[i]);
    }

    printf("Enter target amount: ");
    scanf("%d", &V);

    long long result = countWays(coins, n, V);

    printf("Total number of combinations = %lld\n", result);

    return 0;
}