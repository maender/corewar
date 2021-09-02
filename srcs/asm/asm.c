/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:04:48 by edjubert          #+#    #+#             */
/*   Updated: 2019/08/11 17:31:38 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_digit_string(char *str)
{
	if (*str && *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int		check_prog(t_env *env)
{
	t_token	*tmp;

	tmp = env->lst;
	while (tmp)
		tmp = tmp->next;
	return (1);
}

char	*get_file_content(char *av)
{
	int		fd;
	size_t	len;
	char	*str;

	if (ft_strcmp(av + ft_strlen(av) - 2, ".s"))
		exit_error(ERR_FILE_EXT, NULL, NULL, NULL);
	fd = open(av, 0);
	if (fd < 0)
	{
		ft_printf("Can't read source file %s\n", av);
		exit(1);
	}
	len = lseek(fd, 0, 2);
	lseek(fd, 0, 0);
	if (!(str = (char*)ft_memalloc(len + 1)))
		exit(1);
	str[len] = 0;
	read(fd, str, len);
	close(fd);
	return (str);
}

int		main(int ac, char **av)
{
	int		fd;
	t_token	*token;
	t_label	*label;
	t_env	env;

	token = NULL;
	label = NULL;
	ft_bzero(&env, sizeof(t_env));
	ft_bzero(&env.lexer, sizeof(t_lexer));
	env.lexer.token = &token;
	env.lexer.label = &label;
	env.debug_fd = 1;
	get_options(&env, ac, av);
	env.lexer.str = get_file_content(av[ac - 1]);
	get_prog(&env.lexer);
	init_check_opt(&env);
	fd = create_file(&env, av[ac - 1]);
	if (fd == -1)
		exit(0);
	if (env.opt == 0)
		writing_binary(fd, &env);
	ft_strdel(&env.path);
	return (free_env(&env.lexer));
}
