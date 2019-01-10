/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   op.h                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/21 17:43:20 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/10 19:27:41 by bodibon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef OP_VM_H
# define OP_VM_H

# include "../../libft/libft.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

/*
** coucou
*/

typedef char	t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4

/*
** binary parsing macros
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define MAGIC					0xea83f3

/*
** proclist macros
*/

# define PROC_NB				800

/*
** error messages
*/

# define N_ERR	"Invalid player number given\n"
# define N_US	"\tUsage: ./corewar -n [1-%d] file.cor (for each contestant)\n"
# define N_MESSAGE N_ERR N_US
# define FILE_ERROR		"Can't read source file %s\n"

typedef struct			s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}						t_header;

typedef struct			s_opmodvm
{
	int					paramnb;
	char				paramtype[MAX_ARGS_NUMBER];
	int					cycles;
	int					ocp;
	int					carry;
	int					dirsize;
}						t_opmodvm;

typedef struct			s_op
{
	char				*label;
	int					index;
	int					size;
	unsigned char		type;
	int					ocp;
	int					pcount;
	int					param[3];
	int					param_size[3];
	int					param_val[3];
}						t_op;

typedef struct			s_proc
{
	int					id;
	int					type;
	char				paramnb;
	unsigned char		ocp;
	char				paramtype[MAX_ARGS_NUMBER];
	int					paramval[MAX_ARGS_NUMBER];
	size_t				size;
	int					carry;
	int					cycles_exec;
	int					pc;
	int					regs[REG_NUMBER - 1];
	int					lives;
	int					lastlive;
}						t_proc;

typedef struct			s_proctab
{
	t_proc				*proc[PROC_NB];
	int					proclen;
	int					i;
	struct s_proctab	*prev;
	struct s_proctab	*next;
}						t_proctab;

typedef struct			s_champ
{
	int					id;
	int					mempos;
	t_header			*head;
	int					lastlive;
	int					lives;
	struct s_champ		*next;
}						t_champ;

struct					s_win;

typedef struct			s_vm
{
	unsigned char		mem[MEM_SIZE];
	int					champ_nb;
	t_proctab			*proclist;
	t_champ				*champ;
	int					cycle;
	int					lives;
	int					procnb;
	int					ctd;
	int					check;
	int					dump;
	char				vis;
	char				aff;
	char				verbose;
	char				n;
	struct s_win		*win;
}						t_vm;

/*
**launch vm
*/
int						check_param(t_op *op, char *param, char **label);
int						options(int ac, char **av, t_vm *vm);
int						print_man(t_vm *vm);
int						champ_error(char *file);
int						introduce_contestants(t_vm *vm);
/*
**get the party going
*/
int						launch_vm(t_vm *vm);
t_opmodvm				*get_op_tab_vm(void);
int						launch_proc(t_proc *proc, t_vm *vm, int procnb);
int						exec_proc(t_proc *proc, t_vm *vm, int procnb);
int						ft_live(t_proc *proc, t_vm *vm);
int						ft_ld(t_proc *proc, t_vm *vm);
int						ft_st(t_proc *proc, t_vm *vm);
int						ft_add(t_proc *proc, t_vm *vm);
int						ft_sub(t_proc *proc, t_vm *vm);
int						ft_and(t_proc *proc, t_vm *vm);
int						ft_or(t_proc *proc, t_vm *vm);
int						ft_xor(t_proc *proc, t_vm *vm);
int						ft_zjmp(t_proc *proc, t_vm *vm);
int						ft_ldi(t_proc *proc, t_vm *vm);
int						ft_sti(t_proc *proc, t_vm *vm);
int						ft_fork(t_proc *proc, t_vm *vm);
int						ft_lld(t_proc *proc, t_vm *vm);
int						ft_lldi(t_proc *proc, t_vm *vm);
int						ft_lfork(t_proc *proc, t_vm *vm);
int						ft_aff(t_proc *proc, t_vm *vm);
int						manage_opc(t_proc *proc, int i, t_vm *vm);
t_proc					*init_proc(void);
t_proctab				*init_proctab(t_proctab *prev);
size_t					calc_size(t_proc *proc);
int						fill_paramval(t_proc *proc, t_vm *vm);
int						update_proclist(t_proc *proc, t_proctab *cycles);
int						manage_nega(t_arg_type type, int dirsize, int val);
int						check_ocp(t_proc *proc);
int						refill_proc(t_proc *proc, t_vm *vm);
void					fill_son(t_proc *son, t_proc *proc, t_vm *vm, int pc);
/*
**mem tools
*/
int						read_mem(unsigned char *mem, int start, size_t bytes);
void					write_mem(unsigned char *mem, int start, size_t bytes,
						int val);
/*
**proc tools
*/
t_proc					*init_proc(void);
int						refill_proc(t_proc *proc, t_vm *vm);
int						fill_proc(t_proc *proc, t_vm *vm, int id, int mempos);
void					free_proc(t_proc **proc, t_vm *vm);
int						check_proc_to_exec(t_vm *vm);
int						check_proc_lives(t_vm *vm);
/*
**champ tools
*/
t_header				*init_head(void);
t_champ					*init_champ(void);
int						get_champs(int ac, int i, t_vm *vm, char **av);
int						check_champs_nb(t_vm *vm);
/*
**verbose tools
*/
void					verb_proc_lives(t_vm *vm, t_proctab *start, int i);
void					verb_cycle(t_vm *vm, int mode);
void					verbose_ope(int val1, int val2, t_proc *proc, t_vm *vm);
void					verb_procnb(t_vm *vm, int procnb, size_t procsize);
void					verb_live(int val1, int val2, t_proc *proc);
void					verb_ld(int val1, int val2, t_proc *proc);
void					verb_st(int val1, int val2, t_proc *proc);
void					verb_add(int val1, int val2, t_proc *proc);
void					verb_sub(int val1, int val2, t_proc *proc);
void					verb_and(int val1, int val2, t_proc *proc);
void					verb_or(int val1, int val2, t_proc *proc);
void					verb_xor(int val1, int val2, t_proc *proc);
void					verb_zjmp(int val1, int val2, t_proc *proc);
void					verb_ldi(int val1, int val2, t_proc *proc);
void					verb_sti(int val1, int val2, t_proc *proc);
void					verb_fork(int val1, int val2, t_proc *proc);
void					verb_lld(int val1, int val2, t_proc *proc);
void					verb_lldi(int val1, int val2, t_proc *proc);
void					verb_lfork(int val1, int val2, t_proc *proc);
void					verb_aff(int val1, int val2, t_proc *proc);
/*
**visualizer
*/
# include <ncurses.h>

# define WRAP_W 303
# define WRAP_H 72
# define WRAP_SX 0
# define WRAP_SY 0

# define MATRIX_W 240
# define MATRIX_H 70
# define MATRIX_SX 1
# define MATRIX_SY 1

# define INFO_W 60
# define INFO_H 70
# define INFO_SX 242
# define INFO_SY 1

typedef struct			s_win
{
	WINDOW				*wrap;
	WINDOW				*matrix;
	WINDOW				*info;
}						t_win;

t_win					*init_windows(void);
void					start_visualizer(t_vm *vm);
void					close_windows(t_win *win);
char					nibble_to_char(unsigned char ch);
void					display_memory(t_vm *vm);
void					write_matrix(WINDOW *matrix, int id,
		unsigned int pos, unsigned char c);
void					write_matrix2(WINDOW *matrix, int start, int val,
		int proc_id);
void					update_visu(t_vm *vm);

/*
**this is the end
*/
int						free_all(t_vm *vm);
void					print_result(t_vm *vm);
void					print_dump(t_vm *vm);

#endif
