/*
*main.c -- C Test App.
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

#define MAX_SEND_SIGNUM 1000000 

int main(int argc, char *argv[])
{
	int i;
	pid_t pid;
	int a;

	puts("insert PID");
	scanf("%ld", &pid);
	getchar(); // fflush(stdin);
	
	printf("%s: sending signal %d to process %ld %d times\n", argv[0], SIGUSR2, (long)pid, MAX_SEND_SIGNUM);
								
	for(i = 0; i < MAX_SEND_SIGNUM; i++)
		if(kill(pid, SIGUSR2) == -1)
			fprintf(stderr, "kill error [%s]\n", strerror(errno));
									
	printf("%s: exiting\n", argv[0]);
										
	exit(EXIT_SUCCESS);
											
	return 0;
}
