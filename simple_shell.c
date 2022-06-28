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
 *
 * Return: 0
 */
void _strtok(char *token, char *str, char delim);
int simple_shell2(char *str2, char *str, char **envp)
{
	char *argument[] = {"sh"}, *token;/**env[] = {"der", NULL};*/
	int count, i;/*char c[150] = "PATH=";*/

	argument[1] = "-c";
	if (strcmp(str, "env") != 0)
		argument[2] = str;
	else
	{
		for (i = 0; envp[i] != NULL; i++)
		{token = malloc(sizeof(*token) * 20);
			_strtok(token, envp[i], '=');
			if (strcmp(token, "LS_COLORS") != 0)
			{
				write(1, envp[i], (int)strlen(envp[i]));
				write(1, "\n", 1);
				free(token);
			}
		}
		return (0);
	}
	argument[3] = NULL;
	/*env[0] = getenv("PATH");
	strcat(c, env[0]);
	env[0] = c;
	env[1] = NULL;*/
	execve("/bin/sh", argument, 0);
	count = nbchar(str2);
	write(2, str2, count);
	write(2, ": No such file or directory\n", 28);
	return (0);
}
void _strtok(char *token, char *str, char delim)
{
	int i = 0;

	while (str[i] != delim && str[i] != '\0' && str != NULL)
	{
		token[i] = str[i];
		i++;
	}
	if (i == 0)
	{
		free(token);
		token = NULL;
	}
	else
		token[i] = '\0';
}
/**
 * If_cmd_exist - checks if command exist in PATH
 * @cmd: a command
 *
 * Return: 1 if command exist, otherwise 0
 */
int If_cmd_exist(char *cmd)
{
	char *path = getenv("PATH"), *token1, *token3, *token2;
	struct stat stats;
	int res = 0;

	path[nbchar(path)] = '\0';
	token3 = path;
	token2 = malloc(sizeof(*token2) * 20);
	token1 = malloc(sizeof(*token1) * 10);
	_strtok(token2, token3, ':');
	_strtok(token1, cmd, ' ');
	while(token2 != NULL)
	{
		strcat(token2, "/");
		strcat(token2, token1);
		if (stat(token2, &stats) == -1)
		{
			res = 0;
			token3 += (nbchar(token2) - nbchar(token1));
			if (token3[0] == 'P')
			{
				free(token1);
				free(token2);
				return (0);
			}
			free(token2);
			token2= malloc(sizeof(*token2) * 20);
			_strtok(token2, token3, ':');
		}
		else
		{
			res = 1;
			free(token2);
			free(token1);
			return (1);
		}
	}
	return (res);
}
/**
 * simple_shell3 - a non-interactive shell
 * @str: name of program
 *
 * Return: an int
 */
int simple_shell3(char *str, int status, char *envp[])
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
			if ((token[0] == '.' && token[1] == '/') || (strcmp(token, "env") == 0) || (token[0] == '.' && token[1] == '.' && token[2] == '/') || token[0] == '/' || strcmp(token, "exit") == 0)
				goto process;
			if (If_cmd_exist(token) == 1)
			{
process:
				proc = fork();
				if (proc == -1)
				{
					perror("fork error");
					exit(1);
				}
				if (proc == 0)
				{
					simple_shell2(str, token, envp);
				}
				else
				{
					if (strcmp(token, "exit") != 0)
						waitpid(proc, &status, 0);
					else
						wait(NULL);
					free(token);
					i++;
					j = 0;
				}
			}
			else
			{
				write(2, "./hsh: 1:", 10);
			       write(2, token, nbchar(token));
			       write(2, ": not found\n", 12);
			       free(token);
			       i++;
			}	       
		}
		else
		{
			free(token);
			i++;
		}
	}
	free(str2);
	return (status);
}
