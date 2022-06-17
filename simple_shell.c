#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
/**
 * signalhandler - handler of a signal
 * @signum: a signal
 */
void signalhandler(int signum)
{
	write(1, "\n", 1);
	exit(signum);	
}
/**
 * simple_shell - a custom shell
 */
void simple_shell(void)
{
	char *buf, *argument[] = {"", NULL};
	pid_t proc1;
	int i = 0, c = 1;
	char d;
	
	signal(SIGINT, signalhandler);
	while (1)
	{
		buf = malloc(sizeof(*buf) * 25);
		if (buf == NULL)
		{
			perror("Malloc error");
			exit(1);
		}
		write(1, "#cisfun$ ", 9);
		while (c != 0)
		{
			c = read(0, &d, 1);
			if (c == 0 || c == -1)
				break;
			buf[i] = d;
			i++;
		}
		proc1 = fork();
		if (proc1 == -1)
		{
			perror("fork error");
			exit(1);
		}
		if (proc1 == 0)
		{
			write(1, "\n", 1);
			execve(buf, argument, 0);
			c = 1;
			i = 0;
			write(2,"./hsh: No such file or directory\n", 33);
		}
		else
		{
			wait(NULL);
			c = 1;
			i = 0;
			free(buf);
		}
	}
}
/**
 * simple_shell2 - a custom shell
 * @str: a string
 */
void simple_shell2(char *str)
{
	char *argument[] = {"", NULL};
	pid_t proc;

	write(1, "#cisfun$ ", 9);
	proc = fork();
	if (proc == -1)
	{
		perror("fork error");
		exit(1);
	}
	if (proc == 0)
	{
		execve(str, argument, NULL);
		write(2, "./hsh", 5);
		write(2, ": No such file or directory\n", 28);
		kill(getpid(), SIGTERM);
	}
	else
	{
		wait(NULL);
		write(1, "#cisfun$ ", 9);
	}
}
