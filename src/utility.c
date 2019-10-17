#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <regex.h> 
#include <netinet/in.h>
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
    printf("%-20s", c->inode);
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
    char *result = malloc(sizeof(char) * 64);
    struct sockaddr_in sa;
    struct in_addr ip;
    ip.s_addr = hexStringToInt(subString(address, 0, 8));
    sa.sin_family = AF_INET; 
    sa.sin_addr = ip;
    inet_ntop(AF_INET, &(sa.sin_addr), result, INET_ADDRSTRLEN);
    return result;
}

char * addressToIp6(char *address)
{
    char *result = "";
    char *tmp = malloc(sizeof(char) * 33);
    memset(tmp, 0, 33);

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
    char *resultAddress = malloc(sizeof(char) * 128);
    memset(resultAddress, 0, 128);
    struct sockaddr_in6 sa;
    struct in6_addr ip;
    for(int i = 0; i < 16;i++) {
        ip.s6_addr[i] = hexStringToInt(subString(tmp, i*2, i*2+2)); 
    }
    sa.sin6_family = AF_INET6; 
    sa.sin6_addr = ip;
    inet_ntop(AF_INET6, &(sa.sin6_addr), resultAddress, INET6_ADDRSTRLEN);
    return resultAddress;
}