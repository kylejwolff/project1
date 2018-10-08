#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#include "child1.h"

int main(int argc, char const *argv[])
{
    int pfds[2];
    char buf[30];

    pipe(pfds);

    int child_pid=fork();
    if(child_pid == 0){
        printf(" CHILD: writing to the pipe\n");
        write(pfds[1], "test", 5);
        printf(" CHILD: exiting\n");
        exit(0);

    }
    else{
        //close(pfds[0]);
        printf("PARENT: reading from pipe\n");
        read(pfds[0], buf, 5);
        printf("PARENT: read \"%s\"\n", buf);
        wait(NULL);
    }
    return 0;
}
