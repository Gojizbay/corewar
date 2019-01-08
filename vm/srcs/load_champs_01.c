#include "op.h"

header_t	*init_head(void)
{
	header_t	*head;

	if (!(head = ft_memalloc(sizeof(header_t))))
		return (NULL);
	return (head);
}

t_champ		*init_champ(void)
{
	t_champ	*champ;

	if (!(champ = ft_memalloc(sizeof(t_champ))))
		return (NULL);
	champ->head = init_head();
	return (champ);
}

void		get_champs(t_vm *vm)
{
	t_champ		*champ;
	int			i;

	champ = vm->champ;
	i = 0;
	while (g_arg.file[i])
	{
		champ->id = g_arg.player_id[i];
		fill_champ(g_arg.file[i], champ, vm);
		i++;
		if (i < MAX_PLAYERS && g_arg.file[i])
		{	
			if (!(champ = init_champ()))
				ft_error("init_champ() failed");
			vm->champ->next = champ;
		}
	}
}

void		fill_champ(char *file, t_champ *champ, t_vm *vm)
{
	int			fd;

	if ((fd = open(file, O_RDONLY)) < 0)
		ft_error("fill_champ() failed");
	champ->mempos = (MEM_SIZE / vm->champ_nb) * (-champ->id - 1);
	if (!read_champ(fd, champ, vm))
		ft_error("read_champ() failed");
	close(fd);
}

int			read_champ(int fd, t_champ *champ, t_vm *vm)
{
	unsigned char	bf[0xb3a];
	int				i;
	int				j;
	int				n;

	j = 0;
	if ((n = read(fd, bf, sizeof(bf))) >= 0)
	{
		if ((champ->head->magic = read_mem(bf, 3, 4)) != COREWAR_EXEC_MAGIC)
			ft_error("wrong magic number");
		champ->head->prog_size = read_mem(bf, 0x88, 4);
		ft_memcpy(champ->head->prog_name, bf + 4, PROG_NAME_LENGTH + 1);
		ft_memcpy(champ->head->comment, bf + 12 + PROG_NAME_LENGTH,
				COMMENT_LENGTH + 1);
		i = 0x890;
		while (i < 0xb3a)
			vm->mem[j++ + champ->mempos] = bf[i++];
	}
	else
		return (0);
	if (n == 0)
		ft_error("champion is too small");
	if ((n = read(fd, bf, sizeof(bf))) > 0)
		ft_error("champion is too large");
	return (1);
}
