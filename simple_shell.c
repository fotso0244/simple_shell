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
{printf("toto = %d\n",signum);
	
}
/**
 * simple_shell - a custom shell
 *
 */
void simple_shell(void)
{
	char *buf, *argument[] = {"", NULL};
	pid_t proc1;
	int i = 0;
	char c;
	
	signal(SIGINT, signalhandler);
	while (1)
	{
		if (buf != NULL)
			free(buf);
		buf = malloc(sizeof(*buf) * 25);
		if (buf == NULL)
			perror("Malloc error");
		write(1, "#cisfun$ ", 9);
		proc1 = fork();
		while (c != '\n')
		{
			read(0, &c, 1);
			if (c == '\n')
				break;
			buf[i] = c;
			i++;
		}
		proc1 = fork();
		if (proc1 == -1)
			perror("fork error");
		if (proc1 == 0)
		{
			execve(buf, argument, 0);
			write(1,"./shell: No such file or directory\n", 35);
		}
		else
		{
			wait(NULL);
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

	execve(str, argument, NULL);
	write(2, "./shell", 7);
	write(2, ": No such file or directory\n", 28);
}
