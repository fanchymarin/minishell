/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:23:59 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/03/24 16:22:13 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	void	*p2;
	int		i;

	p = (void *)malloc(size * count);
	if (!p)
		return (0);
	i = size * count;
	p2 = p;
	while (i--)
		*(char *)p2++ = 0;
	return (p);
}
