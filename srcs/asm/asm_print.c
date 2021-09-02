/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 17:47:51 by sdincbud          #+#    #+#             */
/*   Updated: 2019/08/11 17:03:25 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_color_ref(t_env *env)
{
	int	fd;

	fd = 0;
	if (env->opt & OP_COLOR)
	{
		ft_printf("\n%w{bold}Color references:{eoc}\n", fd);
		ft_printf("%w    - {red}Labels{eoc}\n", fd);
		ft_printf("%w    - {yellow}Commands{eoc}\n", fd);
		ft_printf("%w    - {magenta}Registers{eoc}\n", fd);
		ft_printf("%w    - {green}Directs{eoc}\n", fd);
		ft_printf("%w    - {cyan}Indirects{eoc}\n", fd);
		ft_printf("%w    - {blue}Arguments mask{eoc}\n", fd);
	}
}

int		get_max_addr(t_env *env)
{
	t_token *tmp;
	int		addr;

	addr = 0;
	tmp = *env->lexer.token;
	while (tmp->next && tmp->next->content)
		tmp = tmp->next;
	addr = tmp->address + tmp->mem_size;
	return (addr);
}

void	print_lst(t_env *env, int fd)
{
	t_token *tmp;

	tmp = *env->lexer.token;
	ft_printf("%wDumping annotated program on %s output\n",
		fd, fd == 2 ? "error" : "standard");
	ft_printf("%wProgram size : %d bytes\n", fd, get_max_addr(env));
	ft_printf("%wName : \"%s\"\n", fd, env->lexer.name);
	ft_printf("%wComment : \"%s\"\n", fd, env->lexer.comment);
	ft_printf("%w\n", fd);
	while (tmp)
	{
		if (!tmp->content || tmp->lex_type == 0)
			break ;
		if (tmp->type == T_LAB)
			print_first_line(env, tmp);
		if (tmp->lex_type == instruction)
		{
			print_first_line(env, tmp);
			print_code(env, tmp, 1);
			print_code(env, tmp, 0);
			ft_printf("%w\n", fd);
		}
		tmp = tmp->next;
	}
}

void	print_labels(t_env *env)
{
	int		fd;
	int		color;
	t_label	*tmp;

	fd = env->debug_fd;
	color = env->opt & OP_COLOR;
	tmp = *env->lexer.label;
	color ? ft_printf("%w{cyan}", fd) : 0;
	ft_printf("%w\n%-20s%-8s%s\n", fd, "Name", "Hexa", "Decimal");
	while (tmp)
	{
		color ? ft_printf("%w{magenta}", fd) : 0;
		ft_printf("%w%-20s", fd, tmp->name);
		color ? ft_printf("%w{green}", fd) : 0;
		ft_printf("%w0x%-5x {eoc}", fd, tmp->address);
		ft_printf("%w(", fd);
		color ? ft_printf("%w{yellow}", fd) : 0;
		ft_printf("%w%-5d{eoc}", fd, tmp->address);
		ft_printf("%w)\n", fd);
		tmp = tmp->next;
	}
}

void	print_tokens(t_token *token)
{
	while (token)
	{
		ft_printf("Token [%03d:%03d] : -%s-\n", token->line, token->row,
			token->content);
		ft_printf("	lex_type	: %d\n", token->lex_type);
		ft_printf("	type		: %d\n", token->type);
		ft_printf("	nl		: %d\n", token->nl);
		ft_printf("	el		: %d\n", token->el);
		ft_printf("	eof		: %d\n", token->eof);
		ft_printf("	addr		: %d\n", token->address);
		ft_printf("	size		: %d\n\n", token->mem_size);
		token = token->next;
	}
}
