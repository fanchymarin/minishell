/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:49:23 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/04/19 18:53:36 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char	*p;

	if (c > 255)
		c -= 256;
	while (*s)
	{
		if (*s == c)
		{
			p = (char *)s;
			return (p);
		}
		s++;
	}
	if (c == 0)
	{
		p = (char *)s;
		return (p);
	}
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	void	*p2;
	int		i;

	if (size > ((size_t) - 1) / 2 && count > ((size_t) - 1) / 2)
		return (0);
	p = (void *)malloc(size * count);
	if (!p)
		return (0);
	i = size * count;
	p2 = p;
	while (i--)
		*(char *)p2++ = 0;
	return (p);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		i;

	if (!s1 || !s2)
		return (0);
	p = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!p)
		return (0);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		++i;
	}
	while (*s2)
		p[i++] = *(s2++);
	p[i] = 0;
	return (p);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}
