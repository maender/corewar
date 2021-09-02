/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parsechecks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 12:38:05 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/10 12:57:06 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	parse_start_check(t_token *tmp, t_lexer *lex)
{
	if (tmp->lex_type != param && tmp->lex_type != separator_operator)
		exit_error(ERR_SYNTAX, lex, tmp->content, tmp);
	if (lex->param_count > 0 && tmp->lex_type != separator_operator)
		exit_error(ERR_SYNTAX, lex, tmp->content, tmp);
}

void	parse_end_check(t_token *tmp, t_token *instr, t_lexer *lex)
{
	if (tmp && tmp->lex_type != endline)
		exit_error(ERR_SYNTAX, lex, tmp->next->content, instr);
	if (lex->param_count != instr->op.num_args)
		exit_error(ERR_NUM_PARAM, lex, instr->content, instr);
}

void	asm_commandcheck(t_token *tmp, t_lexer *lex)
{
	if (lex->header && (!tmp->prev || tmp->prev->lex_type != endline))
		exit_error(ERR_SYNTAX, lex, tmp->content, tmp);
}
