/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:00:23 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/09 16:07:05 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_token	*create_token(t_lexer *lex, char *tmp, char *ptr, int type)
{
	t_token	*token;
	char	*str;

	if (!(token = (t_token *)ft_memalloc(sizeof(t_token))))
		exit_error(ERR_LEXICAL, lex, ptr, 0);
	token->content = tmp - ptr > 0 ? ft_strldup(ptr, tmp - ptr) : NULL;
	token->content_size = tmp - ptr;
	token->ptr = ptr;
	str = skip_spaces_only_rev(lex->str, ptr);
	token->nl = (*str && (*str == '\n' || str == lex->str));
	token->line = get_line(lex->str, ptr);
	token->row = get_row(lex->str, ptr);
	tmp = skip_spaces_only(tmp);
	token->el = *tmp == '\n';
	tmp = skip_space_char(tmp);
	token->eof = *tmp == 0;
	token->lex_type = type;
	return (token);
}

void	token_queue(t_token **start, t_token *token)
{
	t_token	*tmp;

	tmp = *start;
	if (!tmp)
		*start = token;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = token;
		token->prev = tmp;
	}
}
