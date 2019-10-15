#ifndef UTILITY_H
#define UTILITY_H

#include "list.h"
#include "connection.h"
#include "process.h"

void printConnection(Connection *);
void printProcess(Process *p);
void printString(char *);
List * split(char *, const char *);
char * subString(char *, int, int);
char * intToString(int);
int stringToInt(char *);
int hexStringToInt(char *);
char * concat(const char *, const char *);
bool regexIsMatch(char *, char *);
char * addressToIP4(char *);
char * addressToIp6(char *);

#endif