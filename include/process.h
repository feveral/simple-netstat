#ifndef PROCESS_H
#define PROCESS_H

#include <stdbool.h>

typedef struct process {
    char *pid;
    char *command;
    List *socketInodes;
} Process;


Process *processNew(char *, char *, List *);

List * findAllProcess();
List * findAllPids();
char *findCommandByPid(char *);
List *findSocketInodesByPid(char *);
char *findInodeByLinkPath(char *);
bool isInodeInProcess(Process *, char *);

#endif