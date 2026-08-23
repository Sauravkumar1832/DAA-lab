#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int number;
    char color;
} Item;

/* Get maximum number */
int getMax(Item a[], int n) {
    int max = a[0].number;

    for (int i = 1; i < n; i++) {
        if (a[i].number > max)
            max = a[i].number;
    }

    return max;
}

/* Stable counting sort according to one digit */
void countingSortByDigit(Item a[], int n, int exp) {
    Item *output = (Item *)malloc(n * sizeof(Item));
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(a[i].number / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        int digit = (a[i].number / exp) % 10;
        output[count[digit] - 1] = a[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++)
        a[i] = output[i];

    free(output);
}

/* Radix sort according to number */
void radixSort(Item a[], int n) {
    int max = getMax(a, n);

    for (int exp = 1; max / exp > 0; exp *= 10)
        countingSortByDigit(a, n, exp);
}

/* Give each color a priority */
int colorValue(char color) {
    if (color == 'R')
        return 0;
    if (color == 'B')
        return 1;
    return 2;       // Yellow
}

/* Stable counting sort according to color */
void sortByColor(Item a[], int n) {
    Item *output = (Item *)malloc(n * sizeof(Item));
    int count[3] = {0};

    /* Count colors */
    for (int i = 0; i < n; i++)
        count[colorValue(a[i].color)]++;

    /* Prefix sum */
    for (int i = 1; i < 3; i++)
        count[i] += count[i - 1];

    /* Stable placement */
    for (int i = n - 1; i >= 0; i--) {
        int c = colorValue(a[i].color);
        output[count[c] - 1] = a[i];
        count[c]--;
    }

    /* Copy back */
    for (int i = 0; i < n; i++)
        a[i] = output[i];

    free(output);
}

int main() {
    int n;

    printf("Enter number of items: ");
    scanf("%d", &n);

    Item *a = (Item *)malloc(n * sizeof(Item));

    printf("Enter number and color (R/B/Y):\n");

    for (int i = 0; i < n; i++) {
        scanf("%d %c", &a[i].number, &a[i].color);
    }

    /* First sort numbers */
    radixSort(a, n);

    /* Then stable sort colors */
    sortByColor(a, n);

    printf("\nSorted items:\n");

    for (int i = 0; i < n; i++) {
        printf("(%d, %c)\n", a[i].number, a[i].color);
    }

    free(a);

    return 0;
}
