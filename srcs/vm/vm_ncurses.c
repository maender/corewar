/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ncurses.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdincbud <sdincbud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 11:43:03 by fldoucet          #+#    #+#             */
/*   Updated: 2019/08/11 15:05:17 by sdincbud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			get_color_arena(t_color colors[MEM_SIZE], int i[4])
{
	int		pos;
	int		color;

	pos = i[0] * 64 + i[1] / 3;
	color = colors[pos].champ;
	if (colors[pos].t >= colors[pos].time)
	{
		colors[pos].t = 0;
		colors[pos].time = 0;
		if (colors[pos].opcode == 1)
			colors[pos].champ = colors[pos].lastchamp;
	}
	if (colors[pos].t < colors[pos].time)
		color += (colors[pos].opcode == 1 ? 11 : 7);
	if (i[3] == 1 && colors[pos].t < colors[pos].time)
		colors[pos].t = colors[pos].t + 1;
	return (color);
}

int			print_players(t_champ **champs, WINDOW *info)
{
	int		n;
	t_champ *tmp;

	tmp = *champs;
	n = 0;
	while (tmp)
	{
		mvwprintw(info, n * 4 + 11, 3, "Player %lld : ", tmp->num);
		wattron(info, COLOR_PAIR(tmp->playerno + 7));
		mvwprintw(info, n * 4 + 11, 16, "%s", tmp->title);
		wattroff(info, COLOR_PAIR(tmp->playerno) + 7);
		mvwprintw(info, n * 4 + 12, 3, " Last live : %22d", tmp->lives);
		mvwprintw(info, n * 4 + 13, 3, " Lives in current period : %8d",
			tmp->livecurrent);
		tmp = tmp->next;
		n++;
	}
	return (n);
}

void		get_info(t_vm *vm, WINDOW *info, int cycles)
{
	int n;

	wattron(info, COLOR_PAIR(6));
	mvwprintw(info, 4, 3, "Cycles/second limit : %d", 50);
	mvwprintw(info, 7, 3, "Cycle : %d", cycles);
	mvwprintw(info, 9, 3, "Processes : %d", vm->pnum);
	n = print_players(&vm->champs, info);
	mvwprintw(info, n * 4 + 11, 3, "Live breakdown for current period :");
	mvwprintw(info, n * 4 + 14, 3, "Live breakdown for last period :");
	wattron(info, COLOR_PAIR(7));
	get_live_breakdown(vm, n, info);
	print_old_breakdown(vm, info, n);
	wattroff(info, COLOR_PAIR(7));
	mvwprintw(info, n * 4 + 17, 3, "CYCLE_TO_DIE : %d		", vm->cyclecheck);
	mvwprintw(info, n * 4 + 19, 3, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvwprintw(info, n * 4 + 21, 3, "NRB_LIVE : %d", NBR_LIVE);
	mvwprintw(info, n * 4 + 23, 3, "MAX_CHECKS : %d", MAX_CHECKS);
	wattroff(info, COLOR_PAIR(6));
}

void		init_colors_ncurses(void)
{
	start_color();
	init_color(COLOR_YELLOW, 500, 500, 500);
	init_color(COLOR_WHITE, 1000, 1000, 1000);
	init_color(COLOR_LIGHT_BLUE, 400, 400, 900);
	init_color(COLOR_LIGHT_CYAN, 400, 900, 900);
	init_color(COLOR_LIGHT_GREEN, 400, 1000, 400);
	init_color(COLOR_LIGHT_RED, 900, 400, 400);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(6, COLOR_WHITE, COLOR_BLACK);
	init_pair(7, COLOR_YELLOW, COLOR_BLACK);
	init_pair(8, COLOR_LIGHT_GREEN, COLOR_BLACK);
	init_pair(9, COLOR_LIGHT_BLUE, COLOR_BLACK);
	init_pair(10, COLOR_LIGHT_RED, COLOR_BLACK);
	init_pair(11, COLOR_LIGHT_CYAN, COLOR_BLACK);
	init_pair(12, COLOR_WHITE, COLOR_GREEN);
	init_pair(13, COLOR_WHITE, COLOR_BLUE);
	init_pair(14, COLOR_WHITE, COLOR_RED);
	init_pair(15, COLOR_WHITE, COLOR_CYAN);
}

void		init_ncurses(WINDOW **arena, WINDOW **info)
{
	initscr();
	noecho();
	timeout(0);
	curs_set(0);
	init_colors_ncurses();
	refresh();
	*arena = newwin(68, 64 * 3 + 5, 0, 0);
	*info = newwin(68, 58, 0, 64 * 3 + 4);
	wattron(*arena, COLOR_PAIR(5));
	wattron(*info, COLOR_PAIR(5));
	box(*arena, 0, 0);
	box(*info, 0, 0);
	wattroff(*info, COLOR_PAIR(5));
	wrefresh(*arena);
	wrefresh(*info);
}
