#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
/**
 * simple_shell - a custom shell
 *
 * Return: 0 if success, otherwise -1
 */
int simple_shell(void)
{
	char *buf, *argument[] = {"", NULL}, *buf2;
	pid_t proc;
	int i = 0;

	buf = malloc(sizeof(*buf) * 25);
	buf2 = malloc(sizeof(*buf2) * 25);
	if (buf == NULL || buf2 == NULL)
	{
		perror("Malloc error");
		return (-1);
	}
	proc = fork();
	if (proc == -1)
	{
		perror("fork error");
		return (-1);
	}
	if (proc == 0)
	{
		write(1, "#cisfun$ ", 9);
		read(0, buf, 25);
		while (buf[i] != '\n')
		{
			buf2[i] = buf[i];
			i++;
		}
		execve(buf2, argument, NULL);
		write(2, "./shell", 7);
		write(2, ": No such file or directory\n", 28);
	}
	else
	{
		wait(NULL);
		free(buf);
		free(buf2);
	}
	return (0);
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
