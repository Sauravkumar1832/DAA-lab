#include <stdio.h>

int main()
{
    int E, F;
    int dp[101][101];

    printf("Enter number of eggs: ");
    scanf("%d", &E);

    printf("Enter number of floors: ");
    scanf("%d", &F);

    for (int e = 1; e <= E; e++)
    {
        dp[e][0] = 0;
        dp[e][1] = 1;
    }

    for (int f = 0; f <= F; f++)
    {
        dp[1][f] = f;
    }

    for (int e = 2; e <= E; e++)
    {
        for (int f = 2; f <= F; f++)
        {
            dp[e][f] = F;

            for (int x = 1; x <= f; x++)
            {
                int broken = dp[e - 1][x - 1];
                int notBroken = dp[e][f - x];

                int worst;

                if (broken > notBroken)
                    worst = broken;
                else
                    worst = notBroken;

                int attempts = 1 + worst;

                if (attempts < dp[e][f])
                    dp[e][f] = attempts;
            }
        }
    }

    printf("\nMinimum number of drops = %d\n", dp[E][F]);

    return 0;
}