/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:04:26 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/03/28 19:30:56 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_allocnum(int n, int neg)
{
	int	i;

	i = 0;
	while (n)
	{
		++i;
		n /= 10;
	}
	if (neg)
		++i;
	return (i);
}

static char	*ft_itoa2(int n, char *p, int i, int neg)
{
	p[i--] = 0;
	if (neg)
		*p = '-';
	if (n == -2147483648)
	{
		*(p + 1) = 50;
		n = 147483648;
	}
	while (n)
	{
		p[i--] = n % 10 + 48;
		n /= 10;
	}
	return (p);
}

char	*ft_itoa(int n)
{
	int		i;
	int		neg;
	char	*p;

	neg = 0;
	if (n == 0)
	{
		p = (char *) malloc(sizeof(char) + 1);
		*p = 48;
		*(p + 1) = 0;
		return (p);
	}
	if (n < 0)
	{
		neg = 1;
		n *= -1;
	}
	i = ft_allocnum(n, neg);
	p = (char *) malloc(sizeof(char) * i + 1);
	if (!p)
		return (0);
	return (ft_itoa2(n, p, i, neg));
}
