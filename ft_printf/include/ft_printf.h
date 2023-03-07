/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 15:22:00 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/04/01 15:24:03 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

int		ft_printf(const char *format, ...);
void	ft_printnbr(int n, int *nbrlen);
void	ft_printuns(unsigned int n, int *nbrlen);
int		ft_printchar(char c);
int		ft_printstr(char *str);
int		ft_printhex(unsigned long n, const char ph, int *sum);
int		ft_printpt(unsigned long n, const char ph, int *sum);

#endif
