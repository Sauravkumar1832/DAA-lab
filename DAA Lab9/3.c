#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int d, f;
} Station;

int cmp(const void *a, const void *b) {
    Station *x = (Station *)a;
    Station *y = (Station *)b;
    return (x->d > y->d) - (x->d < y->d);
}

int heap[100005], hs = 0;

void push(int x) {
    int i = ++hs;
    while (i > 1 && heap[i / 2] < x) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = x;
}

int pop() {
    int ans = heap[1], last = heap[hs--], i = 1, c;

    while (2 * i <= hs) {
        c = 2 * i;
        if (c < hs && heap[c + 1] > heap[c])
            c++;
        if (last >= heap[c])
            break;
        heap[i] = heap[c];
        i = c;
    }

    if (hs > 0)
        heap[i] = last;

    return ans;
}

int main() {
    int n, D, F, i, stops = 0;

    printf("Enter number of stations, destination and initial fuel: ");
    scanf("%d %d %d", &n, &D, &F);

    Station s[n];

    for (i = 0; i < n; i++) {
        printf("Enter station distance and fuel: ");
        scanf("%d %d", &s[i].d, &s[i].f);
    }

    qsort(s, n, sizeof(Station), cmp);

    int fuel = F, prev = 0;

    for (i = 0; i <= n; i++) {
        int next = (i == n) ? D : s[i].d;
        fuel -= next - prev;

        while (fuel < 0 && hs > 0) {
            fuel += pop();
            stops++;
        }

        if (fuel < 0) {
            printf("Destination cannot be reached\n");
            return 0;
        }

        if (i < n)
            push(s[i].f);

        prev = next;
    }

    printf("Minimum refueling stops = %d\n", stops);
    return 0;
}