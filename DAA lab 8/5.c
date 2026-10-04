#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *A = (int *)malloc(n * sizeof(int));
    int *dp = (int *)malloc(n * sizeof(int));
    int *parent = (int *)malloc(n * sizeof(int));

    if (A == NULL || dp == NULL || parent == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    /*
        dp[i] = maximum sum of an increasing
                subsequence ending at i

        parent[i] = previous index in that subsequence
    */

    for (int i = 0; i < n; i++) {
        dp[i] = A[i];
        parent[i] = -1;
    }

    // Calculate DP values
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {

            if (A[j] < A[i] &&
                dp[j] + A[i] > dp[i]) {

                dp[i] = dp[j] + A[i];
                parent[i] = j;
            }
        }
    }

    // Find maximum sum
    int maxSum = dp[0];
    int maxIndex = 0;

    for (int i = 1; i < n; i++) {
        if (dp[i] > maxSum) {
            maxSum = dp[i];
            maxIndex = i;
        }
    }

    // Reconstruct the subsequence
    int *sequence = (int *)malloc(n * sizeof(int));
    int size = 0;

    int current = maxIndex;

    while (current != -1) {
        sequence[size++] = A[current];
        current = parent[current];
    }

    printf("\nMaximum Sum = %d\n", maxSum);

    printf("Maximum Sum Increasing Subsequence: ");

    for (int i = size - 1; i >= 0; i--) {
        printf("%d ", sequence[i]);
    }

    printf("\n");

    free(A);
    free(dp);
    free(parent);
    free(sequence);

    return 0;
}