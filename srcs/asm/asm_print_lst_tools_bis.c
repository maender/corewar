/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_print_lst_tools_bis.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 15:05:10 by edjubert          #+#    #+#             */
/*   Updated: 2019/08/10 15:25:57 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_dump(t_token *param)
{
	int		i;
	t_token	*tmp;

	i = 1;
	if (param->op.args_mask)
		i++;
	tmp = param->next;
	while (tmp && tmp->type != 0 && (tmp->type & T_DIR
			|| tmp->type & T_IND || tmp->type & T_REG))
	{
		if (tmp->type & T_REG)
			i++;
		else if (tmp->type & T_DIR)
			i += param->op.carry ? 2 : 4;
		else
			i += 2;
		tmp = tmp->next;
	}
	return (i);
}

void	print_addresses(t_env *env, t_token *tmp, int fd)
{
	int	color;

	color = env->opt & OP_COLOR;
	color ? ft_printf("%w{bold}", fd) : 0;
	if (tmp->type == T_LAB)
	{
		ft_printf("%w%-11d:    ", fd, tmp->address);
		color ? ft_printf("%w{red}{bold}", fd) : 0;
		ft_printf("%w%s", fd, tmp->content);
	}
	else if (tmp->type == 0)
	{
		ft_printf("%w%-5d", fd, tmp->address);
		color ? ft_printf("%w{eoc}", fd) : 0;
		ft_printf("%w(", fd);
		color ? ft_printf("%w{yellow}{bold}", fd) : 0;
		ft_printf("%w%-3d", fd, get_dump(tmp));
		color ? ft_printf("%w{eoc}", fd) : 0;
		ft_printf("%w)", fd);
		color ? ft_printf("%w{bold}", fd) : 0;
		ft_printf("%w :        ", fd);
		color ? ft_printf("%w{yellow}{bold}", fd) : 0;
		ft_printf("%w%-10s", fd, tmp->content);
	}
}

void	print_ind_lst(t_env *env, t_token *cmd, t_token *tmp, int version)
{
	int		toprint;
	char	*str;
	t_label	*label;

	label = *env->lexer.label;
	str = tmp->content;
	if (str[0] == LABEL_CHAR)
	{
		while (label && (ft_strncmp(str + 1, label->name, ft_strlen(str + 1))
				|| ft_strncmp(str + 1, label->name, ft_strlen(label->name))))
			label = label->next;
		toprint = label->address - cmd->address;
	}
	else
		toprint = ft_atol(tmp->content);
	env->opt & OP_COLOR ? ft_printf("%w{cyan}", env->debug_fd) : 0;
	if (version)
	{
		ft_printf("%w%-3d ", env->debug_fd, ((unsigned int)toprint >> 8) % 256);
		ft_printf("%w%-14d", env->debug_fd, (unsigned int)toprint % 256);
	}
	else
		ft_printf("%w%-17d ", env->debug_fd, (unsigned int)toprint);
	env->opt & OP_COLOR ? ft_printf("%w{eoc}", env->debug_fd) : 0;
}

void	print_carry(t_env *env, t_token *param, int toprint, int version)
{
	int	fd;

	fd = env->debug_fd;
	env->opt & OP_COLOR ? ft_printf("%w{green}", fd) : 0;
	if (version)
	{
		!param->op.carry
			? ft_printf("%w%-4d", fd, ((unsigned int)toprint >> 24) % 256) : 0;
		!param->op.carry
			? ft_printf("%w%-4d", fd, ((unsigned int)toprint >> 16) % 256) : 0;
		ft_printf("%w%-4d", fd, ((unsigned int)toprint >> 8) % 256);
		param->op.carry
			? ft_printf("%w%-3d", fd, ((unsigned int)toprint) % 256)
			: ft_printf("%w%-6d", fd, ((unsigned int)toprint) % 256);
		param->op.carry ? ft_printf("%w%11s", fd, "") : 0;
	}
	else
		ft_printf("%w%-18d", fd, toprint);
	env->opt & OP_COLOR ? ft_printf("%w{eoc}", fd) : 0;
}

void	print_dir_lst(t_env *env, t_token *param, t_token *tmp, int version)
{
	char	*str;
	int		toprint;
	t_label	*label;

	label = *env->lexer.label;
	str = tmp->content;
	if (str[1] == LABEL_CHAR)
	{
		while (label && (ft_strncmp(str + 2, label->name, ft_strlen(str + 2))
				|| ft_strncmp(str + 2, label->name, ft_strlen(label->name))))
			label = label->next;
		toprint = label->address - param->address;
		print_carry(env, param, toprint, version);
	}
	else
	{
		toprint = (int)ft_atol(&str[1]);
		print_carry(env, param, toprint, version);
	}
}
