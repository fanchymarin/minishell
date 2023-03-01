/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_restore.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:15:22 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/01 16:49:44 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*restore_quotes(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == -5)
			line[i] = SIMPLE_QUOTE;
		else if (line[i] == -6)
			line[i] = DOUBLE_QUOTE;
	}
	return (line);
}

char	*restore_vars(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == -4)
			line[i] = DOLLAR;
	}
	return (line);
}

char	*restore_pipes(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == -1)
			line[i] = PIPE;
		else if (line[i] == -2)
			line[i] = LESS_THAN;
		else if (line[i] == -3)
			line[i] = MORE_THAN;

	}
	return (line);
}
