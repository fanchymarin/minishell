/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:44:44 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/24 11:50:40 by fmarin-p         ###   ########.fr       */
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
	if (rl->fd_tmp)
	{
		rl->fd_tmp = open(".tmp", O_RDONLY);
		(dup2(rl->fd_tmp, 0), close(rl->fd_tmp));
	}
	else if (rl->infile)
		(dup2(rl->infile, 0), close(rl->infile));
	if (rl->outfile)
		(dup2(rl->outfile, 1), close(rl->outfile));
	else if (i != rl->n_cmd - 1)
		close_pipe(rl, 1);
}

void	exec_command_child(t_cmdtable *rl, char **cmd)
{
	if (!ft_strncmp(cmd[0], "pwd\0", 4))
		pwd_cmd();
	else if (!ft_strncmp(cmd[0], "echo\0", 5))
		echo_cmd(cmd);
	else if (!ft_strncmp(cmd[0], "env\0", 4))
		env_cmd(rl->env);
	else
		execve_cmd(rl->env, ft_find_path(cmd[0], rl->env), cmd);
	free_dp(cmd);
	free_dp(rl->all_cmd);
	free(rl->line);
	exit(0);
}

void	fork_process(t_cmdtable *rl, int i)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
		(red_pipe_child(rl, i),
			exec_command_child(rl, ft_split(rl->all_cmd[i], ' ')));
	else
	{
		if (i != rl->n_cmd - 1)
			close_pipe(rl, 0);
		(signal(SIGINT, SIG_IGN), wait(&rl->status));
		if (WTERMSIG(rl->status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
	}
}
