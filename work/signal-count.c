#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>

static int sigcount1, sigcount2;

static void sig_usr(int signo) {

	if(signo == SIGUSR1) {
		sigcount1++;
		printf("%d, SIGUSR1\n", sigcount1);
	}
	else if(signo == SIGUSR2) {
		sigcount2++;
		printf("%d, SIGUSR2\n", sigcount2);
	}
		
}

int main(void) {
	if(!fork()) {
		
		int ppid;
		int i;

		ppid = getppid();

		for(i = 0; i < 5; i++) {
			kill(ppid, SIGUSR1);
			kill(ppid, SIGUSR2);

			sleep(3);
		}

		printf("child exiting\n");

		exit(0);
	}
	else{
		if(signal(SIGUSR1, sig_usr) == SIG_ERR)
			perror("cannot catch SIGUSR1\n");
		if(signal(SIGUSR2, sig_usr) == SIG_ERR)
			perror("cannot catch SIGUSR2\n");

		wait(NULL);
	}
		
	return 0;
}




