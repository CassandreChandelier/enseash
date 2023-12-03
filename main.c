
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define ENSEASH "enseash "
#define PROMPT ENSEASH"% "
#define WELCOME "Welcome to ENSEA Tiny Shell\r\nType 'exit' to quit\r\n"PROMPT
#define EXITMESSAGE "Bye bye...\r\n"

#define NBYTES 128

void prompt(char *message){ write(1,message,strlen(message));}

void welcomeMessage(){prompt(WELCOME);}

void executionCommand(char *command) {

	pid_t childPid = fork();

	if (childPid == -1) { perror("fork");} //error

	if (childPid == 0) { //son
		execlp(command, command, (char *)NULL);
		perror("execlp");
		exit(1);

	} else { //parent
		int status;
      		waitpid(childPid, &status, 0);

		if (WIFEXITED(status)){ //return code
			char statusMessage[NBYTES];
			prompt(ENSEASH);
			sprintf(statusMessage,"[exit: %d]",WEXITSTATUS(status));
			write(STDOUT_FILENO,statusMessage,strlen(statusMessage));
			prompt(" % ");
		}

		else if (WIFSIGNALED(status)){//return signal if end of son because of signal
			char statusMessage[NBYTES];
			prompt(ENSEASH);
			sprintf(statusMessage,"[sig: %d]",WTERMSIG(status));
			write(STDOUT_FILENO,statusMessage,strlen(statusMessage));
			prompt(" % ");

		}
	}
}


int main(void){

	char command[NBYTES];
	ssize_t input;

       	welcomeMessage() ;

	while(1){

		input = read(STDIN_FILENO,command, sizeof(command));

		if (input == -1 || input == 0) {
			write(STDERR_FILENO, EXITMESSAGE, sizeof(EXITMESSAGE));
			exit(EXIT_FAILURE);
		}

		command[input-1]='\0';

		if (strcmp(command,"exit")==0){
			write(STDOUT_FILENO,EXITMESSAGE,sizeof(EXITMESSAGE));
			exit(EXIT_SUCCESS);
		}
		executionCommand(command);
	}
	return EXIT_SUCCESS;
}

