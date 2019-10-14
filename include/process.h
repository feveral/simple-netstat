#ifndef PROCESS_H
#define PROCESS_H

typedef struct process {
    int pid;
    char *name;
} Process;

List * findAllPids();


#endif