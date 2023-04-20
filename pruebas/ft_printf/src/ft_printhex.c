/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:55:09 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/07 16:55:43 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printhex(unsigned long n, const char ph, int *sum)
{
	char	base[17];

	if (ph == 'X')
		ft_strlcpy(base, "0123456789ABCDEF", 17);
	else
		ft_strlcpy(base, "0123456789abcdef", 17);
	if (!n)
		return (0);
	ft_printhex(n / 16, ph, sum);
	write (STDERR_FILENO, &base[n % 16], 1);
	(*sum)++;
	return (1);
}
