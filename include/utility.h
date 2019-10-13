#ifndef UTILITY_H
#define UTILITY_H

#include "list.h"
#include "connection.h"

void printConnection(Connection *);
void printString(char *);
List * split(char *, const char *);
char * subString(char *, int, int);
int hexStringToInt(char *);
char * concat(const char *, const char *);
char * addressToIP4(char *);
char * addressToIp6(char *);

#endif