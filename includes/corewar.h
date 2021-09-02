/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:05:27 by edjubert          #+#    #+#             */
/*   Updated: 2019/08/11 15:10:42 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "op.h"
# include "fcntl.h"
# include <ncurses.h>

# define COLOR_LIGHT_BLUE 8
# define COLOR_LIGHT_GREEN 9
# define COLOR_LIGHT_CYAN 10
# define COLOR_LIGHT_RED 11

# define ERR0 "Usage: ./corewar\n"

typedef struct		s_type
{
	unsigned int	data;
	char			flag;
}					t_type;

typedef struct		s_proc
{
	unsigned char	carry : 1;
	short			pc;
	short			start;
	int				live;
	int				cycle;
	unsigned long	player;
	unsigned int	*reg;
	struct s_proc	*next;
}					t_proc;

typedef	struct		s_order
{
	unsigned long	num;
	char			*file;
}					t_order;

typedef struct		s_option
{
	int				players;
	int				dump;
	int				dsize;
	int				visu;
	int				stealth;
	t_order			p[MAX_PLAYERS];
}					t_option;

typedef struct		s_champ
{
	int				flen;
	int				prog_len;
	int				livecurrent;
	int				lives;
	unsigned int	playerno;
	unsigned long	num;
	unsigned char	*cor;
	unsigned char	*code;
	char			*title;
	char			*comment;
	struct s_champ	*next;
}					t_champ;

typedef struct		s_color
{
	int				opcode;
	int				lastchamp;
	int				champ;
	int				time;
	int				t;
}					t_color;

typedef struct		s_vm
{
	int				cyclecheck;
	int				cycles;
	int				checks;
	int				output;
	int				first_print;
	int				nb_champ;
	int				pnum;
	int				breakdown[MAX_PLAYERS];
	int				breakdown_old[MAX_PLAYERS];
	int				tot_live;
	int				tot_live_old;
	unsigned long	last_live;
	struct s_option	opt;
	struct s_proc	*proc;
	struct s_champ	*champs;
	struct s_color	colors[MEM_SIZE];
	unsigned char	arena[MEM_SIZE];
}					t_vm;

typedef struct		s_op
{
	char			*name;
	int				num_args;
	t_arg_type		args[3];
	char			opcode;
	int				num_cycles;
	char			*desc;
	int				args_mask;
	int				carry;
}					t_op;

void				op_zjmp(t_vm *vm, t_proc **proc, t_type args[]);
void				op_aff(t_vm *vm, t_proc **proc, t_type args[]);
void				op_ld(t_vm *vm, t_proc **proc, t_type args[]);
void				op_lld(t_vm *vm, t_proc **proc, t_type args[]);
void				op_live(t_vm *vm, t_proc **proc, t_type args[]);
void				op_ldi(t_vm *vm, t_proc **proc, t_type args[]);
void				op_lldi(t_vm *vm, t_proc **proc, t_type args[]);
void				op_add(t_vm *vm, t_proc **proc, t_type args[]);
void				op_sub(t_vm *vm, t_proc **proc, t_type args[]);
void				op_and(t_vm *vm, t_proc **proc, t_type args[]);
void				op_or(t_vm *vm, t_proc **proc, t_type args[]);
void				op_xor(t_vm *vm, t_proc **proc, t_type args[]);
void				op_fork(t_vm *vm, t_proc **proc, t_type args[]);
void				op_lfork(t_vm *vm, t_proc **proc, t_type args[]);
void				op_st(t_vm *vm, t_proc **proc, t_type args[]);
void				op_sti(t_vm *vm, t_proc **proc, t_type args[]);
void				fill_32bit(uint32_t *arg, short index,
						unsigned char *arena);
void				fill_16bit(uint32_t *arg, short index,
						unsigned char *arena);
int					op_invalid_mask(t_vm *vm, t_proc *proc, t_op instruct);
int					regchk(t_type args[], t_op instruct);
void				op_exec(t_vm *vm, t_proc *proc, t_op instruct);

int					player_taken(t_option *opt, unsigned long player,
						char *file);
void				args_nchampion(t_vm *vm, char **av, int *i, int *j);
void				args_champion(t_vm *vm, char *av, int *j);
void				args_dump(t_vm *vm, char **av, int *i, t_option *opt);
void				vm_args(t_vm *vm, int ac, char **av, int i);

void				push_champ(t_champ **head, t_champ *new);
t_champ				*init_heads(int ind[3], unsigned long num);
void				parse_headers(t_champ **head, int ind[3],
						unsigned long num);
void				parse_instructions(t_champ **head, t_champ *new,
						int ind[3], unsigned char *tmp);

void				init_colors(t_color colors[MEM_SIZE]);
void				push_color(t_color colors[MEM_SIZE], int index,
						int length, int champ);

void				root_print(t_vm *vm, t_proc **proces, int i[4],
						WINDOW *arena);
void				print_arena(t_vm *vm, WINDOW *arena);
void				how_to_win_lines(t_vm *vm, WINDOW *arena, WINDOW *info,
						int *i);
void				vm_fight(t_vm *vm, int i, int paused);
void				vm_endfight(t_vm *vm, WINDOW **arena, WINDOW **info);

void				init_regs(unsigned int *regs);
void				init_arena(t_vm *vm, t_champ **head, t_proc **procs,
						int i);
void				vm_init(t_vm *vm);
void				vm_init_new(t_proc **proc, unsigned int pn,
						unsigned long num, int i);

void				vm_read(int fd, t_champ *new, int i);
void				vm_finish_them(t_champ **champs, t_proc **procs);
void				vm_error(int error, char *str);

t_op				get_op_tab(int nb);

int					check_operations(unsigned char ocp, int opcode);
int					check_stildilldi(unsigned char ocp, int opcode);
int					check_ldstlld(unsigned char ocp, int opcode);

void				check_defines(void);

void				init_colors(t_color colors[MEM_SIZE]);
void				init_ncurses(WINDOW **arena, WINDOW **info);
void				get_info(t_vm *vm, WINDOW *info,
						int cycles);
int					get_color_arena(t_color colors[MEM_SIZE], int i[4]);
void				delete_color(t_color **colors, t_color *to_del);
void				parse_champions(t_vm *vm, t_order list[MAX_PLAYERS]);

void				loop_procs(t_vm *vm, t_proc **procs, t_proc *prev,
						t_proc *tmp);
void				baseball_bat(t_vm *vm, t_proc **procs);
t_proc				*malloc_proc(void);
void				push_proc_front(t_proc **procs, t_proc *new);

void				op_exec_dir(t_vm *vm, short *index, t_type *arg,
						t_op instruct);
void				op_exec_ind(t_vm *vm, short *index, t_type *arg);
void				op_exec_reg(t_vm *vm, short *index, t_type *arg);

int					help_encoded(t_op *instruction, char byte[3],
						int i, int *test);
int					get_size_encoded(unsigned char *instruct,
						t_op *instruction);
int					get_size(unsigned char *tmp, t_op *instruction);
void				get_instructions(t_vm *vm, t_proc **pc);

short				get_index(t_proc *proc, unsigned int arg);
void				vm_dump(t_vm *vm);
void				do_check_overflow(t_vm *vm, int overflow);
void				check_overheat(t_vm *vm, int *i);
void				print_old_breakdown(t_vm *vm, WINDOW *info, int n);
void				get_live_breakdown(t_vm *vm, int n, WINDOW *info);

void				vm_event(t_vm *vm, WINDOW *arena, WINDOW *info,
						int *paused);

void				get_live_breakdown(t_vm *vm, int n, WINDOW *info);
void				print_old_breakdown(t_vm *vm, WINDOW *info, int n);

# define P1 "usage:\tcorewar [-dhnpv] [[number] champion.cor ...]\n"
# define P2 "\t-d | --dump [number]\tdump vm at specified cycle"
# define P3 "\n\t-v | --visual\t\tncurses visual mode for corewar\n"
# define P4 "\t-h | --help\t\tdisplay usage\n"
# define P5 "\t-n | --number [number]\tset next champion number\n"
# define P6 "\t-p | --print\t\tprint aff and live data, default is off\n"

# define USGMSG P1 P2 P3 P4 P5 P6

#endif
