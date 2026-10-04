#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *A = (int *)malloc(n * sizeof(int));
    int *dp = (int *)malloc(n * sizeof(int));

    if (A == NULL || dp == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the elements:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    // Every element itself forms an LIS of length 1
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }

    // Calculate LIS ending at every index
    for (int i = 1; i < n; i++) {

        for (int j = 0; j < i; j++) {

            if (A[j] < A[i]) {

                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                }
            }
        }
    }

    // Find the maximum value in dp[]
    int lis = dp[0];

    for (int i = 1; i < n; i++) {
        if (dp[i] > lis) {
            lis = dp[i];
        }
    }

    printf("\nLength of Longest Increasing Subsequence = %d\n", lis);

    free(A);
    free(dp);

    return 0;
}