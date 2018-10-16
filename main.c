#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MSGLEN  255
int main(){
    int     fd[2];
    pid_t pid;
    int     result;

    
    //Creating a pipe
    result = pipe (fd);
    if (result < 0) {
        //failure in creating a pipe
        perror("pipe");
        exit (1);
    }
    
    //Creating a child process
    pid = fork();
    if (pid < 0) {
         //failure in creating a child
         perror ("fork");
         exit(2);
    }

    if (pid == 0) {
        //Child process
         char message[MSGLEN];
         char *old_message;

          while(1) {
                    //Clearing the message
                    memset (message, 0, sizeof(message));

                    //Reading message from the pipe
                    close(fd[1]);
                    read (fd[0], message, sizeof(message));

                    //Trying to break loop
                    //if(message == old_message) break;
                    //else old_message = message;

                    //Debugging print
                    printf("%s",message);
            }
            exit(0);
    }
    else {
        //Parent Process
         char message[MSGLEN];
         
         FILE *fp;
         fp = fopen("./ANNA_KARENINA.txt", "r");

         while (fgets(message, sizeof(message), (FILE*)fp) != NULL) {
                    //Writing message to the pipe
                    close(fd[0]);
                    write(fd[1], message, strlen(message));
         }

         //exit(0);
     }
     return 0;
}