#ifndef CONNECTION_H
#define CONNECTION_H

// #include <netinet/in.h>
// #include "list.h"

typedef struct connection {
    char *type;
    char *rawLocalAddress;
    char *rawForeignAddress;
    char *localAddress;
    char *foreignAddress;
} Connection;

Connection * connectionNew(char *, char *, char *);
List * findConnections(char *);
Connection * parseRecordToConnection(char *, char *);
char * translateNetworkAddress(char *, char *);

#endif