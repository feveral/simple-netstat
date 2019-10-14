#include <stdio.h>
#include <string.h>



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