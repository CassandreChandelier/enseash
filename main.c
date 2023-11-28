#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define WELCOME "Welcome to ENSEA Tiny Shell\r\nType 'exit' to quit\r\nenseash % "

void welcomeMessage(){
        write(1, WELCOME, sizeof(WELCOME)) ;
}

int main(void){

        welcomeMessage() ;

        return EXIT_SUCCESS ;
}


