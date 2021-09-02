/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 12:45:57 by maabou-h          #+#    #+#             */
/*   Updated: 2019/08/11 17:39:08 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	init_check_opt(t_env *env)
{
	if (env->opt & OP_LABELS)
		print_labels(env);
	if (env->opt & OP_PRINT)
		print_lst(env, env->debug_fd);
	if (env->opt & OP_CHAIN)
		print_tokens(*env->lexer.token);
	if (env->opt & OP_COREF)
		print_color_ref(env);
}
