#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static size_t sqrt(size_t num)
{
    if (num < 2)
        return num;

    size_t lo = 1;
    size_t hi = num >> 1;
    while (lo <= hi)
    {
        size_t mid = lo + ((hi - lo) >> 1);
        size_t target = num / mid;

        if (mid == target)
            return mid;

        if (mid < target)
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    return hi;
}

bool *sieve_of_eratosthenes(size_t num)
{
    bool *sieve = malloc(sizeof(bool) * (num + 1));
    if (sieve == NULL)
        return NULL;

    for (size_t i = 2; i <= num; i++)
        sieve[i] = true;

    sieve[0] = false;
    if (num >= 1)
        sieve[1] = false;

    for (size_t prime = 2, limit = sqrt(num); prime <= limit; prime++)
    {
        if (sieve[prime])
        {
            for (size_t i = prime * prime; i <= num; i += prime)
                sieve[i] = false;
        }
    }

    return sieve;
}

int main(void)
{
    bool *sieve = sieve_of_eratosthenes(200000000);
    free(sieve);
    return 0;
}