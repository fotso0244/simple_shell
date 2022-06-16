#include "main.h"
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
