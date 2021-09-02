/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdincbud <sdincbud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:03:44 by edjubert          #+#    #+#             */
/*   Updated: 2019/08/11 15:04:12 by sdincbud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	vm_read(int fd, t_champ *new, int i)
{
	new->playerno = i;
	new->flen = lseek(fd, 0, 2);
	if (new->flen - (PROG_NAME_LENGTH + COMMENT_LENGTH + 16) < 3)
		vm_error(7, NULL);
	lseek(fd, 0, 0);
	if (!(new->cor = (unsigned char*)malloc(sizeof(unsigned char)
		* (new->flen + 1))))
		vm_error(3, NULL);
	new->cor[new->flen] = 0;
	read(fd, new->cor, new->flen);
}

void	vm_finish_them(t_champ **champs, t_proc **procs)
{
	t_proc	*tmp;
	t_proc	*past;
	t_champ	*tmp2;
	t_champ *past2;

	tmp = *procs;
	while (tmp)
	{
		past = tmp;
		free(tmp->reg);
		tmp = tmp->next;
		free(past);
	}
	free(tmp);
	tmp2 = *champs;
	while (tmp2)
	{
		past2 = tmp2;
		free(tmp2->cor);
		free(tmp2->title);
		free(tmp2->comment);
		tmp2 = tmp2->next;
		free(past2);
	}
	free(tmp2);
}

void	vm_error(int error, char *str)
{
	static char		*g_ft_errno[14] = {
	"Define error",
	"Open error",
	"Read error",
	"Malloc error",
	"Usage: ./corewar",
	"Visual not possible with dump/print mode",
	"Invalid champion number",
	"Invalid champion size",
	"Invalid magic, not a valid corewar file",
	"Not enough champions",
	"Invalid dump size",
	"Champion number already in use",
	USGMSG,
	"Invalid/too many champion",
	};

	if (str)
		ft_printf("%w%s (%s)\n", STDERR_FILENO, g_ft_errno[error], str);
	else
		ft_putendl_fd(g_ft_errno[error], STDERR_FILENO);
	exit(0);
}

int		main(int ac, char **av)
{
	t_vm		vm;

	if (ac <= 1)
		vm_error(4, NULL);
	check_defines();
	vm_init(&vm);
	vm_args(&vm, ac, av, 1);
	parse_champions(&vm, vm.opt.p);
	init_colors(vm.colors);
	init_arena(&vm, &(vm.champs), &(vm.proc), 0);
	vm_fight(&vm, 0, 0);
	vm_finish_them(&vm.champs, &vm.proc);
	return (0);
}
