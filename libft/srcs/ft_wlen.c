/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wlen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:56:33 by edjubert          #+#    #+#             */
/*   Updated: 2018/11/07 16:50:37 by edjubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_wlen(const char *s, int i, char c)
{
	int	wordlen;

	wordlen = 0;
	if (s[i] == c)
		return (0);
	while (s[i] && s[i] != c)
	{
		wordlen++;
		i++;
	}
	return (wordlen);
}
