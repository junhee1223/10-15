#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

void clock_tick(int signo) {
	printf("\r%ld", time(NULL));
	alarm(1);
}
void handler_init(int signo) {
}
int main(void) {
	int pid;

	setvbuf(stdout, NULL, _IONBF, BUFSIZ);
	printf("\e[2J\e[H");

	if(signal(SIGALRM, clock_tick) == SIG_ERR)
		perror("cannot catch SIGALRM");

	if(signal(SIGINT, handler_init) == SIG_ERR)
		perror("cannot catch SIGINT");
	
	clock_tick(-1); /* 1~64제외한 수 넣어도 괜찮다.*/

	for(;;)
		pause();

	return(0);
}

