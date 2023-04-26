/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:40:54 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/04/26 13:44:54 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_closed(char *line, int i, char quote)
{
	while (line[++i])
	{
		if (line[i] == quote)
			return (i);
	}
	return (-1);
}

char	*manage_quotes(char *line, int *i, char quote)
{
	int	j;

	j = quotes_closed(line, *i, quote);
	while (j == -1)
	{
		line = append_from_input(line, reading_doc(&quote, 0));
		if (!line)
			return (NULL);
		j = quotes_closed(line, *i, quote);
	}
	return (hide_quoted_metachars(i, j, line, quote));
}

char	*quotes_checker(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[0] == PIPE || (line[i] == PIPE && line[i + 1] == PIPE)
			|| (line[i] == PIPE && !check_blank_line(&line[i + 1])))
			return (free(line), error_msg(PIPE), NULL);
		else if (line[i] == DOUBLE_QUOTE)
			line = manage_quotes(line, &i, DOUBLE_QUOTE);
		else if (line[i] == SIMPLE_QUOTE)
			line = manage_quotes(line, &i, SIMPLE_QUOTE);
		if (!line)
			return (NULL);
	}
	return (line);
}
