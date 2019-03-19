////////////////////////////////////////////////////////////////////////////////
// This File:        division.c
// Other Files:      sendsig.c , intdate.c
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

int numer; // the user input first integer
int denom; // the user input second integer
int count; // number of successful operations

// This handler is for SIGINT, it prints a how many sucessful operations and ends program
void handler_SIGINT() {
        printf("\nTotal number of operations completed successfully: %d\n"
                        "The program will be terminated.\n", count);
        exit(0);
}

// This handler is for SIGFPE, it prints error statement,
// how many sucessful operations and ends program
void handler_SIGFPE() {
	printf("Error: a division by 0 operation was attempted.\n"
			"Total number of operations completed successfully: %d\n"
			"The program will be terminated.\n", count);
	exit(0);
}

// This program loops, reqesting the user enter a numerator and denomminator to determine
// its result when dividing, as well as the remainder.
// The program also keeps cound of the number of sucessful divisions.
int main() {

	// Set up signal handler for SIGFPE
        struct sigaction actFPE;
        memset(&actFPE, 0, sizeof(actFPE));
        actFPE.sa_handler = handler_SIGFPE;
        actFPE.sa_flags = 0;

        // Check the return type
        int checkHandler1 = sigaction(SIGFPE, &actFPE, NULL);
        if (checkHandler1 != 0){
                printf("Error setting handler for SIGFPE");
        }

	// Set up signal handler for SIGINT
        struct sigaction actINT;
        memset(&actINT, 0, sizeof(actINT));
        actINT.sa_handler = handler_SIGINT;
        actINT.sa_flags = 0;

        // Check the return type
        int checkHandler2 = sigaction(SIGINT, &actINT, NULL);
        if (checkHandler2 != 0){
                printf("Error setting handler for SIGINT");
        }

	while(1) {

		// Prompt user for first divider, numerator
		printf("Enter first integer: ");
		
		const int bufsize = 100;
		char buffer[bufsize];
		if(fgets(buffer, bufsize, stdin) != NULL) {
			numer = atoi(buffer);
			
			// Prompt user for second divider, denominator
			printf("Enter second integer: ");
			if(fgets(buffer, bufsize, stdin) != NULL) {
				denom = atoi(buffer);
			}
			else {
				printf("ERROR");
				exit(0);
			}
		}
		else {
			printf("ERROR");
			exit(0);
		}

		//operating the division and print the result
		int result = numer/denom;
		int remainder = numer%denom;
		count++;
		printf("%d / %d is %d with a remainder of %d\n", numer, denom, result, remainder);
	}

	return(0);

}
