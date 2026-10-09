
#include <stdio.h>
#include <string.h>

#define MAX 100005
#define CHARSET 256

typedef struct {
    unsigned char ch;
    int freq;
} Node;

typedef struct {
    Node data[CHARSET + 1];
    int size;
} MaxHeap;

typedef struct {
    Node node;
    long long release;
} Cooldown;

char s[MAX], result[MAX];
int freq[CHARSET];
MaxHeap h;
Cooldown q[MAX];

void insert(Node x) {
    int i = ++h.size;

    while (i > 1 && h.data[i / 2].freq < x.freq) {
        h.data[i] = h.data[i / 2];
        i /= 2;
    }

    h.data[i] = x;
}

Node removeMax() {
    Node ans = h.data[1];
    Node last = h.data[h.size--];
    int i = 1, child;

    while (2 * i <= h.size) {
        child = 2 * i;

        if (child < h.size &&
            h.data[child + 1].freq > h.data[child].freq) {
            child++;
        }

        if (last.freq >= h.data[child].freq)
            break;

        h.data[i] = h.data[child];
        i = child;
    }

    if (h.size > 0)
        h.data[i] = last;

    return ans;
}

int main() {
    int K, n, i, len = 0;
    int front = 0, rear = 0;

    printf("Enter string: ");

    if (scanf("%100000s", s) != 1)
        return 1;

    printf("Enter K: ");

    if (scanf("%d", &K) != 1 || K < 1) {
        printf("Invalid K\n");
        return 1;
    }

    n = (int)strlen(s);

    if (K == 1) {
        printf("Reorganised string = %s\n", s);
        return 0;
    }

    for (i = 0; i < n; i++)
        freq[(unsigned char)s[i]]++;

    h.size = 0;

    for (i = 0; i < CHARSET; i++) {
        if (freq[i] > 0) {
            Node x;
            x.ch = (unsigned char)i;
            x.freq = freq[i];
            insert(x);
        }
    }

    for (i = 0; i < n; i++) {
        while (front < rear && q[front].release <= i) {
            insert(q[front].node);
            front++;
        }

        if (h.size == 0) {
            printf("Reorganised string = empty string\n");
            return 0;
        }

        Node x = removeMax();

        result[len++] = (char)x.ch;
        x.freq--;

        if (x.freq > 0) {
            q[rear].node = x;
            q[rear].release = (long long)i + K;
            rear++;
        }
    }

    result[len] = '\0';

    printf("Reorganised string = %s\n", result);

    return 0;
}
