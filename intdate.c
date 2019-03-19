////////////////////////////////////////////////////////////////////////////////
// This File:        intdate.c
// Other Files:      sendsig.c , division.c
// Semester:         CS 354 Fall 2018
//
// Author:           Kimberly Inthavong
// Email:            inthavong@wisc.edu
// CS Login:         inthavong
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

int sec = 3; // Keeps track of the number of seconds between alarm 
int count = 0; // Keeps track number of times SIGUSR1 is caught

// This handlers catches SIGINT, printing the amount of times SIGUSR1 was called on the program
void handler_SIGINT(){
	printf("SIGINT recieved.\nSIGUSR1 was recieved %d times. Exiting now\n", count);
	exit(0);
}

// This handler catches SIGUSR1, printing a statement 
// and incrmenting the global counter 
void handler_SIGUSR1(){
	printf("SIGUSR1 caught!\n");
	// increment global counter
	count++;
}

// This handler is for SIGALRM that catches the signal and 
// prints out the current time, date, and pid
void handler_SIGALRM(){
	// Get current time and date
	time_t timeNow = time(NULL);
	struct tm *tm = localtime(&timeNow);
	
	// Print pid and current time and date 
        printf("PID: %d | Current Time: %s", getpid(), asctime(tm));
        
	// Re arm alarm
	alarm(sec);
	
	return;
}

// This program prints out pid, date and time every 3 seconds 
int main(){
	// Program description
	printf("Pid and time will be printed every 3 seconds.\n"
			"Enter ^C to end the program.\n");

	// Set up signal handler for SIGALRM
	struct sigaction act;
	memset(&act, 0, sizeof(act));
	act.sa_handler = handler_SIGALRM;
	act.sa_flags = 0;
	// Check the return type
	int checkHandler = sigaction(SIGALRM, &act, NULL);
	if (checkHandler != 0){
		printf("Error setting handler for SIGALRM");
	}
	
	// Set up signal handler for SIGUSR1
        struct sigaction useract;
        memset(&useract, 0, sizeof(useract));
        useract.sa_handler = handler_SIGUSR1;
        useract.sa_flags = 0;
        // Check the return type
        int checkHandler2 = sigaction(SIGUSR1, &useract, NULL);
        if (checkHandler2 != 0){
                printf("Error setting handler for SIGUSR1");
        }

	// Set up signal handler
        struct sigaction intact;
        memset(&intact, 0, sizeof(intact));
        intact.sa_handler = handler_SIGINT;
        intact.sa_flags = 0;
        // Check the return type
        int checkHandler3 = sigaction(SIGINT, &intact, NULL);
        if (checkHandler3 != 0){
                printf("Error setting handler for SIGUSR1");
        }

	// Set up alarm that will go off 3 seconds later 
	// causing SIGALRM to be sent
	alarm(sec);

	while(1){
	}
	return(0);
}
