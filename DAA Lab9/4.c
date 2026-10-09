#include <stdio.h>

int heap[100005], size = 0;

void insert(int x) {
    int i = ++size;

    while (i > 1 && heap[i / 2] > x) {
        heap[i] = heap[i / 2];
        i /= 2;
    }

    heap[i] = x;
}

int removeMin() {
    int ans = heap[1];
    int last = heap[size--];
    int i = 1, child;

    while (2 * i <= size) {
        child = 2 * i;

        if (child < size && heap[child + 1] < heap[child])
            child++;

        if (last <= heap[child])
            break;

        heap[i] = heap[child];
        i = child;
    }

    if (size > 0)
        heap[i] = last;

    return ans;
}

int main() {
    int n, i, a, b;
    long long cost = 0;

    printf("Enter number of sticks: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        int length;
        scanf("%d", &length);
        insert(length);
    }

    while (size > 1) {
        a = removeMin();
        b = removeMin();

        cost += (long long)a + b;
        insert(a + b);
    }

    printf("Minimum total cost = %lld\n", cost);
    return 0;
}