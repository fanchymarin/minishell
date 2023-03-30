/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 19:15:16 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/07 16:56:00 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(STDERR_FILENO, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		write (STDERR_FILENO, &str[i], 1);
		++i;
	}
	return (i);
}
