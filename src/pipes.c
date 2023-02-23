/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:44:44 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/23 17:21:16 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(t_cmdtable *rl, int fd)
{
	close(rl->pipe[fd ^ 1]);
	dup2(rl->pipe[fd], fd);
	close(rl->pipe[fd]);
}

void	red_pipe_child(t_cmdtable *rl, int i)
{
	// if (rl->here_doc != 0)
	// 	(dup2(rl->here_doc, 0), close(rl->here_doc));
	if (rl->infile)
		(dup2(rl->infile, 0), close(rl->infile));
	if (rl->outfile)
		(dup2(rl->outfile, 1), close(rl->outfile));
	else if (i != rl->n_cmd - 1)
		close_pipe(rl, 1);
}

void	parent_process(t_cmdtable *rl, int i)
{
	if (i != rl->n_cmd - 1)
		close_pipe(rl, 0);
	wait(&rl->status);
}
