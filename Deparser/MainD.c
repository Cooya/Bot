#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LINE_LENGTH 75
#define LENGTH 54

FILE* LOG_FILE;

void swap(char* s, int i, int j)
{
    char tmp=s[i];
    s[i]=s[j];
    s[j]=tmp;
}

bool isDigit(char c)
{
    return (c>='0' && c<='9');
}

bool isHexa(char c)
{
    return (isDigit(c) || (c>='A' && c<='F'));
}

int readSizePacket(char* line)
{
    char* tmp=(line+10);
    while(!isDigit(*tmp))
        tmp++;
    int i=0;
    while(isDigit(tmp[i]))
        i++;
    tmp[i]='\0';
    return atoi(tmp);
}

int minimizeString(unsigned char *s) {
    int cpt=0;
    unsigned char *pos=s;

    for(int i=0; i<16; i++) {
        if(!isHexa(*s))
            break;
        *pos++=*s++;
        *pos++=*s++;
        s++;

        cpt++;
    }

    return cpt*2;
}

int convertCharHexaToNumber(char c)
{
    if (isDigit(c))
        return c-48;
    if (isHexa(c))
        return c-55;
    printf("Erreur de conversion !");
    exit(0);
}

void convertStringHexaToNumber(unsigned char* s, int length)
{
    int j=0;
    for(int i=0; i<length; i+=2,j++)
        s[j]=(convertCharHexaToNumber(s[i])*16)+convertCharHexaToNumber(s[i+1]);
    s[j]='\0';
}

void appendStringToString(unsigned char* dest, unsigned char* src, int length)
{
    for(int i=0; i<length; i++)
        *dest++=*src++;
}

bool getDirection(char* s)
{
    if(strstr(s,"Send")!=NULL)
        return true;
    else if(strstr(s,"Recv")!=NULL)
        return false;
    else
    {
        printf("Erreur de lecture !");
        exit(0);
    }
}

int main()
{
    FILE* file=fopen("wpe.txt","r");
    LOG_FILE=fopen("log.txt","w");
    char* line=malloc(LINE_LENGTH);
    char* line2=malloc(LINE_LENGTH);
    unsigned char* line_tmp;
    unsigned char* buffer;
    int buffer_size;
    int pos=0;
    bool direction;
    while(fgets(line,LENGTH,file)!=NULL)
    {
        if(strstr(line,"Hide")!=NULL)
        {

            fgets(line2,LINE_LENGTH,file);
            if(strstr(line2,"key")!=NULL) // vérif du paquet relou
                continue;
            fseek(file,-(strlen(line2)+1),SEEK_CUR);

            direction=getDirection(line);
            pos=0;
            buffer_size=readSizePacket(line);
            buffer=malloc(buffer_size);
            int toRead=buffer_size/16;
            if(buffer_size%16!=0)
                toRead++;
            for(int i=0; i<toRead; i++)
            {
                fgets(line,LINE_LENGTH,file);
                line_tmp=line+6;
                int line_length=minimizeString(line_tmp);
                convertStringHexaToNumber(line_tmp,line_length);
                appendStringToString(buffer+pos,line_tmp,line_length/2);
                pos+=line_length/2;
            }
            handleBuffer(buffer,buffer_size,direction);
        }
    }
    free(line);
    fclose(file);
    return EXIT_SUCCESS;
}
