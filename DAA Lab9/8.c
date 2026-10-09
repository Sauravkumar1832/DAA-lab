#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start, end;
} Meeting;

int cmpStart(const void *a, const void *b) {
    Meeting *x = (Meeting *)a;
    Meeting *y = (Meeting *)b;
    return (x->start > y->start) - (x->start < y->start);
}

int cmpInt(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

int main() {
    int n, i, j;
    int rooms = 0, maxRooms = 0;

    printf("Enter number of meetings: ");
    scanf("%d", &n);

    Meeting *m = malloc(n * sizeof(Meeting));
    int *ends = malloc(n * sizeof(int));

    if (m == NULL || ends == NULL) {
        printf("Memory allocation failed\n");
        free(m);
        free(ends);
        return 1;
    }

    printf("Enter start and end times:\n");

    for (i = 0; i < n; i++) {
        scanf("%d %d", &m[i].start, &m[i].end);
        ends[i] = m[i].end;
    }

    qsort(m, n, sizeof(Meeting), cmpStart);
    qsort(ends, n, sizeof(int), cmpInt);

    j = 0;

    for (i = 0; i < n; i++) {
        if (m[i].start < ends[j]) {
            rooms++;
            if (rooms > maxRooms)
                maxRooms = rooms;
        } else {
            j++;
        }
    }

    printf("Minimum meeting rooms = %d\n", maxRooms);

    free(m);
    free(ends);
    return 0;
}