/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:01:01 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/02 19:00:34 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	int		i2;

	if (!needle && !haystack)
		return (0);
	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && len)
	{
		if (haystack[i] == *needle)
		{	
			i2 = 0;
			while (haystack[i + i2] == needle[i2])
			{
				i2++;
				if (!needle[i2] && len >= (size_t)i2)
					return ((char *)&haystack[i]);
			}
		}
		++i;
		--len;
	}
	return (0);
}
