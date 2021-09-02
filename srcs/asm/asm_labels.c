/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_labels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdincbud <sdincbud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 12:32:12 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/10 14:56:26 by sdincbud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_label	*create_label(t_token *token)
{
	t_label	*new;

	if (!(new = (t_label*)ft_memalloc(sizeof(t_label))))
		exit(0);
	new->name = ft_strldup(token->content, token->content_size - 1);
	new->address = token->address;
	new->next = NULL;
	return (new);
}

void	label_queue(t_label **lst, t_label *label)
{
	t_label	*tmp;

	tmp = *lst;
	if (!tmp)
		*lst = label;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = label;
	}
}

void	parse_label(t_lexer *lex, t_token **token)
{
	t_token	*tmp;
	char	*str;

	tmp = *token;
	str = tmp->content;
	if (tmp->lex_type != label || !tmp->nl)
		exit_error(ERR_SYNTAX, lex, str, tmp);
	tmp->address = lex->curr_addr;
	label_queue(lex->label, create_label(tmp));
	tmp->type |= T_LAB;
	tmp->address = lex->curr_addr;
	tmp = tmp->next;
	*token = tmp;
}

void	parse_label_param(t_lexer *lex, t_token *token, t_token *instr,
			int type)
{
	char	*str;

	str = token->content;
	str += 1 + (type == T_DIR);
	while (*str)
	{
		if (!ft_strchr(LABEL_CHARS, *str))
			exit_error(ERR_SYNTAX, lex, token->content, token);
		str++;
	}
	token->type |= T_LAB | type;
	token->address = lex->curr_addr;
	token->mem_size = 2;
	if (token->type & T_DIR && !instr->op.carry)
		token->mem_size += 2;
	lex->curr_addr += token->mem_size;
}
