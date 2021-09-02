/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:38:08 by sdincbud          #+#    #+#             */
/*   Updated: 2019/08/11 17:03:00 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_label(t_token *token, t_label *label)
{
	char	*str;

	str = token->content + 1 + ((token->type & T_DIR) > 0);
	while (label)
	{
		if (!ft_strcmp(str, label->name))
			return (1);
		label = label->next;
	}
	return (0);
}

void	check_all_labels(t_lexer *lex)
{
	t_token	*token;
	t_label	*label;

	token = *lex->token;
	label = *lex->label;
	while (token)
	{
		if (token->type & T_LAB && (token->type & T_DIR || token->type & T_IND))
		{
			if (!is_label(token, label))
				exit_error(ERR_LABEL_UNKNOWN, lex, token->content, token);
		}
		token = token->next;
	}
}

t_token	*del_one(t_token **start, t_token *token)
{
	t_token	*out;

	if (!token->prev)
	{
		*start = token->next;
		token->next->prev = NULL;
	}
	else
	{
		token->prev->next = token->next;
		token->next->prev = token->prev;
	}
	out = token->prev ? token->prev : token->next;
	ft_strdel(&token->content);
	ft_memdel((void**)&token);
	return (out);
}

void	cut_head(t_lexer *lex)
{
	t_token	*token;
	t_token	*tmp;

	token = *lex->token;
	while (token)
	{
		if (token->lex_type == command)
		{
			tmp = token->next;
			*lex->token = token->next->next;
			token->next->next->prev = NULL;
			ft_strdel(&token->content);
			ft_memdel((void**)&token);
			ft_strdel(&tmp->content);
			ft_memdel((void**)&tmp);
			token = *lex->token;
		}
		else if (token->lex_type == separator_operator
			|| token->lex_type == endline)
			token = del_one(lex->token, token);
		else
			token = token->next;
	}
}

void	get_prog(t_lexer *lex)
{
	corewar_lexer(lex);
	corewar_parser(lex);
	cut_head(lex);
	check_all_labels(lex);
	return ;
}
