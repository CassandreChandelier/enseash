
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define ENSEASH "enseash "
#define PROMPT ENSEASH"% "
#define WELCOME "Welcome to ENSEA Tiny Shell\r\nType 'exit' to quit\r\n"PROMPT
#define EXITMESSAGE "Bye bye...\r\n"
#define ERROR "Error\n"


#define NBYTES 128
#define MILLION 1000000.0

void prompt(char *message){write(1,message,strlen(message));}

void welcomeMessage(){prompt(WELCOME);}

void wifReturn(int status, const char *type, int value, struct timespec *start, struct timespec *end){

	clock_gettime(CLOCK_REALTIME,end);
	double time_spent = (end->tv_sec - start->tv_sec)*1000.0 +
		(end->tv_nsec - start->tv_nsec)/MILLION;

	char statusMessage[NBYTES];
	prompt(ENSEASH);
	sprintf(statusMessage,"[%s: %d|%0.0fms]",type,value,time_spent);
	write(STDOUT_FILENO,statusMessage,strlen(statusMessage));
	prompt(" % ");
}


void executionCommand(char *command) {

	struct timespec start, end;
	clock_gettime(CLOCK_REALTIME,&start);

	pid_t childPid = fork();

	if (childPid == -1) { perror("fork");} //error

	if (childPid == 0) { //son

//		execlp(command, command, (char *)NULL);
		execvp(command,**command);

		perror("execlp");
		exit(1);

	} else { //parent
		int status;
      		waitpid(childPid, &status, 0);

		if (WIFEXITED(status)){ //return code

			wifReturn(status,"exit",WEXITSTATUS(status),&start,&end);}

		else if (WIFSIGNALED(status)){//return signal if end of son because of signal

			wifReturn(status,"sign",WTERMSIG(status),&start,&end);}
	}
}


int main(void){

	char command[NBYTES];
	ssize_t input;

       	welcomeMessage() ;

	while(1){

		input = read(STDIN_FILENO,command, sizeof(command));

		if (input == -1 || input == 0) { //verify if the user did <ctl>+D
			write(STDERR_FILENO, EXITMESSAGE, sizeof(EXITMESSAGE));
			exit(EXIT_FAILURE);
		}

		command[input-1]='\0'; //change \n by \0

		const char * separators = " ,.-!";
		char * strToken = strtok(command,separators);
		while (strToken != NULL) {
			strToken = strtok(NULL,separators);
		}


		if (strcmp(command,"exit")==0){
			write(STDOUT_FILENO,EXITMESSAGE,sizeof(EXITMESSAGE));
			exit(EXIT_SUCCESS);
		}


		executionCommand(command);

	}
	return EXIT_SUCCESS;
}
