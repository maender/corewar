/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_breakdown.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdincbud <sdincbud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:03:00 by sdincbud          #+#    #+#             */
/*   Updated: 2019/08/11 14:31:59 by sdincbud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	print_standard(WINDOW *info, int n, int line)
{
	wattron(info, COLOR_PAIR(7));
	mvwprintw(info, n * 4 + line, 4,
		"--------------------------------------------------");
	wattroff(info, COLOR_PAIR(7));
}

static void	print_io(WINDOW *info, int n, int line, int io)
{
	wattron(info, COLOR_PAIR(6));
	mvwprintw(info, n * 4 + line, 3 + (io ? 0 : 51), io == 1 ? "[" : "]");
	wattroff(info, COLOR_PAIR(6));
}

static void	print_loop(int breakdown[MAX_PLAYERS], WINDOW *info, int n,
	int line)
{
	int	i;
	int	j;
	int	dec;

	i = -1;
	j = 0;
	dec = 0;
	while (++i < 51)
	{
		while (breakdown[j] < 1)
			j++;
		if (breakdown[j] <= i - dec)
		{
			dec += breakdown[j++];
			while (breakdown[j] < 1)
				j++;
		}
		if (j >= n || breakdown[j] < 1)
			break ;
		wattron(info, COLOR_PAIR(8 + j));
		mvwprintw(info, n * 4 + line, 4 + i, "-");
		wattron(info, COLOR_PAIR(8 + j));
	}
}

void		print_old_breakdown(t_vm *vm, WINDOW *info, int n)
{
	print_io(info, n, 15, 0);
	if (vm->tot_live_old)
		print_loop(vm->breakdown_old, info, n, 15);
	else
		print_standard(info, n, 15);
	print_io(info, n, 15, 1);
}

void		get_live_breakdown(t_vm *vm, int n, WINDOW *info)
{
	t_champ *champ;
	int		i;

	i = 0;
	champ = vm->champs;
	vm->tot_live = 0;
	print_io(info, n, 12, 0);
	while (champ)
	{
		vm->tot_live += champ->livecurrent;
		vm->breakdown[i++] = champ->livecurrent;
		champ = champ->next;
	}
	i = -1;
	if (vm->tot_live)
	{
		while (++i < n)
			vm->breakdown[i] = vm->breakdown[i] * 51 / vm->tot_live;
		print_loop(vm->breakdown, info, n, 12);
	}
	else
		print_standard(info, n, 12);
	print_io(info, n, 12, 1);
}
