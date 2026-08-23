#include <stdio.h>
#include <stdlib.h>

struct Event
{
    int point;
    int type;   // 1 = start, -1 = end
};

int compare(const void *a, const void *b)
{
    struct Event *e1 = (struct Event *)a;
    struct Event *e2 = (struct Event *)b;

    if (e1->point != e2->point)
        return e1->point - e2->point;

    // Start comes before end at same point
    return e2->type - e1->type;
}

int main()
{
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    struct Event events[2 * n];

    printf("Enter intervals:\n");

    for (int i = 0; i < n; i++)
    {
        int l, r;

        scanf("%d %d", &l, &r);

        events[2 * i].point = l;
        events[2 * i].type = 1;

        events[2 * i + 1].point = r;
        events[2 * i + 1].type = -1;
    }

    // Sort events
    qsort(events, 2 * n, sizeof(struct Event), compare);

    int count = 0;
    int maxCount = 0;
    int bestPoint = 0;

    for (int i = 0; i < 2 * n; i++)
    {
        count += events[i].type;

        if (count > maxCount)
        {
            maxCount = count;
            bestPoint = events[i].point;
        }
    }

    printf("\nPoint = %d", bestPoint);
    printf("\nMaximum number of intervals = %d\n", maxCount);

    return 0;
}