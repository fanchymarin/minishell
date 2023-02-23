/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:44:44 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/23 15:03:06 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	red_pipe_child(t_cmdtable *rl, int i)
{
	// if (rl->here_doc != 0)
	// 	(dup2(rl->here_doc, 0), close(rl->here_doc));
	if (rl->infile)
		(dup2(rl->infile, 0), close(rl->infile));
	if (rl->outfile)
		(dup2(rl->outfile, 1), close(rl->outfile));
	else if (i != rl->n_cmd - 1)
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
	if (WEXITSTATUS(rl->status) == 200)
		(ft_lstclear(rl->env, (*free)), exit(WEXITSTATUS(rl->status)));
	else if (WEXITSTATUS(rl->status) == 201)
		cd_cmd(ft_split(rl->all_cmd[i], ' '));
	else if (WEXITSTATUS(rl->status) == 202)
		rl->env = export_cmd(rl->env, ft_split(rl->all_cmd[i], ' '));
	else if (WEXITSTATUS(rl->status) == 203)
		rl->env = unset_cmd(rl->env, ft_split(rl->all_cmd[i], ' '));
}
