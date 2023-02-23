/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:40:54 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/23 14:22:21 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quotes_checker(char *line, int i, char quote)
{
	int	j;

	ft_memmove(&line[i], &line[i + 1], ft_strlen(line) - i);
	j = quotes_closed(line, --i, quote);
	while (j == -1)
	{
		line = nested_shell(line, &quote);
		j = quotes_closed(line, i, quote);
	}
	ft_memmove(&line[j], &line[j + 1], ft_strlen(line) - j);
	while (++i < j)
	{
		if (line[i] == PIPE)
			line[i] = 17;
		else if (line[i] == LESS_THAN)
			line[i] = 18;
		else if (line[i] == MORE_THAN)
			line[i] = 19;
		else if (line[i] == DOLLAR && quote == SIMPLE_QUOTE)
			line[i] = 20;
	}
	return (line);
}

char	*metachar_checker(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == DOUBLE_QUOTE)
			line = quotes_checker(line, i, DOUBLE_QUOTE);
		else if (line[i] == SIMPLE_QUOTE)
			line = quotes_checker(line, i, SIMPLE_QUOTE);
		// if (line[i] == DOUBLE_QUOTE || line[i] == SIMPLE_QUOTE)
		// 	break ;
		// else if (line[i] == MORE_THAN)
	}
	return (line);
}
