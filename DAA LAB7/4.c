#include <stdio.h>
#include <stdlib.h>

int *moves;
long long moveCount = 0;

void solve(int n, int start)
{
    int begin;
    int len;
    int i;

    if (n == 1)
    {
        moves[moveCount++] = start;
        return;
    }

    if (n == 2)
    {
        moves[moveCount++] = start;
        moves[moveCount++] = start + 1;
        return;
    }

    begin = moveCount;

    solve(n - 2, start + 2);

    len = moveCount - begin;

    moves[moveCount++] = start;

    for (i = len - 1; i >= 0; i--)
    {
        moves[moveCount++] = moves[begin + i];
    }

    solve(n - 1, start + 1);
}

int legal(int state[], int n, int pos)
{
    int i;

    if (pos == n - 1)
        return 1;

    if (state[pos + 1] != 1)
        return 0;

    for (i = pos + 2; i < n; i++)
    {
        if (state[i] != 0)
            return 0;
    }

    return 1;
}

long long minimumMoves(int n)
{
    long long dp[100];

    dp[1] = 1;
    dp[2] = 2;

    for (int i = 3; i <= n; i++)
    {
        dp[i] = dp[i - 1] + 2 * dp[i - 2] + 1;
    }

    return dp[n];
}

int main()
{
    int n;
    int *state;
    long long expected;

    printf("Enter number of switches: ");
    scanf("%d", &n);

    if (n < 1 || n > 20)
    {
        printf("Enter n between 1 and 20.\n");
        return 0;
    }

    expected = minimumMoves(n);

    moves = malloc(expected * sizeof(int));
    state = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        state[i] = 1;

    solve(n, 0);

    printf("\nMinimum number of moves = %lld\n", expected);

    printf("\nSequence of moves:\n");

    int valid = 1;

    for (long long i = 0; i < moveCount; i++)
    {
        int pos = moves[i];

        if (!legal(state, n, pos))
        {
            printf("Illegal move at move %lld: switch %d\n",
                   i + 1, pos + 1);
            valid = 0;
            break;
        }

        state[pos] = 1 - state[pos];

        printf("Move %lld: Toggle switch %d\n",
               i + 1, pos + 1);
    }

    for (int i = 0; i < n; i++)
    {
        if (state[i] != 0)
            valid = 0;
    }

    printf("\nTotal moves generated = %lld\n", moveCount);

    if (valid && moveCount == expected)
        printf("Algorithm validated successfully.\n");
    else
        printf("Algorithm validation failed.\n");

    free(moves);
    free(state);

    return 0;
}