/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 12:17:37 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/11 14:20:53 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	vm_init_new(t_proc **proc, unsigned int pn, unsigned long num, int i)
{
	t_proc	*new;
	int		j;

	j = -1;
	new = *proc;
	while (++j < REG_NUMBER)
		new->reg[j] = 0;
	new->cycle = 0;
	new->live = 0;
	new->start = i;
	new->pc = 0;
	new->player = pn;
	new->carry = 0;
	new->reg[0] = num;
}

void	init_arena(t_vm *vm, t_champ **head, t_proc **procs, int i)
{
	static int	z = 1;
	t_champ		*champs;
	t_proc		*new;

	champs = *head;
	new = NULL;
	if (!vm->opt.dump)
		ft_printf("Introducing contestants...\n");
	while (champs)
	{
		new = malloc_proc();
		if (champs->code)
			ft_strirep(vm->arena, champs->code, i, champs->prog_len);
		if (!vm->opt.dump)
			ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				champs->num, champs->prog_len, champs->title, champs->comment);
		vm_init_new(&new, champs->playerno, champs->num, i);
		push_color(vm->colors, i, champs->prog_len, z++);
		push_proc_front(procs, new);
		vm->last_live = champs->num;
		vm->pnum++;
		champs = champs->next;
		i = i + (MEM_SIZE / vm->opt.players);
	}
}

void	vm_init(t_vm *vm)
{
	int	i;

	i = -1;
	vm->champs = NULL;
	vm->proc = NULL;
	ft_bzero(vm, sizeof(t_vm));
	ft_bzero(vm->arena, MEM_SIZE);
	ft_bzero(&(vm->opt), sizeof(t_option));
	vm->first_print = 1;
	vm->opt.visu = 0;
	vm->opt.dsize = 0;
	vm->opt.stealth = 0;
	vm->cyclecheck = CYCLE_TO_DIE;
	while (++i < MAX_PLAYERS)
	{
		vm->opt.p[i].num = -1;
		vm->opt.p[i].file = NULL;
	}
}
