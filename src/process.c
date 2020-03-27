#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <ctype.h>
#include "list.h"
#include "process.h"
#include "utility.h"


Process *processNew(char *pid, char *command, List *socketInodes)
{
    Process *process = malloc(sizeof(Process));
    process->pid = malloc( (sizeof(char)) * strlen(pid)+1);    
    process->command = malloc( (sizeof(char)) * strlen(command)+1);    
    memcpy(process->pid, pid, (sizeof(char))*strlen(pid)+1);
    memcpy(process->command, command, (sizeof(char))*strlen(command)+1);
    process->socketInodes = socketInodes;
    return process;
}

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

List * findAllProcess()
{
    List *processList = listNew();
    List *pids = findAllPids();
    ListCell *pCell = pids->head;
    while (pCell != NULL) {
        List *socketInodes = findSocketInodesByPid(pCell->value);
        char *command = findCommandByPid(pCell->value);
        Process *process = processNew(pCell->value, command, socketInodes);
        listAppend(processList, listCellNew(process, sizeof(Process)));
        pCell = pCell->next;
    }
    return processList;
}

char *findCommandByPid(char *pid)
{
    char *path = concat("/proc/", pid);
    path = concat(path, "/cmdline");
    char *command = malloc(sizeof(char) * 128);
    memset(&command[0], 0, 128);
    FILE *fp = fopen(path, "r");
    fread(command, 128, 1, fp);

    int finalCharIndex = 0;
    for (int i = 0; i <128; i++) {
        if (command[i] == '\0') {
            command[i] = ' ';
        } else {
            finalCharIndex = i;
        }
    }
    command[finalCharIndex + 1] = '\n';
    command[finalCharIndex + 2] = '\0';
    List *list = split(command, " ");
    char *commFull = listGet(list, 0)->value;
    for(int i=0;i<strlen(commFull);i++) {
        if (commFull[i] == '\n') commFull[i] = '\0';
    }
    char *commandSimplify = concat(commFull, subString(command, strlen(commFull), strlen(command)+1));
    free(command);
    return commandSimplify;
}

List *findSocketInodesByPid(char *pid)
{
    List *inodes = listNew();
    char *path = concat("/proc/", pid);
    path = concat(path, "/fd/");
    DIR * dir;
    struct dirent * ptr;
    dir = opendir(path);
    if (dir == NULL) {
        return inodes;
    }
    while((ptr = readdir(dir)) != NULL) {
        if (strcmp(ptr->d_name,".") && strcmp(ptr->d_name,"..")) {
            char * inode = findInodeByLinkPath(concat(path, ptr->d_name));
            if (inode != NULL) listAppend(inodes, listCellNew(inode, sizeof(inode)));
        }
    }
    closedir(dir);
    return inodes;
}

char *findInodeByLinkPath(char *path)
{
    char linkMessage[256];
    readlink(path, linkMessage, 256);

    List *sp = split(linkMessage, ":");

    if (!strcmp(listGet(sp, 0)->value, "socket")) {
        ListCell *inodeCell = listGet(sp, 1);
        char *inode = subString(inodeCell->value, 1, strlen(inodeCell->value)-1);
        return inode;
    } else if (!strcmp(listGet(sp, 0)->value, "socket")) {
        ListCell *inodeCell = listGet(sp, 1);
        return inodeCell->value;
    } else {
        return NULL;
    }
}

bool isInodeInProcess(Process *process, char *inode)
{
    ListCell *socketInodeCell = (process->socketInodes)->head;
    while (socketInodeCell != NULL) {
        if (stringToInt(socketInodeCell->value) == stringToInt(inode)) {
            return true;
        }
        socketInodeCell = socketInodeCell->next;
    }
    return false;
}
