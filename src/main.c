#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <netinet/in.h>
#include <ctype.h>
#include <unistd.h>


#include "list.h"
#include "utility.h"
#include "connection.h"


int main(int argc, char **argv) 
{

    

    // const char *optstring = "tu:";
    // struct option opts[] = {
    //     {"tcp", 0, NULL, 't'}, // 0 represent no parameter
    //     {"ucp", 0, NULL, 'u'}, // 0 represent no parameter
    // };
    // char ch = getopt_long(argc, argv, optstring, opts);
    // printf("%c", ch);
    // switch(ch) {
    //     case 't':
    //         printString("List of TCP connections:");
    //         printString("Proto Local Address           Foreign Address         PID/Program name and arguments");
    //         List *tcpConnections = findConnections("tcp");
    //         // List *tcp6Connections = findConnections("tcp6");
    //         listForEach(tcpConnections, printConnection);
    //         // listForEach(tcp6Connections, printConnection);
    //         break;
    //     case 'u':
            
    //         printString("List of TCP connections:");
    //         printString("Proto Local Address           Foreign Address         PID/Program name and arguments");
    //         List *udpConnections = findConnections("udp");
    //         // List *udp6Connections = findConnections("udp6");
    //         listForEach(udpConnections, printConnection);
    //         // listForEach(udp6Connections, printConnection);            
    //         break;
    //     default:
    //         List *tcpConnections = findConnections("tcp");
    //         // List *tcp6Connections = findConnections("tcp6");
    //         List *udpConnections = findConnections("udp");
    //         // List *udp6Connections = findConnections("udp6");
    //         listForEach(tcpConnections, printConnection);
    //         // listForEach(tcp6Connections, printConnection);
    //         listForEach(udpConnections, printConnection);
    //         // listForEach(udp6Connections, printConnection);
    // }
    return 0;
}