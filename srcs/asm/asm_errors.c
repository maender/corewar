/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdincbud <sdincbud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 17:26:13 by sdincbud          #+#    #+#             */
/*   Updated: 2019/08/11 15:02:25 by sdincbud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_cmd_error(int err_code, t_token *lst)
{
	int		i;
	char	*content;

	i = 0;
	content = (char*)lst->content;
	while (is_space(content[i]))
		i++;
	if (err_code == ERR_CMD_UNKNOWN)
		ft_printf("{yellow}Command {red}'%s'{yellow} not found ", &content[i]);
	else if (err_code == ERR_LABEL_UNKNOWN)
		ft_printf("{yellow}Label {red}'%s'{yellow} not found ", &content[i]);
	ft_printf("[ {green}%d{yellow} : ", lst->line);
	ft_printf("{green}%d{yellow} ]{eoc}\n", i + 1);
}

void	exit_error(int err_code, t_lexer *lex, char *str, t_token *token)
{
	if (err_code == ERR_LEXICAL)
		ft_printf("Lexical error at [%d:%d]\n", get_line(lex->str, str),
			get_row(lex->str, str));
	if (err_code == ERR_SYNTAX || err_code == ERR_LABEL_UNKNOWN
		|| err_code == ERR_BAD_INSTRUCTION || err_code == ERR_ENDLINE)
	{
		handle_conditions(err_code, str, token);
		ft_printf("token [TOKEN][%03d:%03d] ", get_line(lex->str, token->ptr),
			get_row(lex->str, token->ptr));
		if (token->lex_type == endline)
		{
			ft_printf("ENDLINE\n");
			exit(err_code);
		}
		handle_exit(str, token);
		ft_printf(" \"%s\"\n", token->content);
	}
	if (err_code == ERR_INVALID_PARAM)
		handle_invalid(str, token, lex);
	if (err_code == ERR_NUM_PARAM)
		ft_printf("Invalid parameter count for instruction %s\n", str);
	if (err_code == ERR_FILE_EXT)
		ft_printf("Bad file extention, please try with \".s\" file\n");
	err_code != ERR_FILE_EXT ? free_env(lex) : 0;
	exit(err_code);
}

void	exit_usage(t_env *env)
{
	print_usage(env);
	free_env(&env->lexer);
	exit(1);
}
