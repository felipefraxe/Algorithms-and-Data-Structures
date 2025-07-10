static inline int max(int num1, int num2)
{
    return num1 > num2 ? num1 : num2;
}

unsigned int kadane(int arr[], int length)
{
    int curr_max = 0;
    int curr_sum = 0;
    for (size_t i = 0; i < length; i++)
    {
        curr_sum = max(curr_sum + arr[i], arr[i]);
        curr_max = max(curr_max, curr_sum);
    }
    return curr_max;
}
