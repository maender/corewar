/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdincbud <sdincbud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/08/10 15:08:13 by sdincbud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op	g_op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

int		check_opname(char *str, t_token *lst, int *address)
{
	int		i;

	i = 0;
	while (g_op_tab[i].opcode != 0)
	{
		if (!ft_strncmp(g_op_tab[i].name, str, ft_strlen(str)))
		{
			ft_memcpy((void*)&lst->op, (void*)&g_op_tab[i], sizeof(t_op));
			lst->type = T_REG + T_IND + T_DIR + T_LAB;
			if (g_op_tab[i].args_mask)
				*address += 1;
			*address += 1;
			return (1);
		}
		i++;
	}
	return (0);
}

int		is_command(t_op *cmd)
{
	int i;

	i = -1;
	while (g_op_tab[++i].opcode != 0)
	{
		if (!ft_strncmp(g_op_tab[i].name, cmd->name, ft_strlen(cmd->name))
				&& !ft_strncmp(g_op_tab[i].name, cmd->name,
				ft_strlen(g_op_tab[i].name)))
		{
			ft_memcpy((void*)cmd, (void*)&g_op_tab[i], sizeof(t_op));
			return (1);
		}
	}
	return (0);
}

char	*ft_strnnchr(const char *s, int c, size_t len)
{
	int i;

	i = 0;
	if (s)
	{
		while (s[i] && i < (int)len)
		{
			if (s[i] == (char)c)
				return ((char*)&s[i]);
			i++;
		}
		return (s[i] == (char)c ? (char*)&s[i] : NULL);
	}
	return (NULL);
}
