#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char ch;
    int freq;
    struct Node *left, *right;
} Node;

Node *heap[200];
int size = 0;

Node *createNode(char ch, int freq, Node *left, Node *right) {
    Node *node = malloc(sizeof(Node));
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

int smaller(Node *a, Node *b) {
    if (a->freq != b->freq)
        return a->freq < b->freq;
    return a->ch < b->ch;
}

void insert(Node *node) {
    int i = ++size;
    while (i > 1 && smaller(node, heap[i / 2])) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = node;
}

Node *removeMin() {
    Node *ans = heap[1];
    Node *last = heap[size--];
    int i = 1, child;

    while (2 * i <= size) {
        child = 2 * i;
        if (child < size && smaller(heap[child + 1], heap[child]))
            child++;
        if (smaller(last, heap[child]))
            break;
        heap[i] = heap[child];
        i = child;
    }

    if (size > 0)
        heap[i] = last;

    return ans;
}

void printCodes(Node *root, char code[], int depth) {
    if (!root)
        return;

    if (!root->left && !root->right) {
        if (depth == 0)
            code[depth++] = '0';
        code[depth] = '\0';
        printf("%c : %s\n", root->ch, code);
        return;
    }

    code[depth] = '0';
    printCodes(root->left, code, depth + 1);

    code[depth] = '1';
    printCodes(root->right, code, depth + 1);
}

int main() {
    int n, i, freq;
    char ch, code[200];

    printf("Enter number of symbols: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter symbol and frequency: ");
        scanf(" %c %d", &ch, &freq);
        insert(createNode(ch, freq, NULL, NULL));
    }

    while (size > 1) {
        Node *a = removeMin();
        Node *b = removeMin();
        Node *parent = createNode(
            (a->ch < b->ch) ? a->ch : b->ch,
            a->freq + b->freq, a, b
        );
        insert(parent);
    }

    printf("Huffman codes:\n");
    printCodes(heap[1], code, 0);
    return 0;
}