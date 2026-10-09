#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i;
    long long total = 0;

    printf("Enter number of children: ");
    scanf("%d", &n);

    int *rating = malloc(n * sizeof(int));
    int *candy = malloc(n * sizeof(int));

    if (rating == NULL || candy == NULL) {
        printf("Memory allocation failed\n");
        free(rating);
        free(candy);
        return 1;
    }

    printf("Enter ratings: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &rating[i]);
        candy[i] = 1;
    }

    for (i = 1; i < n; i++) {
        if (rating[i] > rating[i - 1])
            candy[i] = candy[i - 1] + 1;
    }

    for (i = n - 2; i >= 0; i--) {
        if (rating[i] > rating[i + 1] &&
            candy[i] <= candy[i + 1]) {
            candy[i] = candy[i + 1] + 1;
        }
    }

    for (i = 0; i < n; i++)
        total += candy[i];

    printf("Minimum candies required = %lld\n", total);

    free(rating);
    free(candy);
    return 0;
} 