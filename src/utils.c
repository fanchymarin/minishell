/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:55:15 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/17 12:44:56 by fmarin-p         ###   ########.fr       */
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

void	free_struct(t_cmdtable *rl)
{
	free_dp(rl->all_cmd);
	free(rl->line);
}

int	cmd_counter(t_cmdtable *rl)
{
	int	i;

	i = 0;
	while (rl->all_cmd[i])
		i++;
	return (i);
}

char	*ft_find_path(char *cmd)
{
	int		i;
	char	**split_path;
	char	*path;
	char	*slashed_cmd;

	if (!cmd)
		return (0);
	if (access(cmd, 0) == 0)
		return (cmd);
	split_path = ft_split(getenv("PATH"), ':');
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

	i = -1;
	while (line[++i])
		if (!ft_isblank(line[i]))
			return (1);
	return (0);
}
