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
 * simple - a custom shell
 * @argc: number of arguments
 * @argv: list of arguments
 *
 * Return: 0 if success, otherwise -1
 */
int simple_shell()
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
void simple_shell2(char *str)
{
	char *argument[] = {"", NULL};

	execve(str, argument, NULL);
	write(2, "./shell", 7);
	write(2, ": No such file or directory\n", 28);
}
/**
 * main - a simple shell
 * @argc: number of arguments
 * @argv: list of argument
 *
 * Return: always 0
 */
int main(int argc, char **argv)
{
	if (argc == 1)
		simple_shell();
	else
		simple_shell2(argv[1]);
	return (0);
}
