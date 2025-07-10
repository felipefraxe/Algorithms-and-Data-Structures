unsigned int power(unsigned int base, unsigned int exp)
{
    if (exp == 0)
        return 1;
    
    unsigned int half = power(base, exp / 2);
    unsigned int result = half * half;
    if (exp % 2 == 1)
        result *= base;
    return result;
}
