#include <stdio.h>
#include <stdlib.h>
#include "ByteArray.h"

int main()
{
    char buffer[]="00 12 01 1C 01 02 15 03 00 01 53 56 02 00 01 01 00 02 66 72 01 00 4E FB F9 D8 80 CA C4 31 8D B9 4E 4C 3D 5D B7 9E A9 2F AB 42 D0 D6 CF 46 89 9C 93 A3 97 37 BE 5B F3 52 FA 77 D6 B8 F9 AD 7A FB 8C A9 D7 8D 5C DD B5 CB 53 D0 D0 10 C0 B0 A6 56 4A F9 B1 65 F5 F6 BA 66 C9 8A 5D F5 61 1D 0C DE C6 F5 1B F8 EA 34 C8 64 3F 21 DE B0 5E 1C D5 07 2F 56 D4 E1 5B 58 B9 11 4B 03 5A 86 79 31 F0 A1 D7 D7 5C 33 FB 17 99 B2 EA 61 56 B3 8A F8 21 B7 45 9A 0C E7 8A 1A 91 B2 88 30 7B 24 81 C0 67 61 D4 2C 36 49 E9 48 80 0B D1 5B C2 50 51 D9 37 8E 3F 51 57 8B C0 80 1B E2 53 C8 07 BA 60 24 D5 99 0B 50 93 01 00 E4 EE A7 C1 D2 24 60 98 5D CC 4C 39 F3 AE 14 38 39 CC F4 04 56 C1 2E EA E8 5F 3A B2 E6 F7 90 C8 B9 0C EA 93 40 F4 A8 B3 FA 57 EE 08 5C E4 CB EE 73 35 B2 46 8A E6 92 93 E5 20 E8 F2 F3 AC AB EE DF 85 B2 70 90 83 00 09 D3 8E 5B 2F 86 24 87 98 F7 00 00 00 00 00 00 00 00 00 00 ";
    int size_buffer=sizeof(buffer)-1;
    supprimerEspaces(buffer,&size_buffer);
    conversionHexadecimal(buffer,&size_buffer);
    int tdetaille;
    int taille;
    int id;
    short int header;
    int pos=0;
    while (pos!=size_buffer)
    {
        header = (unsigned char)buffer[pos] << 8 | (unsigned char)buffer[pos+1];
        id = header >> 2;
        tdetaille = header & 3;
        printf("Identifiant du paquet : %d \n",id);
        printf("Longueur de la taille : %d \n",tdetaille);
        if(tdetaille == 0)
            taille = 0;
        else if(tdetaille  == 1)
            taille = buffer[pos+2];
        else if(tdetaille == 2)
            taille = (buffer[pos+2]<<8|buffer[pos+3]);
        else //tdetaille = 3
            taille = ((buffer[pos+2]<<16|buffer[pos+3]<<8)|buffer[pos+4]);
        printf("Taille : %d octets \n \n",taille);
        pos+=tdetaille+taille+2;
        if(id==1)
        {
            ByteArray packet= creerByteArray(&buffer[4],size_buffer-4);
            int int1=ReadInt(packet);
            int int2=ReadInt(packet);
            printf("1er int : %d, 2eme int : %d\n\n\n",int1,int2);
            detruireByteArray(packet);
        }
        else if(id==4)
        {
            ByteArray packet= creerByteArray(&buffer[2+tdetaille],size_buffer-(2+tdetaille));
            char char1=ReadByte(packet);
            bool bool1=!((char1 & 1) == 0);
            bool bool2=!((char1 & 2) == 0);
            bool bool3=!((char1 & 4) == 0);
            printf("char : %d, 1er bool : %d, 2eme bool : %d, 3eme bool : %d\n",char1,bool1,bool2,bool3);
            char version[8];
            printf("version : ");
            for(int i=0;i<5;i++)
            {
               version[i]=ReadByte(packet);
               printf("%d ",version[i]);
            }
            version[5]=ReadInt(packet);
            version[6]=ReadByte(packet);
            version[7]=ReadByte(packet);
            for(int i=5;i<8;i++)
                printf("%d ",version[i]);
            printf("\n");
            char* lang=ReadUTF(packet);
            printf("lang : %s\n",lang);
            char* credentials=ReadUTF(packet);
            printf("credentials : %s\n",credentials);
            short serverId=ReadShort(packet);
            printf("serverId : %d\n",serverId);
            double sessionOptionalSalt=ReadDouble(packet);
            printf("sessionOptionalSalt: %d\n",sessionOptionalSalt);
            detruireByteArray(packet);
        }
    }
}

void supprimerEspaces(char* buffer,int* size_buffer)
{
    int j=0;
    for(int i=0;i<*size_buffer;i++)
        if(buffer[i]==' ')
        {
            j=i;
            while(buffer[j]==' ')
            {
                j++;
                if (j>=*size_buffer)
                {
                    *size_buffer=i;
                    return;
                }

            }
            buffer[i]=buffer[j];
            buffer[j]=' ';
        }
}

void conversionHexadecimal(char* buffer, int* size_buffer)
{
    int j=0;
    int tmp1;
    int tmp2;
    for(int i=0;i<*size_buffer;i+=2)
    {
        if (buffer[i]>='A' && buffer[i]<='F')
            tmp1=buffer[i]-55;
        else
        {
            tmp1=buffer[i]-48;
        }

        if (buffer[i+1]>='A' && buffer[i+1]<='F')
            tmp2=buffer[i+1]-55;
        else
            tmp2=buffer[i+1]-48;
        buffer[j]=(tmp1*16)+tmp2;
        j++;
    }
    *size_buffer=j;
}

void afficherBuffer(char* buffer, int size_buffer)
{
    for(int i=0;i<size_buffer;i++)
        printf("%d ",buffer[i]);
    printf("\n");
}
