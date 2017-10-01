#include <stdarg.h>
#include <stdio.h>

void writeIntoLog(char* string,...)
{
    va_list ap;
    va_start(ap,string);
    int i=va_arg(ap,int);
    char* s=va_arg(ap,char*);
    va_end(ap);
    printf(string,i,s);
}
