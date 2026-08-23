#include <stdio.h>
#include <stdlib.h>

struct Event
{
    int time;
    int type;   // +1 for entry, -1 for exit
};

int compare(const void *a, const void *b)
{
    struct Event *e1 = (struct Event *)a;
    struct Event *e2 = (struct Event *)b;

    return e1->time - e2->time;
}

int main()
{
    int n;

    printf("Enter number of people: ");
    scanf("%d", &n);

    struct Event events[2 * n];

    printf("Enter entry and exit time:\n");

    for (int i = 0; i < n; i++)
    {
        int a, b;

        scanf("%d %d", &a, &b);

        events[2 * i].time = a;
        events[2 * i].type = 1;

        events[2 * i + 1].time = b;
        events[2 * i + 1].type = -1;
    }

    // Sort events by time
    qsort(events, 2 * n, sizeof(struct Event), compare);

    int count = 0;
    int maxPeople = 0;
    int maxTime = 0;

    for (int i = 0; i < 2 * n; i++)
    {
        count += events[i].type;

        if (count > maxPeople)
        {
            maxPeople = count;
            maxTime = events[i].time;
        }
    }

    printf("\nMaximum people present = %d", maxPeople);
    printf("\nTime = %d\n", maxTime);

    return 0;
}