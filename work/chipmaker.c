/*
main.c -- C Test App.
*
* Copyright (C) 2012-2013, 2013 heesoon.kim <chipmaker.tistory.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; version 2 of the License.
*
* This program is distributed in the hope that it will be useful,
	* but WITHOUT ANY WARRANTY; without even the implied warranty of
	* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	* GNU General Public License for more details.
	*
	* You should have received a copy of the GNU General Public License along
	* with this program; if not, write to the Free Software Foundation, Inc.,
	*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

#define MAX_SLEEP_TIME 2

static int sigCnt[NSIG];
static volatile sig_atomic_t gotSigint = 0;

void printSigSet(FILE *of, const char *prefix, const sigset_t *sigset)
{
		int sig, cnt;
			
		cnt = 0;
				
		for(sig = 1; sig < NSIG /*32*/; sig++)
		{
			if(sigismember(sigset, sig))
			{
				cnt++;
																	
				fprintf(of, "%s%d (%s)\n", prefix, sig, strsignal(sig));
			}
		}
				
		if(cnt == 0)
			fprintf(of, "%s<empty signal set >\n", prefix);
}

// signal handler for SIGINT, SIGUSR2
void signal_handler(int sig)
{
		sigset_t pendingMask;
		// in case of SIGUSR2
		if(sig == SIGINT)
			gotSigint = 1;
		// in case of SIGINT
		else
		{
			sigCnt[sig]++;
										
			if(sigpending(&pendingMask) == -1)
			fprintf(stderr, "sigpending\n");
			// call for the print function (siganl setting info)
			printSigSet(stdout, "\t\t",  &pendingMask);			
															
			sleep(MAX_SLEEP_TIME);
		}
}

int main(int argc, char *argv[])
{
		int i;
		struct sigaction sigact;
		//sigset_t pendingMask;
				
		printf("%s: PID is %ld\n", argv[0], (long)getpid());
		//setting for the sigaction structure	
		sigact.sa_handler = signal_handler;
		sigfillset(&sigact.sa_mask);	
		//sigact.sa_flags = SA_RESETHAND | SA_RESTART;
		sigact.sa_flags = SA_RESTART;
							
		sigaction(SIGUSR2, &sigact, NULL);
		sigaction(SIGINT, &sigact, NULL);
										
		while(!gotSigint)
			continue;
											
		for(i = 1; i < NSIG; i++)
		{
			if(sigCnt[i] != 0)
			printf("%s: signal %d caught %d time%s \n", argv[0], i, sigCnt[i], (sigCnt[i] == 1) ? "" : "s");
		}
												
		exit(EXIT_SUCCESS);
													
		return 0;
}
