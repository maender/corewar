/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:38:37 by edjubert          #+#    #+#             */
/*   Updated: 2019/04/05 10:18:22 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_subtempfree(char **recup, char **line, int fd)
{
	char	*temp;
	int		n;

	n = ft_strchr(recup[fd], '\n') - recup[fd];
	if (!(*line = ft_strsub(recup[fd], 0, n)))
		return (-1);
	if (!(temp = ft_strdup(&recup[fd][n + 1])))
		return (-1);
	if (recup[fd])
		free(recup[fd]);
	recup[fd] = temp;
	return (1);
}

static int	write_line(char **recup, char **line, int fd)
{
	if (!(*line = ft_strdup(recup[fd])))
		return (-1);
	ft_strdel(&recup[fd]);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	int				ret;
	static char		*recup[10240];
	char			buf[BUFF_SIZE_GNL + 1];

	if (fd < 0 || !line || BUFF_SIZE_GNL <= 0)
		return (-1);
	ret = 1;
	while (ret > 0)
	{
		if ((ret = read(fd, buf, BUFF_SIZE_GNL)) < 0)
			return (-1);
		buf[ret] = '\0';
		if (!(recup[fd] = ft_strjoin_free(recup[fd], buf, 1)))
			return (-1);
		if (ft_strchr(recup[fd], '\n') != NULL)
			return (ft_subtempfree(recup, line, fd));
		if (!ret && ft_strchr(recup[fd], '\n') == NULL && recup[fd][0])
			return (write_line(recup, line, fd));
	}
	if (recup[fd])
		ft_strdel(&recup[fd]);
	return (0);
}
