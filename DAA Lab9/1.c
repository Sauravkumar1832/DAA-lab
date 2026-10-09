#include <stdio.h>

int main() {
    int n, i, j;
    float W, total = 0, time = 0;

    printf("Enter number of items and capacity: ");
    scanf("%d %f", &n, &W);

    float w[n], v[n], lambda[n], used[n];

    for (i = 0; i < n; i++) {
        printf("Enter weight, value and deterioration rate: ");
        scanf("%f %f %f", &w[i], &v[i], &lambda[i]);
        used[i] = 0;
    }

    while (W > 0) {
        int best = -1;
        float bestDensity = 0;

        for (i = 0; i < n; i++) {
            if (!used[i]) {
                float density = v[i] / w[i] - lambda[i] * time;

                if (density > bestDensity) {
                    bestDensity = density;
                    best = i;
                }
            }
        }

        if (best == -1)
            break;

        float take = (w[best] < W) ? w[best] : W;
        total += take * bestDensity;
        W -= take;
        used[best] = 1;
        time++;
    }

    printf("Maximum greedy value = %.2f\n", total);
    return 0;
}