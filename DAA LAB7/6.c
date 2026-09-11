#include <stdio.h>
#include <stdlib.h>

struct Event
{
    int year;
    int type;
};

int compare(const void *a, const void *b)
{
    struct Event *e1 = (struct Event *)a;
    struct Event *e2 = (struct Event *)b;

    if (e1->year != e2->year)
        return e1->year - e2->year;

    return e1->type - e2->type;
}

int main()
{
    int n;
    int i;
    int alive = 0;
    int maxAlive = 0;
    int bestYear = 0;

    printf("Enter number of scientists: ");
    scanf("%d", &n);

    struct Event *events = malloc(2 * n * sizeof(struct Event));

    for (i = 0; i < n; i++)
    {
        int birth, death;

        printf("Enter birth and death year of scientist %d: ", i + 1);
        scanf("%d %d", &birth, &death);

        events[2 * i].year = birth;
        events[2 * i].type = 1;

        events[2 * i + 1].year = death;
        events[2 * i + 1].type = -1;
    }

    qsort(events, 2 * n, sizeof(struct Event), compare);

    for (i = 0; i < 2 * n; i++)
    {
        alive += events[i].type;

        if (alive > maxAlive)
        {
            maxAlive = alive;
            bestYear = events[i].year;
        }
    }

    printf("\nMaximum number of scientists alive = %d\n", maxAlive);
    printf("Best time to be alive = %d\n", bestYear);

    free(events);

    return 0;
}