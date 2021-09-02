/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_print_lst_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 14:13:42 by edjubert          #+#    #+#             */
/*   Updated: 2019/08/10 15:26:38 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	print_reg(t_env *env, int toprint)
{
	env->opt & OP_COLOR ? ft_printf("%w{magenta}", env->debug_fd) : 0;
	ft_printf("%w%-18d", env->debug_fd, toprint);
	env->opt & OP_COLOR ? ft_printf("%w{eoc}", env->debug_fd) : 0;
}

void		print_first_line(t_env *env, t_token *lst)
{
	int		i;
	int		fd;
	int		color;
	t_token	*tmp;

	tmp = lst;
	fd = env->debug_fd;
	i = tmp->op.num_args + 1;
	color = env->opt & OP_COLOR;
	print_addresses(env, tmp, fd);
	while (--i)
	{
		tmp = tmp->next;
		if (tmp->type & T_REG)
			color ? ft_printf("%w{magenta}{bold}", fd) : 0;
		else if (tmp->type & T_IND)
			color ? ft_printf("%w{cyan}{bold}", fd) : 0;
		else if (tmp->type & T_DIR)
			color ? ft_printf("%w{green}{bold}", fd) : 0;
		ft_printf("%w%-18s", fd, tmp->content);
	}
	color ? ft_printf("%w{eoc}", fd) : 0;
	ft_printf("%w\n", fd);
}

static void	print_code_bis(t_env *env, t_token *param, t_token *tmp)
{
	int	fd;

	fd = env->debug_fd;
	ft_printf("%w%15s     ", fd, "");
	env->opt & OP_COLOR ? ft_printf("%w{yellow}", fd) : 0;
	ft_printf("%w%-4d", fd, param->op.opcode);
	env->opt & OP_COLOR ? ft_printf("%w{eoc}", fd) : 0;
	env->opt & OP_COLOR ? ft_printf("%w{blue}", fd) : 0;
	tmp->op.args_mask ? ft_printf("%w%-6d", fd, get_arg_mask(param))
		: ft_printf("%w%6s", fd, "");
	env->opt & OP_COLOR ? ft_printf("%w{eoc}", fd) : 0;
}

void		print_code(t_env *env, t_token *tmp, int version)
{
	int		i;
	int		fd;
	char	*str;
	t_token	*param;

	param = tmp;
	print_code_bis(env, param, tmp);
	fd = env->debug_fd;
	i = param->op.num_args + 1;
	while (--i)
	{
		tmp = tmp->next;
		str = (char*)tmp->content;
		if (tmp->type & T_REG && str[0] == 'r')
			print_reg(env, ft_atol(&str[1]));
		else if (tmp->type & T_IND)
			print_ind_lst(env, param, tmp, version);
		else if (tmp->type & T_DIR)
			print_dir_lst(env, param, tmp, version);
	}
	ft_printf("%w\n", fd);
}
