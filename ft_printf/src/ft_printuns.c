/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printuns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 20:25:55 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/07 16:56:10 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printuns(unsigned int n, int *nbrlen)
{
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
