#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    pid_t pid;
    int fd[2];
    char * val ="";

    pipe(fd);
    pid = fork();

    if(pid <0){  /*Fork Failed */
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid==0){ /* Child Process*/
    	close(fd[1]);
    	read(fd[0],&val, sizeof(val));
        printf("CHILD(%d) PROCESS recieved %s\n",getpid(),val);
        close(fd[0]);

    }else{  /*Parent Process */
        close(fd[0]);
        val = "poop";
        write(fd[1], &val, sizeof(val));
        printf("Parent(%d) send value: %s\n", getpid(), val);
        printf("Child Process Complete\n");

    }
    return 0;

} //End Main
