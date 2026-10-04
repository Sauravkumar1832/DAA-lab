#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n;

    printf("Enter rod length: ");
    scanf("%d", &n);

    int *price = (int *)malloc((n + 1) * sizeof(int));
    int *revenue = (int *)malloc((n + 1) * sizeof(int));
    int *firstCut = (int *)malloc((n + 1) * sizeof(int));

    if (price == NULL || revenue == NULL || firstCut == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter prices for pieces of length 1 to %d:\n", n);

    for (int i = 1; i <= n; i++) {
        printf("Price[%d] = ", i);
        scanf("%d", &price[i]);
    }

    /* Base case */
    revenue[0] = 0;
    firstCut[0] = 0;

    /* Dynamic Programming */
    for (int j = 1; j <= n; j++) {

        revenue[j] = price[j];
        firstCut[j] = j;

        for (int i = 1; i < j; i++) {

            int currentRevenue = price[i] + revenue[j - i];

            if (currentRevenue > revenue[j]) {
                revenue[j] = currentRevenue;
                firstCut[j] = i;
            }
        }
    }

    printf("\nMaximum Revenue = %d\n", revenue[n]);

    printf("Optimal decomposition: ");

    int remaining = n;

    while (remaining > 0) {
        int piece = firstCut[remaining];

        printf("%d", piece);

        remaining -= piece;

        if (remaining > 0) {
            printf(" + ");
        }
    }

    printf("\n");

    printf("\nDP Table:\n");
    printf("Length\tRevenue\tFirst Cut\n");

    for (int i = 0; i <= n; i++) {
        printf("%d\t%d\t%d\n",
               i,
               revenue[i],
               firstCut[i]);
    }

    free(price);
    free(revenue);
    free(firstCut);

    return 0;
}