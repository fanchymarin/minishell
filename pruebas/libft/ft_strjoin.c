/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:43:06 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/03/28 15:55:31 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	while (*s1)
		p[i++] = *(s1++);
	while (*s2)
		p[i++] = *(s2++);
	p[i] = 0;
	return (p);
}
