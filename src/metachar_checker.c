/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:40:54 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/01 18:41:48 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	theres_quote(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == SIMPLE_QUOTE)
			return (SIMPLE_QUOTE);
		else if (str[i] == DOUBLE_QUOTE)
			return (DOUBLE_QUOTE);
	}
	return (0);
}

char	*append_quoted(char **cmd, int *i, int quote)
{
	t_list	**head;

	head = malloc(sizeof(t_list *));
	*head = 0;
	ft_memmove(ft_strchr(cmd[*i], quote), ft_strchr(cmd[*i],
			quote) + 1, ft_strlen(ft_strchr(cmd[*i], quote)));
	ft_lstadd_back(head, ft_lstnew(ft_strdup(cmd[(*i)++])));
	ft_lstadd_back(head, ft_lstnew(ft_strdup(" ")));
	while (cmd[*i] && !ft_strchr(cmd[*i], quote))
		(ft_lstadd_back(head, ft_lstnew(ft_strdup(cmd[(*i)++]))),
			ft_lstadd_back(head, ft_lstnew(ft_strdup(" "))));
	ft_memmove(ft_strchr(cmd[*i], quote), ft_strchr(cmd[*i],
			quote) + 1, ft_strlen(ft_strchr(cmd[*i], quote)));
	ft_lstadd_back(head, ft_lstnew(ft_strdup(cmd[(*i)++])));
	return (append_str(head));
}

char	**remove_quotes(char **cmd, char *line, int quote)
{
	char	*quote_loc;
	int		i;

	quote_loc = ft_strchr(line, quote);
	ft_memmove(quote_loc, quote_loc + 1, ft_strlen(quote_loc));
	quote_loc = ft_strchr(line, quote);
	ft_memmove(quote_loc, quote_loc + 1, ft_strlen(quote_loc));
	i = 0;
	while (cmd[i])
		restore_quotes(cmd[i++]);
	return (cmd);
}

char	**struct_quotes(char *old_cmd)
{
	char	**cmd;
	char	**new_cmd;
	int		quote;
	int		i[2];

	cmd = ft_split(old_cmd, ' ');
	quote = theres_quote(old_cmd);
	if (!quote)
		return (cmd);
	new_cmd = ft_calloc(sizeof(char *), cmd_counter(cmd));
	i[0] = 0;
	i[1] = 0;
	while (cmd[i[0]])
	{
		if (ft_strchr(cmd[i[0]], quote))
		{
			if (ft_strchr(cmd[i[0]], quote) != ft_strrchr(cmd[i[0]], quote))
				return (free_dp(new_cmd), remove_quotes(cmd, cmd[i[0]], quote));
			else
				new_cmd[i[1]++] = restore_quotes(
						append_quoted(cmd, &i[0], quote));
			continue ;
		}
		new_cmd[i[1]++] = ft_strdup(cmd[i[0]++]);
	}
	return (free_dp(cmd), new_cmd);
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
		if (!line)
			return (NULL);
		if (line[i] == DOUBLE_QUOTE || line[i] == SIMPLE_QUOTE)
			break ;
	}
	return (line);
}
