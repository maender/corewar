/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 18:31:55 by edjubert          #+#    #+#             */
/*   Updated: 2019/08/11 17:31:37 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		print_header(int fd, t_env *env)
{
	int size;

	size = get_max_addr(env);
	ft_printf("%w%c", fd, COREWAR_EXEC_MAGIC >> 24);
	ft_printf("%w%c", fd, COREWAR_EXEC_MAGIC >> 16);
	ft_printf("%w%c", fd, COREWAR_EXEC_MAGIC >> 8);
	ft_printf("%w%c", fd, COREWAR_EXEC_MAGIC);
	ft_printf("%w%s", fd, env->lexer.name);
	print_zero_byte(fd, ft_strlen(env->lexer.name), PROG_NAME_LENGTH + 4);
	ft_printf("%w%c", fd, (char)(size >> 24));
	ft_printf("%w%c", fd, (char)(size >> 16));
	ft_printf("%w%c", fd, (char)(size >> 8));
	ft_printf("%w%c", fd, (char)size);
	ft_printf("%w%s", fd, env->lexer.comment);
	print_zero_byte(fd, ft_strlen(env->lexer.comment), COMMENT_LENGTH + 4);
}

unsigned char	get_arg_mask(t_token *param)
{
	int				i;
	int				shift;
	t_token			*tmp;
	unsigned char	arg_mask;

	i = -1;
	arg_mask = 0;
	shift = 6;
	if (param->next)
		tmp = param->next;
	while (++i < param->op.num_args)
	{
		if (tmp->type & T_REG)
			arg_mask |= REG_CODE << shift;
		if (tmp->type & T_DIR)
			arg_mask |= DIR_CODE << shift;
		if (tmp->type & T_IND)
			arg_mask |= IND_CODE << shift;
		shift -= 2;
		tmp = tmp->next;
	}
	return (arg_mask);
}

static void		print_command(int fd, t_token *tmp, t_token **param)
{
	unsigned char	arg_mask;

	if (tmp->op.args_mask)
	{
		arg_mask = get_arg_mask(tmp);
		print_byte(fd, (unsigned char)tmp->op.opcode, 1);
		print_byte(fd, arg_mask, 1);
	}
	else
		ft_printf("%w%c", fd, tmp->op.opcode);
	*param = tmp;
}

static void		print_content(int fd, t_env *env)
{
	t_token	*par;
	t_token	*tmp;

	tmp = *env->lexer.token;
	par = NULL;
	while (tmp)
	{
		if (!tmp->content)
			break ;
		if (tmp->lex_type == param && tmp->type & T_REG)
			print_byte(fd, (unsigned int)ft_atol(tmp->content + 1), 1);
		else if (tmp->lex_type == param && tmp->type & T_IND)
			print_ind_output(fd, tmp, *env->lexer.label, par);
		else if (tmp->lex_type == param && tmp->type & T_DIR)
			print_dir_output(fd, tmp, *env->lexer.label, par);
		else if (tmp->lex_type == instruction)
			print_command(fd, tmp, &par);
		tmp = tmp->next;
	}
}

void			writing_binary(int fd, t_env *env)
{
	ft_printf("Writing output program to %s\n", env->path);
	print_header(fd, env);
	print_content(fd, env);
	close(fd);
}
