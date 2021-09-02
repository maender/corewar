/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdincbud <sdincbud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 12:18:41 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/11 15:05:02 by sdincbud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

short	get_index(t_proc *proc, unsigned int arg)
{
	short	index;

	index = (proc->pc + proc->start + (short)arg % IDX_MOD) % MEM_SIZE;
	while (index < 0)
		index += MEM_SIZE;
	return (index);
}

void	vm_dump(t_vm *vm)
{
	int	ln;
	int	byte;

	ln = 0;
	while (ln < MEM_SIZE)
	{
		ft_printf(!ln ? "0x0000 : " : "%#.4x : ", ln);
		byte = -1;
		while (++byte < vm->opt.dsize)
			ft_printf("%.2x ", vm->arena[byte + ln]);
		ft_printf("\n");
		ln += vm->opt.dsize;
	}
	exit(0);
}

void	do_check_overflow(t_vm *vm, int overflow)
{
	if (overflow >= NBR_LIVE)
		vm->cyclecheck = (vm->cyclecheck
				- CYCLE_DELTA < 0 ? 0 : vm->cyclecheck - CYCLE_DELTA);
	else
		++vm->checks;
	if (vm->checks >= MAX_CHECKS)
	{
		vm->cyclecheck = (vm->cyclecheck
				- CYCLE_DELTA < 0 ? 0 : vm->cyclecheck - CYCLE_DELTA);
		vm->checks = 0;
	}
}

void	check_overheat(t_vm *vm, int *i)
{
	int			overflow;
	t_proc		*champ;
	t_champ		*list;

	overflow = 0;
	champ = vm->proc;
	list = vm->champs;
	while (champ)
	{
		overflow += champ->live;
		champ = champ->next;
	}
	while (list)
	{
		list->livecurrent = 0;
		list = list->next;
	}
	do_check_overflow(vm, overflow);
	baseball_bat(vm, &vm->proc);
	ft_memcpy(vm->breakdown_old, vm->breakdown, sizeof(int) * MAX_PLAYERS);
	vm->tot_live_old = vm->tot_live;
	*i = 0;
}

void	vm_event(t_vm *vm, WINDOW *arena, WINDOW *info, int *paused)
{
	int test;

	test = 0;
	if ((test = getch()) == ' ' && *paused == 0)
	{
		*paused = 1;
		mvwprintw(info, 2, 3, "** PAUSED ** ");
		wrefresh(info);
	}
	else if (test == ' ' && *paused == 1)
		*paused = 0;
	else if (test == 27)
	{
		vm_endfight(vm, &arena, &info);
		exit(0);
	}
}
