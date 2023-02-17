/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:40:54 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/17 19:09:11 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
char	*expand_env(char *line)
{
	int		i;
	int		j;
	char	*var;

	i = -1;
	while (line[++i])
	{
		if (line[i] == DOLLAR)
		{
			j = i;
			while (ft_isalnum(line[++i]))
				;
			var = ft_substr(line, j + 1, i);
		}
	}
	return (line);
}*/

char	*restore_metachar(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == 17)
			line[i] = PIPE;
		else if (line[i] == 18)
			line[i] = LESS_THAN;
		else if (line[i] == 19)
			line[i] = MORE_THAN;
		else if (line[i] == 20)
			line[i] = DOLLAR;
	}
	return (line);
}

char	**expand_metachar(char **rev_cmd)
{
	int	i;

	i = -1;
	while (rev_cmd[++i])
	{
//		rev_cmd[i] = expand_env(rev_cmd[i]);
		rev_cmd[i] = restore_metachar(rev_cmd[i]);
	}
	return (rev_cmd);
}

int	quotes_closed(char *line, int i, char quote)
{
	while (line[++i])
		if (line[i] == quote)
			return (i);
	return (-1);
}

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
		if (line[i] == DOUBLE_QUOTE || line[i] == SIMPLE_QUOTE)
			break ;
	}
	return (line);
}
