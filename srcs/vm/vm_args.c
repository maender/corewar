/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdincbud <sdincbud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:06:15 by fldoucet          #+#    #+#             */
/*   Updated: 2019/08/11 14:38:07 by sdincbud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		player_taken(t_option *opt, unsigned long player, char *file)
{
	static unsigned long	z = 1;
	int						i;
	int						j;

	j = -1;
	if (ft_strcmp(file + ft_strlen(file) - 4, ".cor"))
		return (1);
	if ((i = open(file, O_RDONLY)) < 0)
		return (2);
	while (++j < MAX_PLAYERS)
	{
		if (player == opt->p[j].num)
			return (1);
		else if (!(opt->p[j].file))
		{
			opt->p[j].num = player ? player : z;
			opt->p[j].file = file;
			if (player == z || !player)
				z += 1;
			close(i);
			return (0);
		}
	}
	close(i);
	return (0);
}

void	args_nchampion(t_vm *vm, char **av, int *i, int *j)
{
	unsigned int	player;
	int				k;

	player = 0;
	*i += 1;
	if (vm->opt.players >= MAX_PLAYERS)
		vm_error(13, NULL);
	if (av[*i] && (player = ft_atoul(av[*i])) <= 0)
		vm_error(6, NULL);
	*i += 1;
	if (!av[*i])
		vm_error(6, NULL);
	if ((k = player_taken(&vm->opt, player, av[*i])))
		vm_error(k == 2 ? 1 : 13, NULL);
	vm->opt.players = *j;
	*j += 1;
}

void	args_champion(t_vm *vm, char *av, int *j)
{
	int		k;

	if (vm->opt.players >= MAX_PLAYERS)
		vm_error(13, NULL);
	if ((k = player_taken(&vm->opt, 0, av)))
		vm_error(k == 2 ? 1 : 6, NULL);
	vm->opt.players = *j;
	*j += 1;
}

void	args_dump(t_vm *vm, char **av, int *i, t_option *opt)
{
	if (!ft_strcmp(av[*i], "--dump") || !ft_strcmp(av[*i], "-d"))
		opt->dsize = 64;
	else if (!ft_strcmp(av[*i], "--dump32") || !ft_strcmp(av[*i], "-d32"))
		opt->dsize = 32;
	*i += 1;
	if (av[*i] && (vm->opt.dump = ft_atoi(av[*i])) < 1)
		vm_error(10, NULL);
}

void	vm_args(t_vm *vm, int ac, char **av, int i)
{
	int				j;

	j = 1;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "--dump") || !ft_strcmp(av[i], "-d")
			|| !ft_strcmp(av[i], "--dump32") || !ft_strcmp(av[i], "-d32"))
			args_dump(vm, av, &i, &(vm->opt));
		else if (!ft_strcmp(av[i], "--visual") || !ft_strcmp(av[i], "-v"))
			vm->opt.visu = 1;
		else if (!ft_strcmp(av[i], "--help") || !ft_strcmp(av[i], "-h"))
			vm_error(12, NULL);
		else if (!ft_strcmp(av[i], "--number") || !ft_strcmp(av[i], "-n"))
			args_nchampion(vm, av, &i, &j);
		else if (!ft_strcmp(av[i] + ft_strlen(av[i]) - 4, ".cor"))
			args_champion(vm, av[i], &j);
		else if (!ft_strcmp(av[i], "--print") || !ft_strcmp(av[i], "-p"))
			vm->opt.stealth = 1;
		else if (av[i])
			ft_printf("%wERROR: ignoring argument \"%s\"\n", 2, av[i]);
		i++;
	}
	if ((vm->opt.visu && (vm->opt.dump || vm->opt.stealth)) || !vm->opt.players)
		vm_error(!vm->opt.players ? 9 : 5, NULL);
}
