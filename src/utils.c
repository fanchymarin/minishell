/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:55:15 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/18 13:37:39 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_dp(char **dp)
{
	int	i;

	i = 0;
	while (dp[i])
		free(dp[i++]);
	free(dp);
}

char	*ft_getenv(t_list **env, char *name, char *value)
{
	char	*full_name;
	char	**split_name;
	t_list	*line;

	full_name = ft_strjoin(name, "=");
	line = *env;
	while (line)
	{
		if (!ft_strncmp((char *)line->content, full_name, ft_strlen(full_name)))
		{
			free(full_name);
			split_name = ft_split(line->content, '=');
			ft_strlcpy(value, split_name[1], BUF_SIZE);
			free_dp(split_name);
			return (value);
		}
		line = line->next;
	}
	free(full_name);
	return (0);
}

int	cmd_counter(t_cmdtable *rl)
{
	int	i;

	i = 0;
	while (rl->all_cmd[i])
		i++;
	return (i);
}

char	*ft_find_path(char *cmd, t_list **env)
{
	int		i;
	char	**split_path;
	char	*path;
	char	*slashed_cmd;
	char	value_buf[BUF_SIZE];

	if (!cmd)
		return (0);
	if (access(cmd, 0) == 0)
		return (cmd);
	split_path = ft_split(ft_getenv(env, "PATH", value_buf), ':');
	i = 0;
	while (split_path[i])
	{
		slashed_cmd = ft_strjoin(split_path[i], "/");
		path = ft_strjoin(slashed_cmd, cmd);
		free(slashed_cmd);
		if (access(path, 0) == 0)
			return (free_dp(split_path), path);
		free(path);
		i++;
	}
	free_dp(split_path);
	return (0);
}

int	check_blank_line(char *line)
{
	int	i;
	int	quote_counter[2];

	quote_counter[0] = 0;
	quote_counter[1] = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] != DOUBLE_QUOTE)
			quote_counter[0]++;
		else if (line[i] != SIMPLE_QUOTE)
			quote_counter[1]++;
		if (!ft_isblank(line[i]))
			return (1);
	}
	if (quote_counter[0] < 2 || quote_counter[1] < 2)
		return (1);
	return (0);
}
