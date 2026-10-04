#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define INF DBL_MAX

void printOptimalBST(int **root, int i, int j, int parent, char side) {
    if (i > j) {
        printf("Dummy key d%d is the %s child of key k%d\n",
               i - 1,
               side == 'L' ? "left" : "right",
               parent);
        return;
    }

    int r = root[i][j];

    if (parent == -1) {
        printf("Root = k%d\n", r);
    } else {
        printf("k%d is the %s child of k%d\n",
               r,
               side == 'L' ? "left" : "right",
               parent);
    }

    printOptimalBST(root, i, r - 1, r, 'L');
    printOptimalBST(root, r + 1, j, r, 'R');
}

int main() {
    int n;

    printf("Enter number of keys: ");
    scanf("%d", &n);

    double *p = (double *)malloc((n + 1) * sizeof(double));
    double *q = (double *)malloc((n + 1) * sizeof(double));

    double **e = (double **)malloc((n + 2) * sizeof(double *));
    double **w = (double **)malloc((n + 2) * sizeof(double *));
    int **root = (int **)malloc((n + 2) * sizeof(int *));

    if (p == NULL || q == NULL || e == NULL ||
        w == NULL || root == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i <= n + 1; i++) {
        e[i] = (double *)malloc((n + 2) * sizeof(double));
        w[i] = (double *)malloc((n + 2) * sizeof(double));
        root[i] = (int *)malloc((n + 2) * sizeof(int));
    }

    printf("\nEnter successful search probabilities p1 to p%d:\n", n);

    for (int i = 1; i <= n; i++) {
        printf("p[%d] = ", i);
        scanf("%lf", &p[i]);
    }

    printf("\nEnter unsuccessful search probabilities q0 to q%d:\n", n);

    for (int i = 0; i <= n; i++) {
        printf("q[%d] = ", i);
        scanf("%lf", &q[i]);
    }

    /*
     * Base cases:
     * Empty subtree between keys i-1 and i.
     */
    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    /*
     * Dynamic Programming
     *
     * l = length of subtree
     */
    for (int l = 1; l <= n; l++) {

        for (int i = 1; i <= n - l + 1; i++) {

            int j = i + l - 1;

            e[i][j] = INF;

            /*
             * Calculate total probability.
             */
            w[i][j] = w[i][j - 1] + p[j] + q[j];

            /*
             * Try every key as root.
             */
            for (int r = i; r <= j; r++) {

                double cost =
                    e[i][r - 1]
                    + e[r + 1][j]
                    + w[i][j];

                if (cost < e[i][j]) {
                    e[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("\n========================================\n");
    printf("        OPTIMAL BST RESULT\n");
    printf("========================================\n");

    printf("\nMinimum Expected Search Cost = %.4lf\n",
           e[1][n]);

    printf("\nOptimal Binary Search Tree:\n");

    printOptimalBST(root, 1, n, -1, ' ');

    /*
     * Display DP cost table.
     */
    printf("\nDP Cost Table:\n");

    for (int i = 1; i <= n; i++) {

        for (int j = i; j <= n; j++) {
            printf("e[%d][%d] = %.4lf\n",
                   i, j, e[i][j]);
        }
    }

    /*
     * Free memory.
     */
    for (int i = 0; i <= n + 1; i++) {
        free(e[i]);
        free(w[i]);
        free(root[i]);
    }

    free(e);
    free(w);
    free(root);
    free(p);
    free(q);

    return 0;
}