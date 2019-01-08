#include "op.h"

int				check_champs_nb(t_vm *vm)
{
	t_champ		*champ;
	int			i;
	int			bol;

	i = 1;
	bol = 0;
	while (i <= vm->champ_nb)
	{
		champ = vm->champ;
		while (champ)
		{
			if (bol == 1 && champ->id == -i)
				return (0);
			if (champ->id == -i)
				bol = 1;
			champ = champ->next;
		}
		bol = 0;
		i++;
	}
	return (1);
}

int		introduce_contestants(t_vm *vm)
{
	t_champ			*champ;
	int				i;

	i = -1;
	if (vm->n)
		if (!check_champs_nb(vm))
			return (ft_printf(N_ERROR, MAX_PLAYERS));
	ft_printf("Introducing contestants...");
	while (-i <= vm->champ_nb)
	{
		champ = vm->champ;
		while (champ)
		{
			if (i == champ->id)
			{
				ft_printf("\n* Player %d, weighing %d bytes, \"%s\" (\"%s\") !",
					(champ->id * -1), champ->head->prog_size,
					champ->head->prog_name, champ->head->comment);
				break ;
			}
			champ = champ->next;
		}
		i--;
	}
	return (0);
}




