#include <stdlib.h>
#include <string.h>

void compute_lps(int lps[], const char *str, size_t str_len)
{
    int lps_len = 0;
    lps[0] = 0;

    int i = 1;
    while (i < str_len)
    {
        if (str[i] == str[lps_len])
            lps[i++] = lps_len++;
        else if (lps_len != 0)
            lps_len = lps[lps_len - 1];
        else
            i++;
    }
}

int kmp(const char *haystack, const char *needle)
{
    size_t haystack_len = strlen(haystack);
    size_t needle_len = strlen(needle);

    if (needle_len == 0)
        return 0;

    if (haystack_len == 0 || haystack_len < needle_len)
        return -1;

    int lps[needle_len];
    compute_lps(lps, needle, needle_len);

    int i = 0;
    int j = 0;

    while (i < haystack_len)
    {
        if (haystack[i] == needle[j])
        {
            i++;
            j++;
        }

        if (j == needle_len)
            return i - j;
        if (i < haystack_len && haystack[i] != needle[j])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    return -1;
}
