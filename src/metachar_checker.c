/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:40:54 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/01 15:08:31 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	theres_quote(char *str, char quote)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!quote)
		{	
			if (str[i] == SIMPLE_QUOTE)
				return (SIMPLE_QUOTE);
			else if (str[i] == DOUBLE_QUOTE)
				return (DOUBLE_QUOTE);
		}
		else
			if (str[i] == quote)
				return (ft_memmove(&str[i], &str[i + 1], ft_strlen(str) - i),
					quote);
	}
	return (0);
}

char	*append_quoted(char **cmd, int *i, int quote)
{
	t_list	**head;

	head = malloc(sizeof(t_list *));
	*head = 0;
	ft_lstadd_back(head, ft_lstnew(ft_strdup(cmd[(*i)++])));
	ft_lstadd_back(head, ft_lstnew(ft_strdup(" ")));
	while (theres_quote(cmd[*i], quote) != quote && cmd[*i])
		(ft_lstadd_back(head, ft_lstnew(ft_strdup(cmd[(*i)++]))),
			ft_lstadd_back(head, ft_lstnew(ft_strdup(" "))));
	theres_quote(cmd[*i], quote);
	ft_lstadd_back(head, ft_lstnew(ft_strdup(cmd[(*i)++])));
	return (append_str(head));
}

char	**struct_quotes(char *old_cmd)
{
	char	**cmd;
	char	**new_cmd;
	int		quote;
	int		i;
	int		j;

	cmd = ft_split(old_cmd, ' ');
	quote = theres_quote(old_cmd, 0);
	if (!quote)
		return (cmd);
	new_cmd = ft_calloc(sizeof(char *), cmd_counter(cmd));
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (theres_quote(cmd[i], quote) == quote)
		{
			new_cmd[j++] = restore_metachar(append_quoted(cmd, &i, quote), 1);
			continue ;
		}
		new_cmd[j++] = ft_strdup(cmd[i++]);
	}
	free_dp(cmd);
	return (new_cmd);
}

char	*manage_quotes(char *line, int i, char quote)
{
	int	j;

	j = quotes_closed(line, i, quote);
	while (j == -1)
	{
		line = nested_shell(line, &quote);
		j = quotes_closed(line, i, quote);
	}
	while (++i < j)
	{
		if (line[i] == PIPE)
			line[i] = -1;
		else if (line[i] == LESS_THAN)
			line[i] = -2;
		else if (line[i] == MORE_THAN)
			line[i] = -3;
		else if (line[i] == DOLLAR && quote == SIMPLE_QUOTE)
			line[i] = -4;
		else if (line[i] == SIMPLE_QUOTE)
			line[i] = -5;
		else if (line[i] == DOUBLE_QUOTE)
			line[i] = -6;
	}
	return (line);
}

char	*quotes_checker(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == DOUBLE_QUOTE)
			line = manage_quotes(line, i, DOUBLE_QUOTE);
		else if (line[i] == SIMPLE_QUOTE)
			line = manage_quotes(line, i, SIMPLE_QUOTE);
		if (line[i] == DOUBLE_QUOTE || line[i] == SIMPLE_QUOTE)
			break ;
	}
	return (line);
}
