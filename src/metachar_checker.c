/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:40:54 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/07 14:56:30 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_closed(char *line, int i, char quote)
{
	int	quotes_counter;
	int	last_quote;

	quotes_counter = 0;
	last_quote = 0;
	while (line[i])
	{
		if (line[i] == quote)
		{
			last_quote = i;
			quotes_counter++;
		}
		i++;
	}
	if (quotes_counter % 2 == 0)
		return (last_quote);
	return (-1);
}

char	*manage_quotes(char *line, int i, char quote)
{
	int	j;

	j = quotes_closed(line, i, quote);
	while (j == -1)
	{
		line = nested_shell(line, &quote);
		if (!line)
			return (NULL);
		j = quotes_closed(line, i, quote);
	}
	return (hide_quoted_metachars(i, j, line, quote));
}

char	*quotes_checker(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[0] == PIPE || (line[i] == PIPE && line[i + 1] == PIPE))
			return (error_msg(PIPE), NULL);
		else if (line[i] == DOUBLE_QUOTE)
			line = manage_quotes(line, i, DOUBLE_QUOTE);
		else if (line[i] == SIMPLE_QUOTE)
			line = manage_quotes(line, i, SIMPLE_QUOTE);
		if (line[i] == DOUBLE_QUOTE || line[i] == SIMPLE_QUOTE)
			break ;
		if (line[i] == PIPE)
			line = manage_pipe(line, &i);
		if (!line)
			return (NULL);
	}
	return (line);
}
