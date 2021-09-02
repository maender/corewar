/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:06:39 by edjubert          #+#    #+#             */
/*   Updated: 2019/08/10 15:46:58 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include "op.h"

enum {
	command = 1,
	string,
	label,
	instruction,
	separator_operator,
	param,
	endline
};

# define ERR_CMD_UNKNOWN		1
# define ERR_NAME_FORMAT		2
# define ERR_NAME_TOO_LONG		3
# define ERR_COMMENT_TOO_LONG	4
# define ERR_CHAR_NOT_VALID		5
# define ERR_INVALID_PARAM		6
# define ERR_CANT_OPEN_FILE		7
# define ERR_SYNTAX				8
# define ERR_LABEL_UNKNOWN		9
# define ERR_BAD_INSTRUCTION	10
# define ERR_LEXICAL			11
# define ERR_NUM_PARAM			12
# define ERR_COMMAND			13
# define ERR_ENDLINE			14
# define ERR_FILE_EXT			15

# define OP_PRINT	(1 << 0)
# define OP_LABELS	(1 << 1)
# define OP_COLOR	(1 << 2)
# define OP_COREF	(1 << 3)
# define OP_HEXDP	(1 << 4)
# define OP_COREF	(1 << 3)
# define OP_HEXDP	(1 << 4)
# define OP_VERBOSE	(1 << 5)
# define OP_CHAIN	(1 << 6)

# define T_INST		16

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

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

typedef struct		s_token
{
	char			*content;
	size_t			line;
	size_t			row;
	size_t			content_size;
	unsigned int	mem_size;
	t_op			op;
	char			*ptr;
	t_arg_type		type;
	int				lex_type;
	int				address;
	int				idx;
	int				nl;
	int				el;
	int				eof;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct		s_label
{
	char			*name;
	size_t			address;
	struct s_label	*next;
}					t_label;

typedef struct		s_lexer
{
	t_token			**token;
	t_label			**label;
	unsigned int	curr_addr;
	int				curr_type;
	char			*str;
	char			*name;
	char			*comment;
	unsigned char	header;
	unsigned char	command;
	unsigned char	instr;
	unsigned char	param_count;
	unsigned char	at_least_one;
}					t_lexer;

typedef struct		s_env
{
	short			opt;
	char			*str;
	int				debug_fd;
	t_token			*lst;
	t_label			*labels;
	t_lexer			lexer;
	char			*name;
	char			*comment;
	int				head;
	int				cmd;
	char			*path;
}					t_env;

/*
**				print functions
*/
void				print_usage(t_env *env);
void				exit_usage(t_env *env);
void				print_color_ref(t_env *env);
void				print_lst(t_env *env, int fd);
void				print_labels(t_env *env);
void				print_tokens(t_token *token);
void				print_first_line(t_env *env, t_token *lst);
void				print_code(t_env *env, t_token *tmp, int version);
void				print_zero_byte(int fd, int start, int loop_nb);
void				print_byte(int fd, unsigned int bit, int shift);
int					get_dump(t_token *param);
void				print_addresses(t_env *env, t_token *tmp, int fd);
void				print_dir_lst(t_env *env, t_token *param, t_token *tmp,
	int version);
void				print_ind_lst(t_env *env, t_token *cmd, t_token *tmp,
	int version);
void				print_carry(t_env *env, t_token *param, int toprint,
	int version);

/*
**				input and read functions
*/

char				*get_file_content(char *av);
void				get_options(t_env *env, int ac, char **av);
void				get_prog(t_lexer *lex);
void				corewar_lexer(t_lexer *lex);
void				corewar_parser(t_lexer *lex);

/*
**				random tools for ASM program
*/

void				get_options(t_env *env, int ac, char **av);
int					get_line(char *str, char *ptr);
int					get_row(char *str, char *ptr);
void				exit_error(int err_code, t_lexer *lex, char *str,
	t_token *token);
void				print_cmd_error(int err_code, t_token *lst);
unsigned char		get_arg_mask(t_token *param);
int					get_max_addr(t_env *env);
int					create_file(t_env *env, char *src);
void				print_dir_output(int fd, t_token *tmp, t_label *label,
	t_token *param);
void				print_ind_output(int fd, t_token *tmp, t_label *label,
	t_token *param);

/*
**				free functions
*/

int					free_env(t_lexer *lex);
void				free_labels(t_label **lst);
void				free_tokens(t_token **lst);

/*
**				token list tools
*/

t_token				*create_token(t_lexer *lex, char *tmp, char *ptr, int type);
void				token_queue(t_token **start, t_token *token);

/*
**				label list tools
*/

t_label				*create_label(t_token *token);
void				label_queue(t_label **lst, t_label *label);
void				parse_label(t_lexer *lex, t_token **token);
void				parse_label_param(t_lexer *lex, t_token *token,
	t_token *instr, int type);

/*
**				writings functions
*/

void				writing_binary(int fd, t_env *env);

/*
**				check tools
*/

int					is_digit_string(char *str);
int					is_command(t_op *cmd);
int					is_space(char c);

/*
**				asm handle error exit
*/

void				handle_printerr(char *str);
void				handle_exit(char *str, t_token *token);
void				handle_invalid(char *str, t_token *token, t_lexer *lex);
void				handle_conditions(int err_code, char *str, t_token *token);

/*
**				asm lexer
*/

void				lexer_string_quote(t_lexer *lex, char **str);
void				lexer_string(t_lexer *lex, char **str);
void				corewar_lexer(t_lexer *lex);

t_token				*create_token(t_lexer *lex, char *tmp, char *ptr, int type);
void				token_queue(t_token **start, t_token *token);

void				lexer_direct(t_lexer *lex, char **str);
void				lexer_value(t_lexer *lex, char **str, int type);
void				lexer_label(t_lexer *lex, char **str, int type);
int					lexer_command(t_lexer *lex, char **str);

char				*skip_useless(char *str);
char				*skip_spaces_only_rev(char *ptr, char *str);
char				*skip_spaces_only(char *str);
char				*skip_space_char(char *str);

char				*newline(char *str);
int					get_row(char *str, char *ptr);
int					get_line(char *str, char *ptr);
int					is_space(char c);

void				parse_command(t_lexer *lex, t_token **token);
void				parse_register(t_lexer *lex, t_token *token);
void				parse_value(t_lexer *lex, t_token *token,
	t_token *instr, int type);
void				parse_indirect(t_lexer *lex, t_token *token,
	t_token *instr);
void				parse_direct(t_lexer *lex, t_token *token, t_token *instr);
void				parse_start_check(t_token *tmp, t_lexer *lex);
void				parse_end_check(t_token *tmp, t_token *instr, t_lexer *lex);
void				asm_commandcheck(t_token *tmp, t_lexer *lex);

void				init_check_opt(t_env *env);

#endif
