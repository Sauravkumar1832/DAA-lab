#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char operation[50];
} Operation;

int min3(int a, int b, int c) {
    int min = a;

    if (b < min)
        min = b;

    if (c < min)
        min = c;

    return min;
}

int main() {
    char A[MAX], B[MAX];

    printf("Enter first string: ");
    scanf("%99s", A);

    printf("Enter second string: ");
    scanf("%99s", B);

    int m = strlen(A);
    int n = strlen(B);

    // DP table
    int **dp = (int **)malloc((m + 1) * sizeof(int *));

    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    // Base cases
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;
    }

    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;
    }

    // Fill DP table
    for (int i = 1; i <= m; i++) {

        for (int j = 1; j <= n; j++) {

            if (A[i - 1] == B[j - 1]) {

                // Characters are equal
                dp[i][j] = dp[i - 1][j - 1];

            } else {

                int insertion = dp[i][j - 1];
                int deletion = dp[i - 1][j];
                int substitution = dp[i - 1][j - 1];

                dp[i][j] = 1 + min3(
                    insertion,
                    deletion,
                    substitution
                );
            }
        }
    }

    printf("\nMinimum Edit Distance = %d\n", dp[m][n]);

    /*
        Maximum number of operations is m + n.
        We store traceback operations here.
    */
    Operation *trace =
        (Operation *)malloc((m + n + 1) * sizeof(Operation));

    int count = 0;

    int i = m;
    int j = n;

    // Traceback
    while (i > 0 || j > 0) {

        // Match
        if (i > 0 && j > 0 &&
            A[i - 1] == B[j - 1] &&
            dp[i][j] == dp[i - 1][j - 1]) {

            sprintf(trace[count].operation,
                    "MATCH      : '%c'",
                    A[i - 1]);

            count++;

            i--;
            j--;
        }

        // Substitution
        else if (i > 0 && j > 0 &&
                 dp[i][j] == dp[i - 1][j - 1] + 1) {

            sprintf(trace[count].operation,
                    "SUBSTITUTE : '%c' -> '%c'",
                    A[i - 1],
                    B[j - 1]);

            count++;

            i--;
            j--;
        }

        // Deletion
        else if (i > 0 &&
                 dp[i][j] == dp[i - 1][j] + 1) {

            sprintf(trace[count].operation,
                    "DELETE     : '%c'",
                    A[i - 1]);

            count++;

            i--;
        }

        // Insertion
        else if (j > 0 &&
                 dp[i][j] == dp[i][j - 1] + 1) {

            sprintf(trace[count].operation,
                    "INSERT     : '%c'",
                    B[j - 1]);

            count++;

            j--;
        }
    }

    // Print traceback in correct order
    printf("\nTraceback:\n");

    for (int k = count - 1; k >= 0; k--) {
        printf("%s\n", trace[k].operation);
    }

    // Print DP table
    printf("\nDP Table:\n\n");

    printf("    ");

    for (int j = 0; j <= n; j++) {
        if (j == 0)
            printf("  0");
        else
            printf("  %c", B[j - 1]);
    }

    printf("\n");

    for (int i = 0; i <= m; i++) {

        if (i == 0)
            printf("0   ");
        else
            printf("%c   ", A[i - 1]);

        for (int j = 0; j <= n; j++) {
            printf("%2d ", dp[i][j]);
        }

        printf("\n");
    }

    // Free memory
    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }

    free(dp);
    free(trace);

    return 0;
}