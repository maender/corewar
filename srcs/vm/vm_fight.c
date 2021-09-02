/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_fight.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdincbud <sdincbud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:46:48 by fldoucet          #+#    #+#             */
/*   Updated: 2019/08/11 15:04:01 by sdincbud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	root_print(t_vm *vm, t_proc **proces, int i[4], WINDOW *arena)
{
	t_proc			*tmp;
	unsigned char	*arena_bis;
	int				pair;

	tmp = *proces;
	arena_bis = vm->arena;
	while (tmp)
	{
		if ((i[0] * 64 + i[1] / 3) == tmp->pc + tmp->start)
		{
			wattron(arena, A_STANDOUT);
			break ;
		}
		tmp = tmp->next;
	}
	pair = COLOR_PAIR(get_color_arena(vm->colors, i));
	wattron(arena, pair);
	mvwprintw(arena, i[0] + 2, i[1] + 3, "%.2x", arena_bis[i[2]]);
	wattroff(arena, A_STANDOUT);
	wattroff(arena, pair);
	mvwprintw(arena, i[0] + 2, i[1] + 5, " ");
}

void	print_arena(t_vm *vm, WINDOW *arena)
{
	int				i;
	int				j;
	int				h;
	int				index[4];

	i = 0;
	h = 0;
	index[3] = 0;
	while (i < 64)
	{
		j = 0;
		while (j < 64 * 3)
		{
			index[0] = i;
			index[1] = j;
			index[2] = h;
			root_print(vm, &(vm->proc), index, arena);
			index[3] = 1;
			j = j + 3;
			h++;
		}
		i++;
	}
}

void	how_to_win_lines(t_vm *vm, WINDOW *arena, WINDOW *info, int *i)
{
	if (vm->opt.visu)
	{
		print_arena(vm, arena);
		mvwprintw(info, 2, 3, "** RUNNING **");
	}
	get_instructions(vm, &vm->proc);
	if (vm->opt.visu)
		get_info(vm, info, vm->cycles);
	if (vm->opt.visu)
	{
		wrefresh(arena);
		wrefresh(info);
		usleep(4500);
	}
	if (vm->opt.dump && vm->opt.dump == vm->cycles)
		vm_dump(vm);
	vm->cycles++;
	*i += 1;
}

void	vm_endfight(t_vm *vm, WINDOW **arena, WINDOW **info)
{
	t_champ		*champ;

	champ = vm->champs;
	if (vm->opt.visu)
	{
		delwin(*arena);
		delwin(*info);
		endwin();
	}
	while (champ)
	{
		if (vm->last_live == champ->num)
			break ;
		champ = champ->next;
	}
	if (!vm->opt.dump && champ)
		ft_printf("Player %d (%s) has won!\n", vm->last_live, champ->title);
}

void	vm_fight(t_vm *vm, int i, int paused)
{
	WINDOW	*arena;
	WINDOW	*info;

	if (vm->opt.visu)
		init_ncurses(&arena, &info);
	while (vm->cyclecheck && vm->proc)
	{
		if (vm->opt.visu)
			vm_event(vm, arena, info, &paused);
		if (paused == 0)
			how_to_win_lines(vm, arena, info, &i);
		if (i == vm->cyclecheck)
			check_overheat(vm, &i);
	}
	vm_endfight(vm, &arena, &info);
}
