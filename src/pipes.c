/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:44:44 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/17 13:44:45 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	red_pipe_child(t_cmdtable *rl, int i)
{
	if (i == 0 && rl->infile)
		dup2(rl->infile, 0);
	if ((i == (int)rl->n_cmd - 1) && rl->outfile)
		dup2(rl->outfile, 1);
	if (i != (int)rl->n_cmd - 1)
	{
		close(rl->pipe[0]);
		dup2(rl->pipe[1], 1);
		close(rl->pipe[1]);
	}
}

void	parent_process(t_cmdtable *rl, int i)
{
	if (i != rl->n_cmd - 1)
	{
		close(rl->pipe[1]);
		dup2(rl->pipe[0], 0);
		close(rl->pipe[0]);
	}
	wait(&rl->status);
	if (WEXITSTATUS(rl->status) == 1)
		exit(WEXITSTATUS(rl->status));
	else if (WEXITSTATUS(rl->status) == 2)
		cd_cmd(ft_split(rl->all_cmd[i], ' '));
}
