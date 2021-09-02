/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdincbud <sdincbud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 16:41:35 by sdincbud          #+#    #+#             */
/*   Updated: 2019/08/11 15:18:23 by sdincbud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		lexer_command(t_lexer *lex, char **str)
{
	char	*tmp;
	char	*ptr;

	tmp = *str;
	ptr = *str;
	if (!ft_strncmp(tmp, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
	{
		if (lex->header & 1)
			return (0);
		lex->header |= 1;
		tmp += ft_strlen(NAME_CMD_STRING);
	}
	else if (!ft_strncmp(tmp, COMMENT_CMD_STRING,
		ft_strlen(COMMENT_CMD_STRING)))
	{
		if (lex->header & 2)
			return (0);
		lex->header |= 2;
		tmp += ft_strlen(COMMENT_CMD_STRING);
	}
	else
		exit_error(ERR_LEXICAL, lex, tmp, 0);
	token_queue(lex->token, create_token(lex, tmp, ptr, command));
	*str = tmp;
	return (1);
}

void	lexer_label(t_lexer *lex, char **str, int type)
{
	t_token	*token;
	char	*tmp;
	char	*ptr;

	tmp = *str + 1 + (type == 1);
	ptr = *str;
	if (!*tmp || !ft_strchr(LABEL_CHARS, *tmp))
		exit_error(ERR_LEXICAL, lex, ptr, 0);
	while (*tmp && !is_space(*tmp) && *tmp != COMMENT_CHAR && *tmp != ';'
		&& *tmp != LABEL_CHAR && *tmp != SEPARATOR_CHAR && *tmp != DIRECT_CHAR)
	{
		if (!ft_strchr(LABEL_CHARS, *tmp))
			exit_error(ERR_LEXICAL, lex, tmp, 0);
		tmp++;
	}
	token = create_token(lex, tmp, ptr, param);
	token->type |= (type ? T_DIR : T_IND) | T_LAB;
	token_queue(lex->token, token);
	*str = tmp;
}

void	lexer_value(t_lexer *lex, char **str, int type)
{
	t_token	*token;
	char	*tmp;
	char	*ptr;

	tmp = *str + (type == 1);
	ptr = *str;
	if (*tmp == '-')
		tmp++;
	if (!*tmp || !ft_isdigit(*tmp))
		exit_error(ERR_LEXICAL, lex, ptr, NULL);
	while (*tmp && ft_isdigit(*tmp))
		tmp++;
	token = create_token(lex, tmp, ptr, param);
	token->type |= (type ? T_DIR : T_IND);
	token_queue(lex->token, token);
	*str = tmp;
}

void	lexer_direct(t_lexer *lex, char **str)
{
	char	*tmp;
	char	*ptr;

	tmp = *str + 1;
	ptr = *str;
	if (!*tmp || (*tmp != LABEL_CHAR && !ft_isdigit(*tmp) && *tmp != '-'))
		exit_error(ERR_LEXICAL, lex, ptr, 0);
	if (*tmp == LABEL_CHAR)
		lexer_label(lex, str, 1);
	else
		lexer_value(lex, str, 1);
}
