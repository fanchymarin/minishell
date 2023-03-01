/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 21:10:26 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/01 21:17:54 by fmarin-p         ###   ########.fr       */
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
	return (restore_quotes(append_str(head)));
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
				new_cmd[i[1]++] = append_quoted(cmd, &i[0], quote);
			continue ;
		}
		new_cmd[i[1]++] = ft_strdup(cmd[i[0]++]);
	}
	return (free_dp(cmd), new_cmd);
}
