/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2018/12/19 11:02:09 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>

enum e_bool		{FALSE, TRUE};
enum e_flags	{DUMP = 1, AFF = 2, VERB = 4, VISU = 8};
enum e_verb		{LIV = 1, CYC = 2, OP = 4, DTH = 8, MOV = 16};

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
#define MEM_SIZE				(4*1024)
#define IDX_MOD					(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

#define COMMENT_CHAR			'#'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','

#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

#define REG_NUMBER				16

#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10

typedef char	t_arg_type;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

# define ID_PROC				cycles->proc[i]->regs[0]
# define NEXT_PC				(cycles->proc[i]->pc + cycles->proc[i]->size) % MEM_SIZE
# define T_ID_PROC				tmp->proc[i]->regs[0]
# define T_NEXT_PC				(tmp->proc[i]->pc + tmp->proc[i]->size) % MEM_SIZE

# define PROC_NB				800
# define MAX_CHAMP_NB			4 /* delete this one */

# define N_ERROR				"Invalid player number given\n\ti\
			Usage: ./corewar -n [1-%d] file.cor (for each contestant)\n"
# define FILE_ERROR				"Can't read source file %s\n"

typedef struct		s_arg
{
	char			*prog_name;
	char			*file[MAX_PLAYERS];
	int				player_id[MAX_PLAYERS];
	int				flags;
	int				verb_lvl;
	unsigned int	dump_cycle;
}					t_arg;

extern t_arg		g_arg;

typedef struct		header_s
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					header_t;

typedef struct		s_opmod
{
	char			*opname;
	int				paramnb;
	int				paramtype[MAX_ARGS_NUMBER];
	int				opcode;
	int				cycles;
	char			*longname;
	int				ocp;
	int				dirsize;
}					t_opmod;

typedef struct		s_opmodvm
{
	int				paramnb;
	char			paramtype[MAX_ARGS_NUMBER];
	int				cycles;
	int				ocp;
	int				carry;
	int				dirsize;
}					t_opmodvm;

typedef struct		s_op
{
	char			*label;
	int				index;
	int				size;
	unsigned char	type;
	int				ocp;
	int				pcount;
	int				param[3];
	int				param_size[3];
	int				param_val[3];
}					t_op;

typedef struct		s_proc
{
	char			type;
	char			paramnb;
	unsigned char	opcode;
	char			paramtype[MAX_ARGS_NUMBER];
	int				paramval[MAX_ARGS_NUMBER];
	size_t			size;
	int				carry;
	int				cycles_exec;
	int				pc;
	int				regs[REG_NUMBER - 1];
	int				lives;
	int				lastlive;
}					t_proc;

typedef struct		s_cycles
{
	t_proc			*proc[PROC_NB];
	int				proclen;
	int				i;
	struct s_cycles	*prev;
	struct s_cycles	*next;
}					t_cycles;

typedef struct		s_champ
{
	int				id;
	int				mempos;
	header_t		*head;
	int				lastlive;
	int				lives;
	struct s_champ	*next;
}					t_champ;

/* rename champ to champ_list */

typedef struct		s_vm
{
	unsigned char	mem[MEM_SIZE];
	int				champ_nb;
	t_cycles		*proclist;
	t_champ			*champ;
	int				cycle;
	int				lives;
	int				procnb;
	int				ctd;
	int				check;
	int				dump;
	char			vis;
	char			aff;
	char			verbose;
	char			n;
}					t_vm;

t_vm				*init_vm(void);
void				get_arg(int ac, char *av[], t_vm *vm);
void				get_champs(t_vm *vm);
void				fill_champ(char *file, t_champ *champ, t_vm *vm);
int					read_champ(int fd, t_champ *champ, t_vm *vm);

void				ft_error(char *s);

/* launch vm */
int					check_param(t_op *op, char *param, char **label);
int					options(int ac, char **av, t_vm *vm);
int					print_man(t_vm *vm);
int					introduce_contestants(t_vm *vm);
/* get the party going */
int					launch_vm(t_vm *vm);
t_opmodvm			*get_op_tab_vm(void);
int					launch_proc(t_proc *proc, t_vm *vm, int procnb);
int					exec_proc(t_proc *proc, t_vm *vm, int procnb);
int					ft_live(t_proc *proc, t_vm *vm);
int					ft_ld(t_proc *proc, t_vm *vm);
int					ft_st(t_proc *proc, t_vm *vm);
int					ft_add(t_proc *proc, t_vm *vm);
int					ft_sub(t_proc *proc, t_vm *vm);
int					ft_and(t_proc *proc, t_vm *vm);
int					ft_or(t_proc *proc, t_vm *vm);
int					ft_xor(t_proc *proc, t_vm *vm);
int					ft_zjmp(t_proc *proc, t_vm *vm);
int					ft_ldi(t_proc *proc, t_vm *vm);
int					ft_sti(t_proc *proc, t_vm *vm);
int					ft_fork(t_proc *proc, t_vm *vm);
int					ft_lld(t_proc *proc, t_vm *vm);
int					ft_lldi(t_proc *proc, t_vm *vm);
int					ft_lfork(t_proc *proc, t_vm *vm);
int					ft_aff(t_proc *proc, t_vm *vm);
int					manage_opc(t_proc *proc, int i, t_vm *vm);
t_proc				*init_proc(void);
t_cycles			*init_cycles(t_cycles *prev);
size_t				calc_size(t_proc *proc);
int					fill_paramval(t_proc *proc, t_vm *vm);
int					update_proclist(t_proc *proc, t_cycles *cycles);
int					manage_nega(t_arg_type type, int dirsize, int val);
int					check_ocp(t_proc *proc);
int					refill_proc(t_proc *proc, t_vm *vm);
/* mem tools */
int					read_mem(unsigned char *mem, int start, size_t bytes);
void				write_mem(unsigned char *mem, int start, size_t bytes,
					int val);
/* proc tools */
t_proc				*init_proc(void);
int					refill_proc(t_proc *proc, t_vm *vm);
int					fill_proc(t_proc *proc, t_vm *vm, int id, int mempos);
void				free_proc(t_proc **proc, t_vm *vm);
/* champ tools */
header_t			*init_head(void);
t_champ				*init_champ(void);
//int					get_champs(int ac, int i, t_vm *vm, char **av);
int					check_champs_nb(t_vm *vm);
/* verbose tools */
void				verb_proc_lives(t_vm *vm, t_cycles *start, int i);
void				verb_cycle(t_vm *vm, int mode);
/* this is the end */
int					free_all(t_vm *vm);
void				print_result(t_vm *vm);
void				print_dump(t_vm *vm);
