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
	int i = 0;
	char c = '\0';

	c = str[i];
	while (c != '\0')
	{
		i++;
		c = str[i];
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
	char *buf, *argument[] = {"", NULL}, *env[] = {NULL};
	pid_t proc1;
	int i = 0, c = 1, count;
	char d;
	
	signal(SIGINT, signalhandler);
	env[0] = getenv("PATH");
	env[1] = NULL;printf("%s\n", env[0]);
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
			execve(buf, argument, NULL);
			c = 1;
			i = 0;
			count = nbchar(str);
			write(2, str, count);
			write(2,": No such file or directory\n", 28);
			exit(1);
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
	char *argument[] = {"sh"};/**env[] = {"der", NULL};*/
	int count;/*char c[150] = "PATH=";*/

	argument[1] = "-c";
	argument[2] = str;
	argument[3] = NULL;
	/*env[0] = getenv("PATH");
	strcat(c, env[0]);
	env[0] = c;
	env[1] = NULL;*/
	execve("/bin/sh", argument, 0);
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
	char *str2 = NULL, *token;
	char d;
	int c = 1, i = 0, j = 0;
	pid_t proc;

	str2 = malloc(sizeof(*str2) * 50);
	for (i = 0; i < 50; i++)
		str2[i] = '\0';
	i = 0;
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
	str2[i + 1] = '\0';
	i = 0;
	while (str2[i] != '\0')
	{
		token = malloc(sizeof(*token) * nbchar(str2));
		while (str2[i] != '\n')
		{
			if (str2[i] != ' ' || str2[i + 1] != ' ')
			{
				token[j] = str2[i];
				i++;
				j++;
			}
			else
				i++;
		}
		if (j != 0)
		{
			token[j] = '\0';
			proc = fork();
			if (proc == -1)
			{
				perror("fork error");
				exit(1);
			}
			if (proc == 0)
			{
				simple_shell2(str, token);
				exit(1);
			}
			else
			{
				wait(NULL);
				free(token);
				i++;
				j = 0;
			}
		}
		else
		{
			free(token);
			i++;
		}
	}
	free(str2);
}
