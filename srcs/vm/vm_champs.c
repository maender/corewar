/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_champs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdincbud <sdincbud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:33:31 by fldoucet          #+#    #+#             */
/*   Updated: 2020/06/28 18:40:27 by sdincbud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void push_champ(t_champ **head, t_champ *new)
{
	t_champ *tmp;

	tmp = *head;
	if (!tmp)
	{
		tmp = new;
		*head = tmp;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void parse_instructions(t_champ **head, t_champ *new, int ind[3],
						unsigned char *tmp)
{
	unsigned char *tmp2;
	char *test;
	int i;

	ind[2] += 3;
	while (++(ind[2]) < COMMENT_LENGTH + 12)
	{
		if (tmp[ind[2]] && (tmp[ind[2]] > 31 && tmp[ind[2]] < 127))
		{
			test = ft_strsub((char *)&tmp[ind[2]], 0, 1);
			new->comment = ft_strjoin_free(new->comment, test, 0);
		}
	}
	new->code = NULL;
	tmp2 = new->cor;
	i = PROG_NAME_LENGTH + COMMENT_LENGTH + 16;
	new->code = tmp2 + i;
	if (new->flen - i != new->prog_len)
		vm_error(7, new->title);
	push_champ(head, new);
}

t_champ *init_heads(int ind[3], unsigned long num)
{
	t_champ *new;

	if (!(new = (t_champ *)malloc(sizeof(t_champ))))
		vm_error(3, NULL);
	vm_read(ind[1], new, ind[0] + 1);
	new->next = NULL;
	new->title = NULL;
	new->comment = NULL;
	new->playerno = ind[0] + 1;
	new->num = num > 0 ? num : (unsigned long)(ind[0] + 1);
	new->livecurrent = 0;
	new->lives = 0;
	return (new);
}

void parse_headers(t_champ **head, int ind[3], unsigned long num)
{
	t_champ *new;
	unsigned char *tmp;
	char *test;
	uint32_t magic;

	new = init_heads(ind, num);
	tmp = new->cor;
	magic = 0;
	ind[2] = 3;
	fill_32bit(&magic, 0, tmp);
	if (magic != COREWAR_EXEC_MAGIC)
		vm_error(8, NULL);
	while (++(ind[2]) < PROG_NAME_LENGTH + 4)
	{
		if (tmp[ind[2]] && (tmp[ind[2]] > 31 && tmp[ind[2]] < 127))
		{
			test = ft_strsub((char *)&tmp[ind[2]], 0, 1);
			new->title = ft_strjoin_free(new->title, test, 0);
		}
	}
	ind[2] += 4;
	fill_32bit(&magic, ind[2], tmp);
	if ((new->prog_len = magic) > CHAMP_MAX_SIZE || new->prog_len < 3)
		vm_error(7, new->title);
	parse_instructions(head, new, ind, tmp);
}

void parse_champions(t_vm *vm, t_order list[MAX_PLAYERS])
{
	int i[3];

	i[0] = -1;
	while (++(i[0]) < vm->opt.players)
	{
		if ((i[1] = open(list[i[0]].file, O_RDONLY)) < 3)
			vm_error(1, list[i[0]].file);
		parse_headers(&vm->champs, i, list[i[0]].num);
		vm->nb_champ++;
		close(i[1]);
	}
}
