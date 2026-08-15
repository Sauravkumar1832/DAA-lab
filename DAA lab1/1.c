#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct Function
{
    char name[30];
    double value;
};

int main()
{
    double n = 1000.0;

    struct Function f[] =
    {
        {"nlog2(n)", n * log2(n)},
        {"12sqrt(n)", 12 * sqrt(n)},
        {"1/n", 1 / n},
        {"n^(log2n)", pow(n, log2(n))},
        {"100n^2+6n", 100 * n * n + 6 * n},
        {"n^0.51", pow(n, 0.51)},
        {"n^2-324", n * n - 324},
        {"50n^0.5", 50 * pow(n, 0.5)},
        {"2n^3", 2 * n * n * n},
        {"3^n", pow(3, n)},
        {"2^32*n", pow(2, 32) * n},
        {"log2(n)", log2(n)}
    };

    int size = sizeof(f) / sizeof(f[0]);

    /* Bubble Sort */

    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (f[j].value > f[j + 1].value)
            {
                struct Function temp = f[j];
                f[j] = f[j + 1];
                f[j + 1] = temp;
            }
        }
    }

    printf("Increasing order of growth (for n = %.0lf)\n\n", n);

    for (int i = 0; i < size; i++)
    {
        printf("%2d. %-15s = %.3e\n",
               i + 1,
               f[i].name,
               f[i].value);
    }

    /* Create data file */

    FILE *data = fopen("growth.dat", "w");

    if (data == NULL)
    {
        printf("Error creating growth.dat\n");
        return 1;
    }

    fprintf(data,
        "# n  1/n  log2n  12sqrt  50sqrt  n0.51 "
        "2^32n  nlogn  n2-324  100n2+6n "
        "2n3  nlog2n  3n\n"
    );

    for (int x = 20; x <= 600; x++)
    {
        double n = x;

        double f1 = 1.0 / n;
        double f2 = log2(n);
        double f3 = 12.0 * sqrt(n);
        double f4 = 50.0 * sqrt(n);
        double f5 = pow(n, 0.51);
        double f6 = pow(2.0, 32) * n;
        double f7 = n * log2(n);
        double f8 = n * n - 324;
        double f9 = 100.0 * n * n + 6.0 * n;
        double f10 = 2.0 * n * n * n;
        double f11 = pow(n, log2(n));

        /*
           3^n becomes extremely large.
           We only calculate it up to n = 100.
        */

        double f12;

        if (n <= 100)
            f12 = pow(3.0, n);
        else
            f12 = 0.0;

        fprintf(data,
            "%d %.10e %.10e %.10e %.10e %.10e "
            "%.10e %.10e %.10e %.10e %.10e %.10e %.10e\n",
            x,
            f1,
            f2,
            f3,
            f4,
            f5,
            f6,
            f7,
            f8,
            f9,
            f10,
            f11,
            f12
        );
    }

    fclose(data);

    /* Create Gnuplot script */

    FILE *gp = fopen("growth.gnu", "w");

    if (gp == NULL)
    {
        printf("Error creating growth.gnu\n");
        return 1;
    }

    /* First Graph */

    fprintf(gp,
        "set terminal wxt 1 size 900,600\n"
        "set title 'Order of Growth - Slow and Medium Functions'\n"
        "set xlabel 'n'\n"
        "set ylabel 'Function Value'\n"
        "set logscale y\n"
        "set grid\n"
        "set key outside right\n"
        "set xrange [20:600]\n"
        "plot "
        "'growth.dat' using 1:2 with lines lw 2 title '1/n', "
        "'growth.dat' using 1:3 with lines lw 2 title 'log2(n)', "
        "'growth.dat' using 1:4 with lines lw 2 title '12sqrt(n)', "
        "'growth.dat' using 1:5 with lines lw 2 title '50sqrt(n)', "
        "'growth.dat' using 1:6 with lines lw 2 title 'n^0.51', "
        "'growth.dat' using 1:7 with lines lw 2 title '2^32*n', "
        "'growth.dat' using 1:8 with lines lw 2 title 'nlog2(n)'\n"
    );

    /* Second Graph */

    fprintf(gp,
        "set terminal wxt 2 size 900,600\n"
        "set title 'Order of Growth - Fast Functions'\n"
        "set xlabel 'n'\n"
        "set ylabel 'Function Value'\n"
        "set logscale y\n"
        "set grid\n"
        "set key outside right\n"
        "set xrange [20:100]\n"
        "plot "
        "'growth.dat' using 1:9 with lines lw 2 title 'n^2-324', "
        "'growth.dat' using 1:10 with lines lw 2 title '100n^2+6n', "
        "'growth.dat' using 1:11 with lines lw 2 title '2n^3', "
        "'growth.dat' using 1:12 with lines lw 2 title 'n^(log2n)', "
        "'growth.dat' using 1:13 with lines lw 2 title '3^n'\n"
    );

    /* Keep both graphs open */

    fprintf(gp, "pause -1\n");

    fclose(gp);

    printf("\nData file created: growth.dat\n");
    printf("Gnuplot script created: growth.gnu\n");
    printf("Opening Gnuplot...\n");

    system("gnuplot growth.gnu");

    return 0;
}
