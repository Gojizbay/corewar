#include "op.h"

void	ft_error(char *s)
{
	char *prog_name;

	prog_name = g_arg.prog_name;
	write(STDERR_FILENO, prog_name, ft_strlen(prog_name));
	write(STDERR_FILENO, ":\t", 2);
	perror(s);
	exit(EXIT_FAILURE);
}
