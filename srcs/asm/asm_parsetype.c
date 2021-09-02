/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parsetype.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdincbud <sdincbud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 12:34:21 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/10 14:54:14 by sdincbud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	parse_command(t_lexer *lex, t_token **token)
{
	t_token *tmp;

	tmp = *token;
	if (!ft_strcmp(tmp->content, NAME_CMD_STRING))
	{
		asm_commandcheck(tmp, lex);
		lex->header |= 1;
		if (!tmp->next || tmp->next->lex_type != string)
			exit_error(ERR_SYNTAX, lex, tmp->ptr, tmp);
		if (!(lex->name = ft_strldup(tmp->next->content + 1,
			ft_strlen(tmp->next->content + 1) - 1)))
			lex->name = ft_strnew(0);
	}
	else
	{
		if (lex->header && (!tmp->prev || tmp->prev->lex_type != endline))
			exit_error(ERR_SYNTAX, lex, tmp->content, tmp);
		lex->header |= 2;
		if (!tmp->next || tmp->next->lex_type != string)
			exit_error(ERR_SYNTAX, lex, tmp->ptr, tmp);
		if (!(lex->comment = ft_strldup(tmp->next->content + 1,
			ft_strlen(tmp->next->content + 1) - 1)))
			lex->comment = ft_strnew(0);
	}
	*token = tmp->next->next;
}

void	parse_register(t_lexer *lex, t_token *token)
{
	char	*str;

	str = token->content;
	str++;
	if (!*str)
		exit_error(ERR_SYNTAX, lex, token->content, token);
	while (*str)
	{
		if (!ft_isdigit(*str))
			exit_error(ERR_SYNTAX, lex, token->content, token);
		str++;
	}
	token->type |= T_REG;
	token->address = lex->curr_addr;
	token->mem_size = 1;
	lex->curr_addr++;
}

void	parse_value(t_lexer *lex, t_token *token, t_token *instr, int type)
{
	char	*str;

	str = token->content;
	str += (type == T_DIR);
	if (*str && *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			exit_error(ERR_SYNTAX, lex, token->content, token);
		str++;
	}
	token->address = lex->curr_addr;
	token->mem_size = 2;
	token->type |= type;
	if (token->type & T_DIR && !instr->op.carry)
		token->mem_size += 2;
	lex->curr_addr += token->mem_size;
}

void	parse_indirect(t_lexer *lex, t_token *token, t_token *instr)
{
	char	*str;

	str = token->content;
	token->type |= T_IND;
	if (*str == LABEL_CHAR)
		parse_label_param(lex, token, instr, T_IND);
	else
		parse_value(lex, token, instr, T_IND);
}

void	parse_direct(t_lexer *lex, t_token *token, t_token *instr)
{
	char	*str;

	str = token->content + 1;
	token->type |= T_DIR;
	if (*str == LABEL_CHAR)
		parse_label_param(lex, token, instr, T_DIR);
	else
		parse_value(lex, token, instr, T_DIR);
}
