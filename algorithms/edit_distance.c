#include <stdlib.h>
#include <string.h>

static inline int min(int num1, int num2)
{
    return num1 < num2 ? num1 : num2;
}

unsigned int edit_distance(char *str1, char *str2)
{
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    unsigned int dp[len1 + 1][len2 + 1];
    for (unsigned int i = 0; i <= len1; i++)
        dp[i][0] = i;
    for (unsigned int j = 0; j <= len2; j++)
        dp[0][j] = j;

    for (unsigned int i = 1; i <= len1; i++)
    {
        for (unsigned int j = 1; j <= len2; j++)
        {
            if (str1[i - 1] == str2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
            {
                unsigned int deletion = dp[i - 1][j];
                unsigned int insertion = dp[i][j - 1];
                unsigned int substitution = dp[i - 1][j - 1];
                dp[i][j] = min(min(deletion, insertion), substitution) + 1;
            }
        }
    }

    return dp[len1][len2];
}
