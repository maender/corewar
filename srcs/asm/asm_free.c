/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdincbud <sdincbud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 12:31:02 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/11 14:57:48 by sdincbud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	free_tokens(t_token **lst)
{
	t_token	*tmp;
	t_token	*list;

	list = *lst;
	while (list)
	{
		tmp = list;
		list = list->next;
		ft_strdel((char**)&tmp->content);
		ft_memdel((void**)&tmp);
	}
	*lst = NULL;
}

void	free_labels(t_label **lst)
{
	t_label	*tmp;
	t_label	*list;

	list = *lst;
	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->name)
			ft_strdel(&tmp->name);
		ft_memdel((void**)&tmp);
	}
	*lst = NULL;
}

int		free_env(t_lexer *lexer)
{
	if (lexer->name)
		ft_strdel(&lexer->name);
	if (lexer->comment)
		ft_strdel(&lexer->comment);
	if (lexer->str)
		ft_strdel(&lexer->str);
	free_tokens(lexer->token);
	free_labels(lexer->label);
	return (0);
}
