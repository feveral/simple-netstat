
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <netinet/in.h>
#include "list.h"
#include "utility.h"
#include "connection.h"

#define CONNECTION_TCP "tcp"
#define CONNECTION_TCP6 "tcp6"
#define CONNECTION_UDP "udp"
#define CONNECTION_UDP6 "udp6"

#define TCP_SOURCE_PATH "/proc/net/tcp"
#define TCP6_SOURCE_PATH "/proc/net/tcp6"
#define UDP_SOURCE_PATH "/proc/net/udp"
#define UDP6_SOURCE_PATH "/proc/net/udp6"

Connection * connectionNew(char *local, char *foreign, char *inode, char *type)
{
    Connection *connection = malloc(sizeof(Connection));
    
    connection->rawLocalAddress = malloc( (sizeof(char)) * strlen(local)+1);
    connection->rawForeignAddress = malloc( (sizeof(char)) * strlen(foreign)+1);    
    memcpy(connection->rawLocalAddress, local, (sizeof(char))*strlen(local)+1);
    memcpy(connection->rawForeignAddress, foreign, (sizeof(char))*strlen(foreign)+1);
    
    char *localAddress = translateNetworkAddress(connection->rawLocalAddress, type);
    char *foreignAddress = translateNetworkAddress(connection->rawForeignAddress, type);    
    
    connection->localAddress = malloc( (sizeof(char)) * strlen(localAddress)+1);
    connection->foreignAddress = malloc( (sizeof(char)) * strlen(foreignAddress)+1);
    
    memcpy(connection->localAddress, localAddress, (sizeof(char))* strlen(localAddress)+1);
    memcpy(connection->foreignAddress, foreignAddress, (sizeof(char))* strlen(foreignAddress)+1);
    
    connection->inode = malloc((sizeof(char)) * strlen(inode)+1);
    memcpy(connection->inode, inode, (sizeof(char))* strlen(inode)+1);
    
    connection->type = malloc((sizeof(char)) * strlen(type)+1);
    memcpy(connection->type, type, (sizeof(char))*strlen(type)+1);

    return connection;
}

char * translateNetworkAddress(char *address16, char *type)
{
    if (strcmp(type, CONNECTION_TCP) == 0 || strcmp(type, CONNECTION_UDP) == 0) {
        // struct sockaddr_storage sas;
        // struct sockaddr_in *addrin = (struct sockaddr_in *)&sas;

        // char addrString[128];
        // int port;
        // sscanf(address16, "%64[0-9A-Fa-f]:%X", addrString, &port);
        // sscanf(addrString, "%X", &addrin->sin_addr.s_addr);
        // sas.ss_family = AF_INET;
        
        // char *resultAddress = malloc(sizeof(char) * INET_ADDRSTRLEN);
        // inet_ntop(AF_INET, addrin, resultAddress, INET_ADDRSTRLEN);
        // return resultAddress;        

        char *ip4addr = addressToIP4(address16);
        char *ip4port = intToString(hexStringToInt(subString(address16, 9, 13)));
        
        return concat(ip4addr, concat(":", ip4port));
    } else if (strcmp(type, CONNECTION_TCP6) == 0 || strcmp(type, CONNECTION_UDP6) == 0) {
        return address16;
    }
}

Connection * parseRecordToConnection(char *record, char *type)
{
    List *items = split(record, " ");
    ListCell *localAddressCell = listGet(items, 1);
    ListCell *foreignAddressCell = listGet(items, 2);
    ListCell *inodeCell = listGet(items, 9);
    return connectionNew(localAddressCell->value, foreignAddressCell->value, inodeCell->value, type);
}

List * findConnections(char *type)
{
    char *sourcePath;
    if (strcmp(type, CONNECTION_TCP) == 0) {
        sourcePath = TCP_SOURCE_PATH;
    } else if (strcmp(type, CONNECTION_TCP6) == 0) {
        sourcePath = TCP6_SOURCE_PATH;
    } else if (strcmp(type, CONNECTION_UDP) == 0) {
        sourcePath = UDP_SOURCE_PATH;
    } else if (strcmp(type, CONNECTION_UDP6) == 0) {
        sourcePath = UDP6_SOURCE_PATH;
    } else return NULL;

    List *connections = listNew();
    int bufferSize = 20000;
    char buffer[bufferSize];
    memset(&buffer[0], 0, sizeof(buffer));

    FILE *fp = fopen(sourcePath, "r");
    size_t size = fread(buffer, bufferSize, 1, fp);
    List *lines = split(buffer, "\n");

    ListCell *current = lines->head;
    current = current->next;
    while(current != NULL) {
        Connection *c = parseRecordToConnection(current->value, type);
        ListCell *cell = listCellNew(c, sizeof(Connection));
        listAppend(connections, cell);
        current = current->next;
    }
    return connections;
}

Process * findProcessByConnection(List *processList, Connection *connection)
{
    ListCell *pCell = processList->head;
    while(pCell != NULL) {
        if (isInodeInProcess(pCell->value, connection->inode)) {
            return pCell->value;
        }
        pCell = pCell->next;
    }
    return NULL;
}