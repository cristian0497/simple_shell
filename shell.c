#include "header.h"
/**
 * _child - funtion to exec in child process
 * @tmp: command without path
 * @arg: arguments of command
 * @bufo: pointer to buff malloc
 * @av: name of executable
 * Return: 0
 */
int _child(char *tmp, char *arg[], char *bufo, char *av)
{
	char *_findpath, *cadena;

	if (!tmp)
		free_buf("Enter a command\n", 16, bufo, "1");
	_findpath = findpath(environ, "PATH");
	cadena = strtok(_findpath, ":");
	while (cadena)
	{
		cadena = string_rec_path(tmp, cadena);
		execve(cadena, arg, NULL);
		cadena = strtok(NULL, ":");
	}
	write(STDOUT_FILENO, av, (_strlen(av)));
	write(STDOUT_FILENO, ": 1: ", 5);
	write(STDOUT_FILENO, tmp, (_strlen(tmp)));
	free_buf(ERROR_MS, 12, bufo, NULL);
	return (0);
}
/**
 * main - funtion main of thw shell
 * @ag: void
 * @av: name of executable
 * Return: exit (0) - fail (1)EOF
 */
int main(int ag, char *av[])
{
	char *arg[] = {"/bin/sh", NULL, NULL, NULL};
	char *bufo = NULL, *tmp = NULL, *xs = "98";
	size_t buffosize;
	int child = 0, x, strrec = 0;

	(void)ag;
	do {
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, PROMPT, 6);
		signal(SIGINT, INThandler);
		x = getline(&bufo, &buffosize, stdin);
		if (x == EOF)
		{
			if (isatty(STDIN_FILENO))
			free_buf("\n", 1, bufo, "1");
			exit(0);
		}
		tmp = strtok(bufo, "\n ");
		arg[1] = strtok(NULL, "\n ");
		arg[2] = strtok(NULL, "\n ");
		strrec = string_rec_exit(bufo);
		if (strrec == 1)
		{
			if (arg[1] == NULL)
				xs = NULL;
			free_buf(NULL, 0, bufo, xs);
		}
		child = fork();
		if (child == 0)
		{
			_child(tmp, arg, bufo, av[0]);
		}
		else
			wait(NULL);
	} while (1);
	return (0);
}
