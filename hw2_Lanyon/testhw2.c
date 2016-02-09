/*************************************************
* Course: CS 4540 – Fall 2015
* Assignment 2 - Problem 1
* Name: Justin Lanyon
* E-mail: justin.j.lanyon@wmich.edu
* Submitted: 10/19/2015
/*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//  Parent: reads from P1_READ, writes on P1_WRITE
//  Child:  reads from P2_READ, writes on P2_WRITE
#define P1_READ     0
#define P2_WRITE    1
#define P2_READ     2
#define P1_WRITE    3
#define NUM_PIPES   2
#define false       0 //Used for testing password strength

//Prototypes for other functions
char * passTest(char * password);
char * getPass(char * password);


int main(int argc, char *argv[])
{
    int fd[2*NUM_PIPES];
    int len, i;
    char * val = malloc(100);
    pid_t pid;
    int tend =100;

    // create all the descriptor pairs we need
    for (i=0; i<NUM_PIPES; ++i)
    {
        if (pipe(fd+(i*2)) < 0)
        {
            perror("Piping Failed");
            exit(EXIT_FAILURE);
        }
    }
    //FORK ERROR
    if ((pid = fork()) < 0)
    {
        perror("Fork Error");
        return EXIT_FAILURE;
    }

    //child process
    if (pid == 0)
    {
        // Child. CLOSE UNNEEDED FD
        close(fd[P1_READ]);
        close(fd[P1_WRITE]);

        // used for output
        pid = getpid();

        // wait until parent sends a value
        len = read(fd[P2_READ], val, tend);
        if (len < 0)
        {
            perror("Child: Failed to read data from pipe\n");
            exit(EXIT_FAILURE);
        }
        else if (len == 0)//In case nothing in pipe
        {
            fprintf(stderr, "Child: Read EOF from pipe\n");
        }
        else
        {
            // report what was recieved
            //printf("Child(%d): Received >%s<\n", pid, val);
            val = passTest(val); //CHECK PASSWORD
            tend = strlen(val);
            //printf("Child(%d): Sending >%s< back\n", pid, val);
            if (write(fd[P2_WRITE], val, tend+1) < 0)
            {
                perror("Child: Failed to write response value");
                exit(EXIT_FAILURE);
            }
        }
        // finished. close remaining descriptors.
        close(fd[P2_READ]);
        close(fd[P2_WRITE]);

        return EXIT_SUCCESS;
        //END CHILD PROCESS
    }else{
    //PARENT PROCESS
    // Close unused FD
        close(fd[P2_READ]);
        close(fd[P2_WRITE]);

    // used for output
        pid = getpid();

    // send password to child
        val = getPass(val);
        strtok(val, "\n"); 
        tend = strlen(val);
        //printf("Parent(%d): Sending %s to child\n", pid, val);
        if (write(fd[P1_WRITE], val, tend+1) != tend+1)
        {
            perror("Parent: Failed to send value to child ");
            exit(EXIT_FAILURE);
        }

    // now wait for a response
        len = read(fd[P1_READ], val, tend);
        if (len < 0)
        {
            perror("Parent: failed to read value from pipe\n");
            exit(EXIT_FAILURE);
        }
        else if (len == 0)
        {
        // not an error, but certainly unexpected
            fprintf(stderr, "Parent(%d): Read EOF from pipe\n", pid);
        }
        else
        {
        // report what we received
            //printf("Parent(%d): Received %s\n", pid, val);
            printf("That is a %s password\n",val );
        }

    // close descriptors
        close(fd[P1_READ]);
        close(fd[P1_WRITE]);

    // wait for child termination
        wait(NULL);
        return EXIT_SUCCESS;
    }
}//END MAIN


char * getPass(char * password){
    printf("\nWELCOME TO APPLICATION X\n");
    printf("Please enter the password: ");
    fgets(password, 50, stdin);
    return password;
}
char * passTest(char * password){
    char * passStrength = malloc(100);
    int   i=0;
    int  found_lower = false, found_upper = false, found_number =false;

    while(password[i] != '\0' || !(found_lower && found_upper&& found_number)) {
        found_lower = found_lower || (password[i] >= 'a' && password[i] <= 'z');
        found_upper = found_upper || (password[i] >= 'A' && password[i] <= 'Z');
        found_number = found_number ||(password[i] >= '0' && password[i] <= '9');
        i++;
    }
    if(found_lower && found_upper&& found_number){
        strcpy(passStrength, "strong");
    }else{
        strcpy(passStrength, "weak");
    }
    if(strlen(password)<8){
        strcpy(passStrength, "short");
    }
    printf("passStrength >%s<\n",passStrength);
    return passStrength;
}