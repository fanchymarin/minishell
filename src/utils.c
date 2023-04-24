/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:55:15 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/04/24 12:48:35 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status(int value)
{
	return (value << 8);
}

void	close_fds(t_cmdtable *rl)
{
	if (rl->infile)
		(close(rl->infile), rl->infile = 0);
	if (rl->outfile)
		(close(rl->outfile), rl->outfile = 0);
}

void	free_dp(char **dp)
{
	int	i;

	i = 0;
	while (dp[i])
		free(dp[i++]);
	free(dp);
}

int	cmd_counter(char **all_cmd)
{
	int	i;

	i = 0;
	while (all_cmd[i])
		i++;
	return (i);
}

int	check_blank_line(char *line)
{
	int	i;

	if (!ft_strncmp(line, "\"\"\0", 3) || !ft_strncmp(line, "''\0", 3))
		return (0);
	i = -1;
	while (line[++i])
	{
		if (!ft_isblank(line[i]))
			return (1);
	}
	return (0);
}
