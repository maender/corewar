/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_lex_wrap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 15:58:26 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/11 17:01:58 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	lexer_string_quote(t_lexer *lex, char **str)
{
	char	*tmp;
	char	*ptr;

	tmp = *str + 1;
	ptr = *str;
	while (*tmp && *tmp != '"')
		tmp++;
	if (*tmp && *tmp == '"')
		tmp++;
	token_queue(lex->token, create_token(lex, tmp, ptr, string));
	*str = tmp;
}

void	lexer_string_setup(char *ptr, char *tmp, t_token *token)
{
	if (is_digit_string(token->content))
	{
		token->type |= T_IND;
		token->lex_type = param;
	}
	if (*ptr == 'r' && *(ptr + 1))
	{
		while (++ptr < tmp)
			if (!ft_isdigit(*ptr))
				return ;
		token->lex_type = param;
		token->type |= T_REG;
	}
}

void	lexer_string(t_lexer *lex, char **str)
{
	t_token	*token;
	char	*ptr;
	char	*tmp;
	int		lab;

	tmp = *str;
	ptr = *str;
	lab = 0;
	while (*tmp && ft_strchr(LABEL_CHARS, *tmp))
		tmp++;
	if (*tmp && *tmp == LABEL_CHAR && (lab = 1) > 0)
		tmp++;
	token = create_token(lex, tmp, ptr, lab ? label : instruction);
	token->type |= lab ? T_LAB : 0;
	token_queue(lex->token, token);
	*str = tmp;
	lexer_string_setup(ptr, tmp, token);
}

void	lexer_char(t_lexer *lex, char **tmp)
{
	char *str;

	str = *tmp;
	if (*str == ';' || *str == COMMENT_CHAR)
		str = newline(str);
	else if (*str == LABEL_CHAR)
		lexer_label(lex, &str, 0);
	else if (ft_strchr(LABEL_CHARS, *str))
		lexer_string(lex, &str);
	else if (*str == '-')
		lexer_value(lex, &str, 0);
	else if (*str == DIRECT_CHAR)
		lexer_direct(lex, &str);
	else if (*str == SEPARATOR_CHAR)
	{
		token_queue(lex->token, create_token(lex, str + 1, str,
			separator_operator));
		str++;
	}
	else
		exit_error(ERR_LEXICAL, lex, str, 0);
	*tmp = str;
}

void	corewar_lexer(t_lexer *lex)
{
	char	*str;

	str = lex->str;
	while (*str)
	{
		str = skip_spaces_only(str);
		if (!*str)
			break ;
		else if (*str == '.')
		{
			if (!lexer_command(lex, &str))
				break ;
		}
		else if (*str == '\n')
		{
			token_queue(lex->token, create_token(lex, str + 1, str, endline));
			str++;
		}
		else if (*str == '"')
			lexer_string_quote(lex, &str);
		else
			lexer_char(lex, &str);
	}
	token_queue(lex->token, create_token(lex, str, str, 0));
}
