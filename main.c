#include "main.h"
#include <stdio.h>
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
		simple_shell(argv[0]);
	else
		simple_shell2(argv[0], argv[1]);
	return (0);
}
