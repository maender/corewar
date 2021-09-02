/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_title_a_o.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 13:50:52 by edjubert          #+#    #+#             */
/*   Updated: 2019/07/01 15:05:02 by fldoucet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_add_mno(char c, char ***title)
{
	if (c == 'm' || c == 'M')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], "___  ___ ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], "||\\\\//|| ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], "|| \\/ || ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], "||    || ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "=========", 1);
	}
	if (c == 'n' || c == 'N')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], "__  __ ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], "||\\ || ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], "||\\\\|| ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], "|| \\|| ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "=======", 1);
	}
	if (c == 'o' || c == 'O')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], "  ___   ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], " // \\\\  ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], "((   )) ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], " \\\\_//  ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "========", 1);
	}
	ft_add_pqr(c, title);
}

static void		ft_add_jkl(char c, char ***title)
{
	if (c == 'j' || c == 'J')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], "   __ ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], "   || ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], "   || ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], "|__|| ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "======", 1);
	}
	if (c == 'k' || c == 'K')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], "__ __ ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], "|| // ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], "||<<  ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], "|| \\\\ ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "======", 1);
	}
	if (c == 'l' || c == 'L')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], "__    ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], "||    ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], "||    ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], "||__| ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "======", 1);
	}
	ft_add_mno(c, title);
}

static void		ft_add_ghi(char c, char ***title)
{
	if (c == 'g' || c == 'G')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], "  ___  ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], " // \\\\ ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], "(( ___ ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], " \\\\_|| ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "=======", 1);
	}
	if (c == 'h' || c == 'H')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], "__  __ ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], "||  || ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], "||==|| ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], "||  || ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "=======", 1);
	}
	if (c == 'i' || c == 'I')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], "__ ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], "|| ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], "|| ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], "|| ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "===", 1);
	}
	ft_add_jkl(c, title);
}

static void		ft_add_def(char c, char ***title)
{
	if (c == 'd' || c == 'D')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], "____   ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], "|| \\\\  ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], "||  )) ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], "||_//  ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "=======", 1);
	}
	if (c == 'e' || c == 'E')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], " ____ ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], "||    ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], "||==  ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], "||___ ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "======", 1);
	}
	if (c == 'f' || c == 'F')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], " ____ ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], "||    ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], "||==  ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], "||    ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "======", 1);
	}
	ft_add_ghi(c, title);
}

void			ft_add(char c, char ***title)
{
	if (c == 'a' || c == 'A')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], " ___  ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], "// \\\\ ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], "||=|| ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], "|| || ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "======", 1);
	}
	if (c == 'b' || c == 'B')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], "_____ ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], "|| )) ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], "||=)) ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], "||_)) ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "======", 1);
	}
	if (c == 'c' || c == 'C')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], "  ___ ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], " //   ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], "((    ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], " \\\\__ ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "======", 1);
	}
	ft_add_def(c, title);
}
