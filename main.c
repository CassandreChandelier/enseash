#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define WELCOME "Welcome to ENSEA Tiny Shell\r\nType 'exit' to quit\r\nenseash % "
#define PROMPT "enseash % "

#define NBYTES 128

void welcomeMessage(){ write(1, WELCOME, sizeof(WELCOME));}

void prompt(){ write(1,PROMPT,sizeof(PROMPT));}


void executionCommand() {

	while(1) {
    		char command[NBYTES];

    		//input
		ssize_t input = read(1, command, sizeof(command));

    		if (input == -1) { perror("read"); }

    		//replace the last character '\n'
    		if (input > 0 && command[input-1] == '\n') { command[input-1] = '\0';}

    		pid_t childPid = fork();

    		if (childPid == -1) { perror("fork");} //error

    		if (childPid == 0) { //son
        		execlp(command, command, (char *)NULL);
        		perror("execlp");
        		exit(1);
    		} else { //parent
        		waitpid(childPid, NULL, 0);
    		}
		prompt();

	}


}

int main(void){

        welcomeMessage() ;
	executionCommand();

        return EXIT_SUCCESS ;
}


