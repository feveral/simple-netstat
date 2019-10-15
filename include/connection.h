#ifndef CONNECTION_H
#define CONNECTION_H

#include "list.h"
#include "process.h"

typedef struct connection {
    char *type;
    char *rawLocalAddress;
    char *rawForeignAddress;
    char *localAddress;
    char *foreignAddress;
    char *inode;
} Connection;

Connection * connectionNew(char *, char *, char *, char *);
List * findConnections(char *);
Connection * parseRecordToConnection(char *, char *);
char * translateNetworkAddress(char *, char *);
Process * findProcessByConnection(List *, Connection *);

#endif