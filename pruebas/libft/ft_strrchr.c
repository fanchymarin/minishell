/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:45:03 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/03/29 14:45:58 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		strlen;
	char	*p;

	if (c > 255)
		c -= 256;
	strlen = ft_strlen(s);
	s = &s[strlen];
	while (strlen + 1)
	{
		if (*s == c)
		{
			p = (char *)s;
			return (p);
		}
		strlen--;
		s--;
	}
	return (0);
}
