/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff_live_zjmp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 12:12:43 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/11 14:27:38 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_live(t_vm *vm, t_proc **proc, t_type args[])
{
	t_proc	*tmp;
	t_champ	*champ;

	tmp = *proc;
	tmp->live += 1;
	champ = vm->champs;
	while (champ)
	{
		if (champ->num == args[0].data)
		{
			if (vm->opt.stealth)
			{
				ft_printf("A process shows that player %d (%s) is alive.\n",
					tmp->player, champ->title);
			}
			push_color(vm->colors, tmp->pc + tmp->start, 1,
					champ->playerno);
			champ->lives = vm->cycles;
			vm->last_live = champ->num;
			champ->livecurrent++;
		}
		champ = champ->next;
	}
}

void	op_aff(t_vm *vm, t_proc **proc, t_type args[])
{
	t_proc			*tmp;
	unsigned char	c;

	tmp = *proc;
	(void)vm;
	if (args[0].data > REG_NUMBER || args[0].data < 1)
		return ;
	c = ((unsigned char)(tmp->reg[args[0].data - 1]) % 256);
	if (vm->opt.stealth)
		ft_printf("Player %d has used aff: (%c)\n", tmp->player, c);
}

void	op_zjmp(t_vm *vm, t_proc **proc, t_type args[])
{
	t_proc	*tmp;

	tmp = *proc;
	if (tmp->carry)
		tmp->pc = tmp->pc + (short)args[0].data % IDX_MOD;
	else
		tmp->pc = tmp->pc + 3;
	while (tmp->start + tmp->pc >= MEM_SIZE)
		tmp->pc -= MEM_SIZE;
	while (tmp->pc + tmp->start < 0)
		tmp->pc += MEM_SIZE;
	(void)vm;
}
