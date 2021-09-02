/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 18:59:14 by sdincbud          #+#    #+#             */
/*   Updated: 2019/08/11 17:02:23 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_param(t_lexer *lex, t_token *token, t_token *instr, int i)
{
	if (i >= instr->op.num_args)
		exit_error(ERR_INVALID_PARAM, lex, token->content, instr);
	if (token->lex_type == param && token->type & T_REG
		&& instr->op.args[i] & T_REG)
		parse_register(lex, token);
	else if (token->lex_type == param && token->type & T_DIR
		&& instr->op.args[i] & T_DIR)
		parse_direct(lex, token, instr);
	else if (token->lex_type == param && token->type & T_IND
		&& instr->op.args[i] & T_IND)
		parse_indirect(lex, token, instr);
	else if (token->lex_type == param)
		exit_error(ERR_INVALID_PARAM, lex, token->content, instr);
	else
		exit_error(ERR_SYNTAX, lex, token->content, token);
}

void	parse_params(t_lexer *lex, t_token **token)
{
	t_token	*tmp;
	t_token	*instr;

	instr = *token;
	tmp = *token;
	tmp = tmp->next;
	if (!tmp || tmp->lex_type != param)
		exit_error(ERR_SYNTAX, lex, tmp->content, tmp);
	lex->param_count = 0;
	while (tmp && tmp->lex_type != endline)
	{
		parse_start_check(tmp, lex);
		if (tmp->lex_type == separator_operator)
			tmp = tmp->next;
		if (!tmp || tmp->lex_type != param)
			exit_error(ERR_SYNTAX, lex, tmp->content, tmp);
		check_param(lex, tmp, instr, lex->param_count);
		lex->param_count++;
		tmp = tmp->next;
		if (tmp->lex_type == endline)
			break ;
	}
	parse_end_check(tmp, instr, lex);
	tmp = tmp->next;
	*token = tmp;
}

void	parse_instruction(t_lexer *lex, t_token **token)
{
	t_token	*tmp;
	char	*str;

	tmp = *token;
	str = tmp->content;
	tmp->op.name = str;
	if (!is_command(&tmp->op))
		exit_error(ERR_BAD_INSTRUCTION, lex, str, tmp);
	tmp->address = lex->curr_addr;
	tmp->mem_size = tmp->op.args_mask ? 2 : 1;
	lex->curr_addr += tmp->mem_size;
	parse_params(lex, token);
	lex->at_least_one = 1;
}

void	parse_label_string(t_lexer *lex, t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if (tmp->type == T_LAB)
		parse_label(lex, token);
	else
		parse_instruction(lex, token);
}

void	corewar_parser(t_lexer *lex)
{
	t_token	*token;

	token = *lex->token;
	lex->header = 0;
	while (token)
	{
		if (token->lex_type == command)
			parse_command(lex, &token);
		else if (token->lex_type == label && lex->header == 3)
			parse_label(lex, &token);
		else if (token->lex_type == instruction && lex->header == 3)
			parse_instruction(lex, &token);
		else if (!token->lex_type && lex->header == 3)
			break ;
		else if (!token->lex_type || token->lex_type == string)
			exit_error(ERR_SYNTAX, lex, token->content, token);
		else if (token->lex_type == endline)
			token = token->next;
		else
			exit_error(ERR_SYNTAX, lex, token->content, token);
	}
	if (!lex->at_least_one)
		exit_error(ERR_SYNTAX, lex, token->content, token);
}
