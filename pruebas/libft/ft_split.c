/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:05:18 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/03/30 20:53:50 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_malloc_error(char **p)
{
	unsigned int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (0);
}

static char	**ft_allocdbpt(char const *s, char c)
{
	int		i;
	int		count;
	char	**p;

	count = 0;
	while (*s)
	{
		i = 0;
		while (*s != c && *s)
		{
			++i;
			++s;
		}
		if (i)
			++count;
		if (*s)
			++s;
	}
	p = (char **) malloc(sizeof(char *) * (count + 1));
	if (!p)
		return (0);
	p[count] = 0;
	return (p);
}

static int	ft_allocpt(char const *s, char **p, int i, int i2)
{
	int	i3;

	p[i2] = (char *) malloc(sizeof(char) * (i + 1));
	if (!p[i2])
		return (0);
	p[i2][i] = 0;
	i3 = 0;
	while (i)
		p[i2][i3++] = *(s - i--);
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	int		i;
	int		i2;

	if (!s)
		return (0);
	p = ft_allocdbpt(s, c);
	if (!p)
		return (0);
	i2 = 0;
	while (*s)
	{
		i = 0;
		while (*s != c && *s)
		{
			++i;
			++s;
		}
		if (i)
			if (!ft_allocpt(s, p, i, i2++))
				return (ft_malloc_error(p));
		if (*s)
			++s;
	}
	return (p);
}
