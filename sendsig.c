////////////////////////////////////////////////////////////////////////////////
// This File:        sendsig.c
// Other Files:      division.c , intdate.c
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
#include <sys/types.h>
#include <signal.h>

int main(int argc, char *argv[]){
	// Check if the number of arguments is valid;
	if (argc != 3)
	{
		printf("Usage: <signal type> <pid>\n");
		printf("%s", argv[0]);
		exit(1);
	}
	pid_t pid = atoi(argv[2]);

	if ( strcmp(argv[1], "-i")==0){
		// send a SIGINT
		kill(pid, SIGINT);
	} else if  (strcmp(argv[1], "-u")==0){
		// send a SIGUSR1
		kill(pid, SIGUSR1);
	} else {
		printf("Usage only accepts -u and -i as signal types\n");
		printf("%s\n", argv[1]);
	}

	return 0;

}
