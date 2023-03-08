/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:44:44 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/08 18:16:28 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_pipe(int *pipe, int fd)
{
	close(pipe[fd ^ 1]);
	dup2(pipe[fd], fd);
	close(pipe[fd]);
}

void	red_pipe_child(t_cmdtable *rl, int i)
{
	if (rl->infile)
		(dup2(rl->infile, 0), close(rl->infile));
	if (rl->outfile)
		(dup2(rl->outfile, 1), close(rl->outfile));
	else if (i != rl->n_cmd - 1)
		redirect_pipe(rl->pipe, 1);
	if (rl->std_in)
		close(rl->std_in);
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

	pid = check_perror(fork(), "fork");
	if (!pid)
		(red_pipe_child(rl, i), exec_command_child(rl,
				restore_spaces(ft_split(rl->all_cmd[i], ' '))));
	else
	{
		if (i != rl->n_cmd - 1)
			redirect_pipe(rl->pipe, 0);
		(signal(SIGINT, SIG_IGN), wait(&rl->status));
		if (WTERMSIG(rl->status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
	}
}
