#include <stdbool.h>

bool strEquals(char* str1, char* str2, int len)
{
    for(int i=0;i<len;++i)
        if (str1[i]!=str2[i])
            return false;
    return true;
}
