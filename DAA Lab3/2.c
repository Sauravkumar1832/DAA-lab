#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 0.000001

int weighingCount = 0;

/*
    Compare two groups of equal size.

    Returns:
       -1  -> left side is lighter
        0  -> both sides are equal
        1  -> left side is heavier
*/
int weighGroups(double coins[], int start1, int start2, int count)
{
    double left = 0.0;
    double right = 0.0;

    for (int i = 0; i < count; i++)
    {
        left += coins[start1 + i];
        right += coins[start2 + i];
    }

    weighingCount++;

    if (fabs(left - right) < EPS)
        return 0;
    else if (left < right)
        return -1;
    else
        return 1;
}

/*
    Find the lighter defective coin.

    start      = starting index of current candidate group
    n          = number of candidate coins
    goodIndex  = index of a coin that is known to be perfect
                 (-1 means no known-good coin)
    
    Returns:
       index of defective coin
       -1 if no defective coin exists
*/
int findDefective(double coins[], int start, int n, int goodIndex)
{
    /*
        One candidate coin.

        We need a known-good coin to compare it with.
    */
    if (n == 1)
    {
        if (goodIndex == -1)
            return -1;

        int result = weighGroups(coins, start, goodIndex, 1);

        if (result == -1)
            return start;      // candidate is lighter

        return -1;             // candidate is normal
    }

    /*
        Two candidates.
    */
    if (n == 2)
    {
        /*
            If there is no known-good coin, compare
            the two candidates directly.
        */
        if (goodIndex == -1)
        {
            int result = weighGroups(coins, start, start + 1, 1);

            if (result == -1)
                return start;

            if (result == 1)
                return start + 1;

            return -1;         // both are equal
        }

        /*
            If a known-good coin exists, compare each
            candidate with it.
        */
        int result = weighGroups(coins, start, goodIndex, 1);

        if (result == -1)
            return start;

        result = weighGroups(coins, start + 1, goodIndex, 1);

        if (result == -1)
            return start + 1;

        return -1;
    }

    /*
        Divide the candidates into three groups.

        s = ceil(n / 3)
    */
    int s = (n + 2) / 3;

    int groupAStart = start;
    int groupBStart = start + s;

    /*
        Number of coins in the third group.
    */
    int groupCSize = n - 2 * s;

    /*
        If C is empty, A and B contain all coins.
    */
    if (groupCSize == 0)
    {
        int result = weighGroups(coins, groupAStart,
                                 groupBStart, s);

        if (result == -1)
        {
            // A is lighter
            return findDefective(coins, groupAStart,
                                 s, groupBStart);
        }
        else if (result == 1)
        {
            // B is lighter
            return findDefective(coins, groupBStart,
                                 s, groupAStart);
        }
        else
        {
            // A and B are equal -> no defective coin
            return -1;
        }
    }

    /*
        First weighing:
             Group A  VS  Group B
    */
    int result = weighGroups(coins, groupAStart,
                             groupBStart, s);

    /*
        Case 1:
        A is lighter.
    */
    if (result == -1)
    {
        return findDefective(coins, groupAStart,
                             s, groupBStart);
    }

    /*
        Case 2:
        B is lighter.
    */
    else if (result == 1)
    {
        return findDefective(coins, groupBStart,
                             s, groupAStart);
    }

    /*
        Case 3:
        A and B are equal.

        Therefore A and B are known-good.
        The defective coin, if present, must be in C.
    */

    /*
        Compare C with known-good coins.

        C can have fewer than s coins, so we add
        good coins from A to make both sides contain
        exactly s coins.
    */

    int padding = s - groupCSize;

    double left = 0.0;
    double right = 0.0;

    /*
        Left side:
        all coins of C + some known-good coins from A
    */
    for (int i = 0; i < groupCSize; i++)
    {
        left += coins[groupBStart + s + i];
    }

    for (int i = 0; i < padding; i++)
    {
        left += coins[groupAStart + i];
    }

    /*
        Right side:
        all coins of B (known-good)
    */
    for (int i = 0; i < s; i++)
    {
        right += coins[groupBStart + i];
    }

    weighingCount++;

    /*
        C is lighter.
    */
    if (left < right - EPS)
    {
        int groupCStart = groupBStart + s;

        return findDefective(coins, groupCStart,
                             groupCSize, groupAStart);
    }

    /*
        C has normal total weight.
        Therefore no defective coin exists.
    */
    return -1;
}

int main()
{
    int n;

    printf("Enter number of coins: ");
    scanf("%d", &n);

    if (n < 2)
    {
        printf("At least 2 coins are required.\n");
        return 0;
    }

    double *coins = (double *)malloc(n * sizeof(double));

    if (coins == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("\nEnter the weight of each coin:\n");

    for (int i = 0; i < n; i++)
    {
        printf("Coin %d: ", i + 1);
        scanf("%lf", &coins[i]);
    }

    /*
        Start with no known-good coin.
    */
    int defective = findDefective(coins, 0, n, -1);

    printf("\n-----------------------------\n");

    if (defective == -1)
    {
        printf("No defective coin found.\n");
    }
    else
    {
        printf("Defective coin: Coin %d\n", defective + 1);
        printf("Weight: %.2lf\n", coins[defective]);
    }

    printf("Number of weighings: %d\n", weighingCount);

    printf("-----------------------------\n");

    free(coins);

    return 0;
}