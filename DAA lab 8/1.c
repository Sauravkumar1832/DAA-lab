#include <stdio.h>
#include <limits.h>
int min_(int a, int b){
    if(a<=b) return a;
    else return b;
}
int minCoins(int coins[], int n, int V) {
    int dp[V + 1];

    // Base case
    dp[0] = 0;

    // Initialize all other values as infinity
    for (int i = 1; i <= V; i++) {
        dp[i] = INT_MAX;
    }

    // Calculate minimum coins for every amount
    for (int i = 1; i <= V; i++) {
        for (int j = 0; j < n; j++) {
            // If coin can be used
            if (coins[j] <= i && dp[i - coins[j]] != INT_MAX) {
                dp[i] = min_(dp[i],dp[i-coins[j]]+1);
            }
        }
    }

    // If V cannot be formed
    if (dp[V] == INT_MAX)
        return -1;

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

    int result = minCoins(coins, n, V);

    if (result == -1)
        printf("Amount cannot be made using given coins.\n");
    else
        printf("Minimum number of coins required = %d\n", result);

    return 0;
}