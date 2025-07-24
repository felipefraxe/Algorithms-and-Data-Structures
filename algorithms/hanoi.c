#include <stdio.h>

void hanoi(int num_disks, char src, char aux, char target)
{
    if (num_disks == 1)
    {
        printf("Move disk %d from %c to %c\n", num_disks, src, target);
        return;
    }

    hanoi(num_disks - 1, src, target, aux);
    printf("Move disk %d from %c to %c\n", num_disks, src, aux);
    hanoi(num_disks - 1, aux, src, target);
}
