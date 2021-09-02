/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_title_o_z.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 13:50:59 by edjubert          #+#    #+#             */
/*   Updated: 2019/03/08 16:53:56 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_add_yz(char c, char ***title)
{
	if (c == 'y' || c == 'Y')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], "_  _ ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], "\\\\// ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], " )/  ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], "//   ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "=====", 1);
	}
	if (c == 'z' || c == 'Z')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], "____ ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], "  // ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], " //  ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], "//__ ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "======", 1);
	}
	if (c == ' ')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], "     ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], "     ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], "     ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], "     ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "=====", 1);
	}
}

static void		ft_add_vwx(char c, char ***title)
{
	if (c == 'v' || c == 'V')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], "__ __ ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], "|| || ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], "\\\\ // ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], " \\v/  ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "======", 1);
	}
	if (c == 'w' || c == 'W')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], "__    __ ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], "||    || ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], "\\\\ /\\ // ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], " \\v/\\v/  ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "=========", 1);
	}
	if (c == 'x' || c == 'X')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], "_   _ ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], "\\\\ // ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], " )x(  ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], "// \\\\ ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "======", 1);
	}
	ft_add_yz(c, title);
}

static void		ft_add_stu(char c, char ***title)
{
	if (c == 's' || c == 'S')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], " ___ ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], "(( \\ ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], " \\\\  ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], "\\_)) ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "=====", 1);
	}
	if (c == 't' || c == 'T')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], "______ ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], "| || | ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], "  ||   ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], "  ||   ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "=======", 1);
	}
	if (c == 'u' || c == 'U')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], "__ __ ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], "|| || ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], "|| || ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], "\\\\_// ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "======", 1);
	}
	ft_add_vwx(c, title);
}

void			ft_add_pqr(char c, char ***title)
{
	if (c == 'p' || c == 'P')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], "____  ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], "|| \\\\ ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], "|| // ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], "||    ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "======", 1);
	}
	if (c == 'q' || c == 'Q')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], "  ___   ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], " // \\\\  ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], "((   )) ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], " \\\\_/x| ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "========", 1);
	}
	if (c == 'r' || c == 'R')
	{
		(*title)[0] = ft_strjoin_free((*title)[0], "____  ", 1);
		(*title)[1] = ft_strjoin_free((*title)[1], "|| \\\\ ", 1);
		(*title)[2] = ft_strjoin_free((*title)[2], "|| // ", 1);
		(*title)[3] = ft_strjoin_free((*title)[3], "|| \\\\ ", 1);
		(*title)[4] = ft_strjoin_free((*title)[4], "======", 1);
	}
	ft_add_stu(c, title);
}
