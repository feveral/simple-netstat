#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

#include "list.h"
#include "utility.h"
#include "connection.h"
#include "process.h"

void outputConnectionResult(List *connectionList, List *processList, char *keyword)
{
    ListCell *connectionCell = connectionList->head; 
    while(connectionCell!= NULL) {
        Connection *connection = connectionCell->value;
        Process *process = findProcessByConnection(processList, connectionCell->value);
        if (keyword == NULL || (process != NULL && regexIsMatch(keyword, process->command))) {
            printf("%-6s", connection->type);
            printf("%-22s  ", connection->localAddress);
            printf("%-20s", connection->foreignAddress);
            if (process != NULL) printf("%8s/%s", process->pid, process->command);
            else printf("%13s\n", "----/----");
        }
        connectionCell = connectionCell->next;
    }    
}

int main(int argc, char **argv) 
{
    int opt;
    int digit_optind = 0;
    int option_index = 0;
    char *optstring = ":tu";
    static struct option long_options[] = {
        {"tcp", optional_argument, NULL, 't'},
        {"udp", optional_argument, NULL, 'u'},
        {0, 0}
    };

    List *processList = findAllProcess();
    while ( (opt = getopt_long(argc, argv, optstring, long_options, &option_index)) != -1){
        if (opt == 't') {
            List *tcpConnections = findConnections("tcp");
            List *tcp6Connections = findConnections("tcp6");
            printString("List of TCP connections:");
            printString("Proto Local Address           Foreign Address         PID/Program name and arguments");
            outputConnectionResult(tcpConnections, processList, argv[optind]);
            outputConnectionResult(tcp6Connections, processList, argv[optind]);
            return 0;
        } else if (opt == 'u') {
            List *udpConnections = findConnections("udp");
            List *udp6Connections = findConnections("udp6");
            printString("List of UDP connections:");
            printString("Proto Local Address           Foreign Address         PID/Program name and arguments");
            outputConnectionResult(udpConnections, processList, argv[optind]);
            outputConnectionResult(udp6Connections, processList, argv[optind]);
            return 0;
        }
    }
    List *udpConnections = findConnections("udp");
    List *udp6Connections = findConnections("udp6");
    List *tcpConnections = findConnections("tcp");
    List *tcp6Connections = findConnections("tcp6");
    printString("List of TCP connections:");
    printString("Proto Local Address           Foreign Address         PID/Program name and arguments");
    outputConnectionResult(tcpConnections, processList, argv[optind]);
    outputConnectionResult(tcp6Connections, processList, argv[optind]);
    printString("List of UDP connections:");
    printString("Proto Local Address           Foreign Address         PID/Program name and arguments");
    outputConnectionResult(udpConnections, processList, argv[optind]);
    outputConnectionResult(udp6Connections, processList, argv[optind]);
    return 0;
}