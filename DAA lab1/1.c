#include<stdio.h>
#include<math.h>
#include<string.h>

struct Function{
    char name[30];
    double value;
};

int main(){
    double n=1000.0;

    //creating the array

    struct Function f[]=
    {
        {"nlog2(n)", n*log2(n)},
        {"12sqrt(n)", 12*sqrt(n)},
        {"1/n",1/n},
        {"n^(log2n)",pow(n,log2(n))},
        {"100n^2+6n",100*n*n+6*n},
        {"n^0.51",pow(n,0.51)},
        {"n^2-324",n*n-324},
        {"50n^0.5",50*pow(n,0.5)},
        {"2n^3",2*n*n*n},
        {"3^n",pow(3,n)},
        {"2^32*n",pow(2,32)*n},
        {"log2(n)",log2(n)},
    };
    int size = sizeof(f) / sizeof(f[0]);

    // Bubble Sort
    for(int i = 0; i < size - 1; i++)
    {
        for(int j = 0; j < size - i - 1; j++)
        {
            if(f[j].value > f[j + 1].value)
            {
                struct Function temp = f[j];
                f[j] = f[j + 1];
                f[j + 1] = temp;
            }
        }
    }

    printf("Increasing order of growth (for n = %.0lf)\n\n", n);

    for(int i = 0; i < size; i++)
    {
        printf("%2d. %-12s = %.3e\n", i + 1, f[i].name, f[i].value);
    }

    return 0;
}