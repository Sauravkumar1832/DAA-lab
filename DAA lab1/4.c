#include <stdio.h>
#include <stdlib.h>

long long moves = 0;

void towerOfHanoi(int n, char source, char auxiliary, char destination)
{
    if (n == 1)
    {
        printf("Move disk 1 from %c to %c\n",
               source, destination);

        moves++;
        return;
    }

    towerOfHanoi(n - 1,
                 source,
                 destination,
                 auxiliary);

    printf("Move disk %d from %c to %c\n",
           n, source, destination);

    moves++;

    towerOfHanoi(n - 1,
                 auxiliary,
                 source,
                 destination);
}

long long countMoves(int n)
{
    if (n == 1)
        return 1;

    return 2 * countMoves(n - 1) + 1;
}

int main()
{
    int n;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Number of disks must be positive.\n");
        return 1;
    }

    printf("\nTower of Hanoi Steps:\n\n");

    moves = 0;

    towerOfHanoi(n, 'A', 'B', 'C');

    printf("\nTotal number of moves = %lld\n", moves);

    FILE *data = fopen("hanoi.dat", "w");

    if (data == NULL)
    {
        printf("Error creating hanoi.dat\n");
        return 1;
    }

    fprintf(data, "# n Actual_Moves Theoretical_Moves\n");

    for (int i = 1; i <= 20; i++)
    {
        long long actual = countMoves(i);
        long long theoretical = (1LL << i) - 1;

        fprintf(data,
                "%d %lld %lld\n",
                i,
                actual,
                theoretical);
    }

    fclose(data);

    FILE *gp = fopen("hanoi.gnu", "w");

    if (gp == NULL)
    {
        printf("Error creating hanoi.gnu\n");
        return 1;
    }

    fprintf(gp,
        "set terminal wxt size 900,600\n"
        "set title 'Tower of Hanoi - Number of Moves'\n"
        "set xlabel 'Number of Disks (n)'\n"
        "set ylabel 'Number of Moves'\n"
        "set grid\n"
        "set key left top\n"
        "plot "
        "'hanoi.dat' using 1:2 with linespoints lw 2 pt 7 "
        "title 'Actual Moves', "
        "'hanoi.dat' using 1:3 with linespoints lw 2 pt 5 "
        "title 'Theoretical Moves (2^n - 1)'\n"
        "pause -1\n"
    );

    fclose(gp);

    printf("\nData saved to hanoi.dat\n");
    printf("Gnuplot script saved to hanoi.gnu\n");
    printf("Opening Gnuplot...\n");

    system("gnuplot hanoi.gnu");

    return 0;
}
