/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printpt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:51:17 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/07 16:55:55 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printpt(unsigned long n, const char ph, int *sum)
{
	write (STDERR_FILENO, "0x", 2);
	*sum += 2;
	return (ft_printhex(n, ph, sum));
}
