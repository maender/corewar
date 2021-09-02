/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_errors_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabou-h <maabou-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 15:05:31 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/09 15:07:15 by maabou-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	handle_printerr(char *str)
{
	ft_printf(str[ft_strlen(str) - 1] == LABEL_CHAR
				? "LABEL" : "INDIRECT");
}

void	handle_exit(char *str, t_token *token)
{
	if (!str && token->eof)
		ft_printf("END");
	else if (token->lex_type == string)
		ft_printf("STRING");
	else if (token->lex_type == instruction)
		ft_printf("INSTRUCTION");
	else if (token->lex_type == command)
		ft_printf("COMMAND_%s", ft_strcmp(str, NAME_CMD_STRING)
			? "COMMENT" : "NAME");
	else if (token->lex_type == separator_operator)
		ft_printf("SEPARATOR");
	else
	{
		if (*str && *str == 'r')
			ft_printf("REGISTER");
		else if (*str && *str == DIRECT_CHAR)
		{
			str++;
			ft_printf("DIRECT");
		}
		else if (*str && *str != 'r')
			handle_printerr(str);
		if (*str && *str == LABEL_CHAR)
			ft_printf("_LABEL");
	}
}

void	handle_invalid(char *str, t_token *token, t_lexer *lex)
{
	ft_printf("Invalid parameter %d type ", lex->param_count);
	if (*str == DIRECT_CHAR)
		ft_printf("direct");
	else
		ft_printf(*str == 'r' ? "register" : "indirect");
	ft_printf(" for instruction %s\n", token->content);
}

void	handle_conditions(int err_code, char *str, t_token *token)
{
	if (err_code == ERR_BAD_INSTRUCTION)
		ft_printf("Invalid instruction at ");
	else
		ft_printf(err_code == ERR_LABEL_UNKNOWN
			? "No such label %s while attempting to dereference "
			: "Syntax error at ", str + ((token->type & T_DIR) > 0) + 1);
}
