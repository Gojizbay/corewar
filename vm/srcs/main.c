#include "op.h"

/*
 * [1] Revoir la gestion des flags :
 * ./corewwar zork.cor -v 31 doit fonctionner ...
 * utiliser des bit fields pour plus de proprete
 *
 * [2] Pas d'interaction entre -d et -n si ce n'est
 * que -n domine les autres options
 *
 * [3] Revoir get_champs aussi
 *
 * [4] ameliorer gestion d'erreur : retour pertinent et sur STDERR
 *
 */

t_arg	g_arg = {NULL, {NULL, NULL, NULL, NULL}, {-1, -2, -3, -4}, 0, 0, 0};

int		main(int ac, char **av)
{
	int		i;
	t_vm	*vm;

	if (ac == 1)
		return (print_man(vm));
	if (!(vm = init_vm()))
		ft_error("init_vm() failed");
	get_arg(ac, av, vm);
	get_champs(vm);
	/*
	if (introduce_contestants(vm))
		return (free_all(vm));
	if (launch_vm(vm) == vm->dump && vm->dump >= 0)
		print_dump(vm);
	else
		print_result(vm);
		*/
	return (free_all(vm));
}
