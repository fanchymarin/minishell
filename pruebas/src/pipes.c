/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:44:44 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/14 19:23:29 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command_child(t_cmdtable *rl, char **cmd)
{
	int	status;

	status = 0;
	if (!ft_strncmp(cmd[0], "pwd\0", 4))
		pwd_cmd();
	else if (!ft_strncmp(cmd[0], "echo\0", 5))
		echo_cmd(cmd);
	else if (!ft_strncmp(cmd[0], "env\0", 4))
		env_cmd(rl->env);
	else
		status = execve_cmd(rl->env, ft_find_path(cmd[0], rl->env), cmd);
	free_dp(cmd);
	free_dp(rl->all_cmd);
	free(rl->line);
	exit(status);
}

void	close_all_f_pipes(t_cmdtable *rl)
{
	int	i;

	i = -1;
	while (++i < (rl->n_cmd - 1))
		(close(rl->pipe[i][0]), close(rl->pipe[i][1]));
	// (close(rl->std_in), close(rl->std_out));
}

void	red_caos_of_f_pipes(t_cmdtable *rl, int i)
{
	// check_perror(rl->std_in = dup(STDIN_FILENO), "dup");
	// check_perror(rl->std_out = dup(STDOUT_FILENO), "dup");
	if (i != 0)
		dup2(rl->pipe[i - 1][0], STDIN_FILENO);
	if (i != rl->n_cmd - 1)
		dup2(rl->pipe[i][1], STDOUT_FILENO);
	// if (rl->infile)
	// 	(dup2(rl->infile, STDIN_FILENO), close(rl->infile), rl->infile = 0);
	// if (rl->outfile)
	// 	(dup2(rl->outfile, STDOUT_FILENO), close(rl->outfile), rl->outfile = 0);
	close_all_f_pipes(rl);
}

void	fork_process(t_cmdtable *rl, int i)
{
	pid_t	pid;

	pid = check_perror(fork(), "fork");
	if (!pid)
		(red_caos_of_f_pipes(rl, i), exec_command_child(rl,
				restore_spaces(ft_split(rl->all_cmd[i], ' '))));
	else
	{
		if (i != rl->n_cmd - 1)
			close(rl->pipe[i][1]);
	}
}
