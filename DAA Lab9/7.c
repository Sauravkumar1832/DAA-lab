#include <stdio.h>

#define MAX 100005

long long heap[MAX];
int size = 0;

void insert(long long x) {
    int i = ++size;

    while (i > 1 && heap[i / 2] < x) {
        heap[i] = heap[i / 2];
        i /= 2;
    }

    heap[i] = x;
}

long long removeMax() {
    long long ans = heap[1];
    long long last = heap[size--];
    int i = 1, child;

    while (2 * i <= size) {
        child = 2 * i;

        if (child < size && heap[child + 1] > heap[child])
            child++;

        if (last >= heap[child])
            break;

        heap[i] = heap[child];
        i = child;
    }

    if (size > 0)
        heap[i] = last;

    return ans;
}

int main() {
    int n, i;
    long long x, mn = 0, deviation;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%lld", &x);

        if (x % 2 != 0)
            x *= 2;

        insert(x);

        if (i == 0 || x < mn)
            mn = x;
    }

    deviation = heap[1] - mn;

    while (heap[1] % 2 == 0) {
        x = removeMax();
        x /= 2;

        if (x < mn)
            mn = x;

        insert(x);

        if (heap[1] - mn < deviation)
            deviation = heap[1] - mn;
    }

    printf("Minimum deviation = %lld\n", deviation);
    return 0;
}