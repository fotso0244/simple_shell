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
 * nbcar - number of character
 * @str: a string
 *
 * Return: a number of character
 */
int nbchar(char *str)
{
	char *s;
	int i = 0;

	s = str;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
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
 * str: name of binary file
 */
void simple_shell(char *str)
{
	char *buf, *argument[] = {"", NULL};
	pid_t proc1;
	int i = 0, c = 1, count;
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
			count = nbchar(str);
			write(2, str, count);
			write(2,": No such file or directory\n", 28);
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
 * @str2: name of binary file
 */
void simple_shell2(char *str2, char *str)
{
	char *argument[] = {"", NULL};
	int count;

	/*write(1, "#cisfun$ ", 9);*/
	execve(str, argument, NULL);
	count = nbchar(str2);
	write(2, str2, count);
	write(2, ": No such file or directory\n", 28);
}
/**
 * simple_shell3 - a non-interactive shell
 * @str: name of program
 */
void simple_shell3(char *str)
{
	char *str2, *token;
	char d;
	int c = 1, i = 0;
	pid_t proc;

	str2 = malloc(sizeof(*str2) * 25);
	if (str2 == NULL)
	{
		perror("malloc error");
		exit(1);
	}
	while (c != 0)
	{
		c = read(0, &d, 1);
		if (c == 0)
			break;
		str2[i] = d;
		i++;
	}
	write(1, "#cisfun$ ", 9);
	proc = fork();
	if (proc == -1)
	{
		perror("fork error");
		exit(1);
	}
	if (proc == 0)
	{
		token = strtok(str2, "\n");
		while (token != NULL)
		{
			simple_shell2(str, token);
			token = strtok(NULL, "\n");
			if (token != NULL)
				write(1, "\n#cisfun$ ", 10);
		}
		exit(1);
	}
	else
	{
		wait(NULL);
		write(1, "#cisfun$ ", 9);
	}
}
