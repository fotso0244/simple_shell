#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
/**
 * main - a simple shell
 * @argc: number of arguments
 * @argv: list of argument
 *
 * Return: always 0
 */
int main(int argc, char **argv, char *envp[])
{
	int status = 0;

	if (argc == 1 && isatty(0))
		simple_shell(argv[0]);
	else
		if (!isatty(0))
		{
			status = simple_shell3(argv[0], status, envp);
		}
		else
			simple_shell2(argv[0], argv[1], envp);
	if (status == 512)
		status = 2;
	if (status == 6 || status == 134)
	{
		status = 0;
		exit(0);
	}
	return (status);
}
