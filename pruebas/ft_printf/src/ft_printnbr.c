/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:44:38 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/07 16:55:52 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printnbr(int n, int *nbrlen)
{
	if (n == -2147483648)
	{
		write (STDERR_FILENO, "-2147483648", 11);
		*nbrlen = 11;
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		write (STDERR_FILENO, "-", 1);
		(*nbrlen)++;
	}
	if (n >= 10)
	{
		ft_printnbr(n / 10, nbrlen);
		ft_printnbr(n % 10, nbrlen);
	}
	else
	{
		n += 48;
		write (STDERR_FILENO, &n, 1);
		(*nbrlen)++;
	}
}
