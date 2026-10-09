
#include <stdio.h>
#include <string.h>

#define N 100
#define L 1000

int overlap(char a[], char b[]) {
    int x = strlen(a);
    int y = strlen(b);
    int k, i;

    for (k = (x < y ? x : y); k > 0; k--) {
        for (i = 0; i < k; i++) {
            if (a[x - k + i] != b[i])
                break;
        }

        if (i == k)
            return k;
    }

    return 0;
}

int main() {
    int n, i, j, best, ov;
    int bestI, bestJ;
    char s[N][L];
    char merged[2 * L];

    printf("Enter number of strings: ");
    scanf("%d", &n);

    if (n < 1 || n > N) {
        printf("Invalid number of strings\n");
        return 1;
    }

    printf("Enter the strings:\n");

    for (i = 0; i < n; i++) {
        scanf("%999s", s[i]);
    }

    while (n > 1) {
        best = -1;
        bestI = 0;
        bestJ = 1;

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (i == j)
                    continue;

                ov = overlap(s[i], s[j]);

                if (ov > best) {
                    best = ov;
                    bestI = i;
                    bestJ = j;
                }
            }
        }

        strcpy(merged, s[bestI]);
        strcat(merged, s[bestJ] + best);

        strcpy(s[bestI], merged);

        for (i = bestJ; i < n - 1; i++) {
            strcpy(s[i], s[i + 1]);
        }

        n--;
    }

    printf("Superstring = %s\n", s[0]);
    printf("Length = %lu\n", (unsigned long)strlen(s[0]));

    return 0;
}

