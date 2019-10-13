#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <netinet/in.h>
#include <ctype.h>


#include "list.h"
#include "utility.h"
#include "connection.h"

List * findAllPids()
{
    List *list = listNew();
    DIR * dir;
    struct dirent * ptr;
    dir = opendir("/proc");
    while((ptr = readdir(dir)) != NULL) {
        if (isdigit(*(ptr->d_name))) {
            listAppendString(list, ptr->d_name);
        }
    }
    closedir(dir);
    return list;
}

int main() 
{
    printString("List of TCP connections:");
    printString("Proto Local Address           Foreign Address         PID/Program name and arguments");
    List *tcpConnections = findConnections("tcp");
    // List *tcp6Connections = findConnections("tcp6");
    List *udpConnections = findConnections("udp");
    // List *udp6Connections = findConnections("udp6");
    listForEach(tcpConnections, printConnection);
    // listForEach(tcp6Connections, printConnection);
    listForEach(udpConnections, printConnection);
    // listForEach(udp6Connections, printConnection);


    // printf("%d %d", tcpConnections->scount, udpConnections->count);
    return 0;
}