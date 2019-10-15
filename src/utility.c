#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <regex.h> 
#include "utility.h"
#include "connection.h"
#include "process.h"
#include "list.h"

void printConnection(Connection *c)
{
    printf("%-6s", c->type);
    printf("%-22s  ", c->localAddress);
    printf("%-20s", c->rawLocalAddress);
    printf("%-20s", c->foreignAddress);
    printf("%-20s", c->rawForeignAddress);
    printf("%-20d", c->inode);
    printf("\n");
}

void printProcess(Process *p)
{
    printf("pid: %s ", p->pid);
    printf("command: %s", p->command);
    listForEach(p->socketInodes, printString);
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

int stringToInt(char *string)
{
    return (int)strtol(string, NULL, 10);
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

bool regexIsMatch(char *pattern, char *string)
{
    regex_t reg;
    regcomp(&reg, pattern, REG_EXTENDED);
    const size_t nmatch = 1;
    regmatch_t pmatch[1];
    int status = regexec(&reg, string, nmatch, pmatch, 0); //匹配他
    return !(status == REG_NOMATCH);
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
    char *result = "";
    char *tmp = malloc(sizeof(char) * 33);
    for (int i = 0; i < 4; i++) {
        tmp[0+8*i] = address[6+8*i];
        tmp[1+8*i] = address[7+8*i];
        tmp[2+8*i] = address[4+8*i];
        tmp[3+8*i] = address[5+8*i];
        tmp[4+8*i] = address[2+8*i];
        tmp[5+8*i] = address[3+8*i];
        tmp[6+8*i] = address[0+8*i];
        tmp[7+8*i] = address[1+8*i];
    }
    for (int i = 0; i < 8; i++) {
        char *numString = subString(tmp, i*4, i*4+4);
        int num = stringToInt(numString);
        result = concat(result, intToString(num));
        if (i != 7) result = concat(result, ":");
        free(numString);
    }
    return result;
}