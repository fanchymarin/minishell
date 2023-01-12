/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:16:31 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/03/29 15:20:29 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	num;
	int	neg;

	num = 0;
	neg = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		++str;
	if (*str == 45 || *str == 43)
	{
		if (*str == 45)
			neg = -1;
		++str;
	}
	while (*str >= 48 && *str <= 57)
	{
		num = num * 10 + (*str - 48);
		if (*str - 48 != num % 10 && num != -2147483648)
		{
			if (neg == -1)
				return (0);
			return (-1);
		}
		++str;
	}
	return (num * neg);
}
