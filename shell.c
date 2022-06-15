#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
/**
 * main - a custom shell
 *
 * Return: always 0
 */
int main(int argc, char** argv)
{
	char *buf, *argument[] = {"", NULL}, *buf2;
	pid_t proc;
	int i;

	if (argc != 1)
		return (1);
	buf = malloc(sizeof(*buf) * 25);
	buf2 = malloc(sizeof(*buf2) * 25);
	proc = fork();
	if (proc == -1)
	{
		perror("fork error");
		return (1);
	}
	if(proc == 0)
	{
		write(1, "#cisfun$ ", 9);
		read(0, buf, 25);
		i = 0;
		while (buf[i] != '\n')
		{
			buf2[i] = buf[i];
			i++;
		}
		execve(buf2, argument, NULL);
		write(2, argv[0], 7);
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
