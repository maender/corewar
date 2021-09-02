/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdincbud <sdincbud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 12:34:28 by edjubert          #+#    #+#             */
/*   Updated: 2019/08/11 15:02:51 by sdincbud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	get_verbose_options(t_env *env, int ac, char **av, int i)
{
	if (!ft_strncmp(av[i], "--print", ft_strlen("--print")))
		env->opt |= OP_PRINT;
	if (!ft_strncmp(av[i], "--help", ft_strlen("--help")))
		exit_usage(env);
	if (!ft_strncmp(av[i], "--labels", ft_strlen("--labels")))
		env->opt |= OP_LABELS;
	if (!ft_strncmp(av[i], "--color", ft_strlen("--color")))
		env->opt |= OP_COLOR;
	if (!ft_strncmp(av[i], "--verbose", ft_strlen("--verbose")))
		env->opt |= OP_VERBOSE;
	if (!ft_strncmp(av[i], "--color-refeferences",
			ft_strlen("--color-references")))
		env->opt |= OP_COLOR;
	if (!ft_strncmp(av[i], "--chained-list", ft_strlen("--chained-list")))
		env->opt |= OP_CHAIN;
	if (!ft_strncmp(av[i], "--file-director",
			ft_strlen("--file-director")))
		if (i < ac - 1 && is_digit_string(av[i + 1]))
			if (ft_atoi(av[i + 1]) > 0 && ft_atoi(av[i + 1]) < 3)
				env->debug_fd = ft_atoi(av[i + 1]);
}

static void	get_short_options(t_env *env, int ac, char **av, int i)
{
	if (ft_match(av[i], "*c*"))
		env->opt |= OP_COLOR;
	if (ft_match(av[i], "*C*"))
		env->opt |= OP_COREF;
	if (ft_match(av[i], "*h*"))
		exit_usage(env);
	if (ft_match(av[i], "*l*"))
		env->opt |= OP_LABELS;
	if (ft_match(av[i], "*v*"))
		env->opt |= OP_VERBOSE;
	if (ft_match(av[i], "*p*"))
		env->opt |= OP_PRINT;
	if (ft_match(av[i], "*L*"))
		env->opt |= OP_CHAIN;
	if (!ft_strcmp(av[i], "-f") || ft_match(av[i], "*f*"))
		if (i < (ac - 1) && is_digit_string(av[i + 1]))
			if (ft_atoi(av[i + 1]) > 0 && ft_atoi(av[i + 1]) < 3)
				env->debug_fd = ft_atoi(av[i + 1]);
}

void		print_usage(t_env *env)
{
	ft_printf("Usage : ./asm [-hlxCp[c[f][1|2]]] [source file]\n");
	ft_printf("options :\n");
	ft_printf("     ");
	ft_printf("-c | --color\t\tprint output with color, only with -p option\n");
	ft_printf("     ");
	ft_printf("-C | --color-references\tprint color references\n");
	ft_printf("     ");
	ft_printf("-f | --file-director\tchoose %s",
		"on witch fd print (1 or 2), only with -p option\n");
	ft_printf("     ");
	ft_printf("-h | --help\t\tprint usage\n");
	ft_printf("     ");
	ft_printf("-l | --labels\t\tprint labels and their addresses\n");
	ft_printf("     ");
	ft_printf("-p | --print\t\tprint debug output\n");
	if (env->str)
		ft_strdel(&env->str);
}

void		get_options(t_env *env, int ac, char **av)
{
	int	i;

	if (ac > 1)
	{
		i = 0;
		while (++i < ac)
		{
			if (ft_strlen(av[i]) > 1 && av[i][0] == '-' && av[i][1] != '-')
				get_short_options(env, ac, av, i);
			else if (ft_strlen(av[i]) > 1 && !ft_strncmp(av[i], "--", 2)
				&& ft_strlen(av[i]) == 2)
				return ;
			else if (ft_strlen(av[i]) > 1 && !ft_strncmp(av[i], "--", 2))
				get_verbose_options(env, ac, av, i);
		}
	}
	else
		exit_usage(env);
}
