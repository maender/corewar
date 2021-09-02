/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_output_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 13:27:32 by edjubert          #+#    #+#             */
/*   Updated: 2019/08/10 15:20:53 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_byte(int fd, unsigned int bit, int shift)
{
	if (shift == 4)
	{
		ft_printf("%w%c", fd, (bit >> 24) % 256);
		ft_printf("%w%c", fd, (bit >> 16) % 256);
	}
	if (shift >= 2)
		ft_printf("%w%c", fd, (bit >> 8) % 256);
	ft_printf("%w%c", fd, bit % 256);
}

void	print_zero_byte(int fd, int start, int loop_nb)
{
	int	i;

	i = start - 1;
	while (++i < loop_nb)
		ft_printf("%w%c", fd, 0);
}

int		create_file(t_env *env, char *src)
{
	int		fd;
	char	*tmp;

	tmp = ft_strldup(src, ft_strlen(src) - 2);
	env->path = ft_strjoin_free(tmp, ".cor", 1);
	if (!(fd = open(env->path, O_WRONLY | O_TRUNC | O_CREAT, 0666)))
		return (-1);
	return (fd);
}

void	print_ind_output(int fd, t_token *tmp, t_label *label, t_token *param)
{
	char			*str;
	unsigned int	toprint;

	str = tmp->content;
	if (tmp->type & T_LAB)
	{
		while (label && (ft_strncmp(str + 1, label->name,
					ft_strlen(label->name)) || ft_strncmp(str + 1,
					label->name, ft_strlen(str))))
			label = label->next;
		toprint = label->address - param->address;
		print_byte(fd, toprint, 2);
	}
	else
	{
		toprint = ft_atol(str);
		print_byte(fd, toprint, 2);
	}
}

void	print_dir_output(int fd, t_token *tmp, t_label *label,
	t_token *param)
{
	char			*str;
	unsigned int	toprint;

	str = tmp->content;
	if (tmp->type & T_LAB)
	{
		while (label && (ft_strncmp(str + 2, label->name,
					ft_strlen(label->name)) || ft_strncmp(str + 2,
					label->name, ft_strlen(str))))
			label = label->next;
		toprint = label->address - param->address;
		print_byte(fd, toprint, param->op.carry ? 2 : 4);
	}
	else
	{
		toprint = ft_atol(str + 1);
		print_byte(fd, toprint, param->op.carry ? 2 : 4);
	}
}
