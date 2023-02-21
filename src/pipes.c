/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:44:44 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/21 16:32:31 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	red_pipe_child(t_cmdtable *rl, int i)
{
	if (i == 0 && rl->infile)
		dup2(rl->infile, 0);
	if ((i == rl->n_cmd - 1) && rl->outfile)
		dup2(rl->outfile, 1);
	if (i != rl->n_cmd - 1)
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
	if (WEXITSTATUS(rl->status) == 10)
		(ft_lstclear(rl->env, (*free)), exit(WEXITSTATUS(rl->status)));
	else if (WEXITSTATUS(rl->status) == 11)
		cd_cmd(ft_split(rl->all_cmd[i], ' '));
	else if (WEXITSTATUS(rl->status) == 12)
		rl->env = export_cmd(rl->env, ft_split(rl->all_cmd[i], ' '));
	else if (WEXITSTATUS(rl->status) == 13)
		rl->env = unset_cmd(rl->env, ft_split(rl->all_cmd[i], ' '));
}
