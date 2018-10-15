#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

static void sig_usr(int signo) {
	if(signo == SIGUSR1)
		printf("SIGUSR1 received from its child\n");
	else if(signo == SIGUSR2)
		printf("SIGUSR2 received from its child\n");
	/*
	   else if(signo == SIGINT)
			printf("SIGINT received from its child \n);
	*/
}

int main(void) {
	if(!fork()) {
		int ppid;
		
		ppid = getppid();
		kill(ppid, SIGUSR1);
		kill(ppid, SIGUSR2);

		exit(0);
	}
	else {
		if(signal(SIGUSR1, sig_usr) == SIG_ERR)
			perror("cannot catch SIGUSR1\n");
		if(signal(SIGUSR2, sig_usr) == SIG_ERR)
			perror("cannot catch SIGUSR2\n");

		wait(NULL);
	}
	return 0;
}
