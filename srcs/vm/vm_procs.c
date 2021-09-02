/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_procs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 10:15:04 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/09 13:44:27 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	loop_procs(t_vm *vm, t_proc **procs, t_proc *prev, t_proc *tmp)
{
	while (tmp)
	{
		if (!tmp->live)
		{
			vm->pnum--;
			if (!prev)
			{
				*procs = tmp->next;
				free(tmp->reg);
				ft_memdel((void**)&tmp);
				tmp = *procs;
				continue ;
			}
			else
			{
				prev->next = tmp->next;
				free(tmp->reg);
				ft_memdel((void**)&tmp);
				tmp = prev;
			}
		}
		tmp->live = 0;
		prev = tmp;
		tmp = tmp->next;
	}
}

void	baseball_bat(t_vm *vm, t_proc **procs)
{
	t_proc *tmp;
	t_proc *prev;

	tmp = *procs;
	prev = NULL;
	if (!tmp)
		return ;
	loop_procs(vm, procs, prev, tmp);
}

t_proc	*malloc_proc(void)
{
	t_proc	*new;

	new = NULL;
	if (!(new = (t_proc*)malloc(sizeof(t_proc))))
		vm_error(3, NULL);
	if (!(new->reg = (unsigned int*)malloc(sizeof(unsigned int) * REG_NUMBER)))
		vm_error(3, NULL);
	return (new);
}

void	push_proc_front(t_proc **procs, t_proc *new)
{
	t_proc	*tmp;

	tmp = *procs;
	if (!tmp)
	{
		*procs = new;
		(*procs)->next = NULL;
	}
	else
	{
		new->next = tmp;
		*procs = new;
	}
}
