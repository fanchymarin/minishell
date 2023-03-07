/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:57:18 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/07 16:55:38 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write (STDERR_FILENO, &c, 1);
	return (1);
}

int	ft_placeholder(va_list ap, const char ph)
{
	int	sum;
	int	hexpt;

	hexpt = 1;
	sum = 0;
	if (ph == 'c')
		sum = ft_printchar(va_arg(ap, int));
	else if (ph == 's')
		sum = ft_printstr(va_arg(ap, char *));
	else if (ph == 'p')
		hexpt = ft_printpt((unsigned long)va_arg(ap, void *), ph, &sum);
	else if (ph == 'd' || ph == 'i')
		ft_printnbr(va_arg(ap, int), &sum);
	else if (ph == 'u')
		ft_printuns(va_arg(ap, unsigned int), &sum);
	else if (ph == 'x' || ph == 'X')
		hexpt = ft_printhex(va_arg(ap, unsigned int), ph, &sum);
	if (!hexpt)
	{
		write (STDERR_FILENO, "0", 1);
		sum++;
	}
	return (sum);
}

int	ft_printf(const char *str, ...)
{
	va_list		ap;
	int			strlen;

	va_start(ap, str);
	strlen = 0;
	while (*str)
	{
		if (*str == '%')
		{
			if (*(++str) == '%')
				strlen += ft_putchar('%');
			else
				strlen += ft_placeholder(ap, *str);
		}
		else
			strlen += ft_putchar(*str);
		++str;
	}
	va_end(ap);
	return (strlen);
}
