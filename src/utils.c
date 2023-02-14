/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:55:15 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/09 19:07:04 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_dp(char **dp, int status)
{
	int	i;

	i = 0;
	while (dp[i])
		free(dp[i++]);
	free(dp);
	return (status);
}

void	check_in_out_file(t_cmdtable *rl)
{
	int	i;
	int red;

	i = 0;
	red = 0;
	while (rl->all_cmd[rl->n_cmd - 1][i])
	{
		if (rl->all_cmd[rl->n_cmd][i] == '<' || rl->all_cmd[rl->n_cmd][i] == '>')
		{
			if (rl->all_cmd[rl->n_cmd][i] == '<')
				rl->infile = open(&rl->all_cmd[rl->n_cmd][i+1], O_RDONLY);
			else
				rl->outfile = open(&rl->all_cmd[rl->n_cmd][i+1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
			if (rl->outfile == -1 || rl->infile == -1)
				perror("open");
			(i++, red++);
		}
		i++;
	}
}

size_t	cmd_counter(t_cmdtable *rl)
{
	int	i;

	i = 0;
	while (rl->all_cmd[i])
		i++;
	return (i);
}
