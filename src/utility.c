#include <stdio.h>
#include <string.h>
#include "utility.h"
#include "connection.h"

void printConnection(Connection *c)
{
    printf("%-6s", c->type);
    printf("%-22s  ", c->localAddress);
    printf("%-20s", c->rawLocalAddress);
    printf("%-20s", c->foreignAddress);
    printf("%-20s", c->rawForeignAddress);
    printf("\n");
}

void printString(char *string)
{
    printf("%s\n", string);
}

List *split(char *string, const char *token)
{
    List *list = listNew();
    int bufferLength = strlen(string)+1;
    char buffer[bufferLength];

    memset(buffer, 0, bufferLength);
    strncpy(buffer, string, bufferLength-1);
    buffer[bufferLength-1] = '\0';

    char *fragment = strtok(buffer, token);
    listAppendString(list, fragment);
    while(fragment != NULL) {
        fragment = strtok(NULL, token);
        if (fragment != NULL) {
            listAppendString(list, fragment);
        }
    }
    return list;
}

int hexStringToInt(char *hexString)
{
    return (int)strtol(hexString, NULL, 16);
}

char * intToString(int num)
{
    char *str = malloc(sizeof(char) * 64);
    sprintf(str,"%d",num);
    return str;
}

char * concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char * subString(char *string, int start, int end)
{
    char *substring = malloc(sizeof(char) * (end - start) );
    for (int i = 0; i < strlen(string) ; i++) {
        strncpy(substring, string + start, end - start);
    }
    return substring;
}

char * addressToIP4(char *address)
{
    char *result = "";
    for(int i = 3; i >= 0; i--) {
        char hexNum[3];
        hexNum[0] = address[i*2];
        hexNum[1] = address[i*2+1];
        hexNum[2] = '\0';
        int num = hexStringToInt(hexNum);
        char *str = intToString(num); // memory leak problem
        result = concat(result, str);
        if (i != 0) result = concat(result, ".");
    }
    return result;
}

char * addressToIp6(char *address)
{

}