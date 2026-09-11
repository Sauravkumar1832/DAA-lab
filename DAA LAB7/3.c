#include <stdio.h>

long long dp[100];
int bestK[100];
long long count = 0;

long long power2(int n)
{
    long long p = 1;
    for (int i = 0; i < n; i++)
        p = p * 2;
    return p;
}

void hanoi3(int n, int start, char source, char destination, char auxiliary)
{
    if (n == 0)
        return;

    hanoi3(n - 1, start, source, auxiliary, destination);

    printf("Move disk %d from %c to %c\n",
           start + n - 1, source, destination);

    count++;

    hanoi3(n - 1, start, auxiliary, destination, source);
}

void hanoi4(int n, int start, char source, char destination, char peg1, char peg2)
{
    if (n == 0)
        return;

    if (n == 1)
    {
        printf("Move disk %d from %c to %c\n",
               start, source, destination);
        count++;
        return;
    }

    int k = bestK[n];

    hanoi4(k, start, source, peg1, destination, peg2);

    hanoi3(n - k, start + k, source, destination, peg2);

    hanoi4(k, start, peg1, destination, source, peg2);
}

int main()
{
    int n;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    dp[0] = 0;
    dp[1] = 1;
    bestK[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        dp[i] = power2(i) - 1;
        bestK[i] = i - 1;

        for (int k = 1; k < i; k++)
        {
            long long moves;

            moves = 2 * dp[k] + power2(i - k) - 1;

            if (moves < dp[i])
            {
                dp[i] = moves;
                bestK[i] = k;
            }
        }
    }

    printf("\nMinimum number of moves = %lld\n", dp[n]);
    printf("Best k = %d\n", bestK[n]);

    printf("\nSequence of moves:\n");

    count = 0;

    hanoi4(n, 1, 'A', 'D', 'B', 'C');

    printf("\nTotal moves performed = %lld\n", count);

    if (count == dp[n])
        printf("Solution verified successfully.\n");
    else
        printf("Solution is incorrect.\n");

    return 0;
}