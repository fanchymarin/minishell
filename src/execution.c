/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:44:44 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/04/20 20:02:01 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_cmds(t_cmdtable *rl)
{
	int	i;

	i = -1;
	while (++i < rl->n_cmd)
	{
		(signal(SIGINT, SIG_IGN), wait(&rl->status));
		if (WTERMSIG(rl->status) == SIGINT)
			(write(STDOUT_FILENO, "\n", 1), rl->status = 33280);
		else if (WTERMSIG(rl->status) == SIGQUIT)
			(write(STDOUT_FILENO, "\n", 1), rl->status = 33536);
	}
}

void	redirect_child(t_cmdtable *rl, int i)
{
	if (rl->infile)
		(dup2(rl->infile, STDIN_FILENO), close(rl->infile));
	if (rl->outfile)
		(dup2(rl->outfile, STDOUT_FILENO), close(rl->outfile));
	else if (i != rl->n_cmd - 1)
		redirect_pipe(rl->pipe, 1);
	close(rl->std_in);
}

int	exec_command(t_cmdtable *rl, char **cmd)
{
	int	status;

	status = 0;
	if (!cmd[0])
		return (free_dp(cmd), status);
	if (!ft_strncmp(cmd[0], "pwd\0", 4))
		pwd_cmd();
	else if (!ft_strncmp(cmd[0], "exit\0", 5))
		(ft_lstclear(rl->env, (*free)), close(rl->std_in),
			free_dp(cmd), exit(0));
	else if (!ft_strncmp(cmd[0], "cd\0", 3))
		status = cd_cmd(cmd);
	else if (!ft_strncmp(cmd[0], "export\0", 7))
		rl->env = export_cmd(rl->env, cmd);
	else if (!ft_strncmp(cmd[0], "unset\0", 6))
		rl->env = unset_cmd(rl->env, cmd);
	else if (!ft_strncmp(cmd[0], "echo\0", 5))
		echo_cmd(cmd);
	else if (!ft_strncmp(cmd[0], "env\0", 4))
		env_cmd(rl->env);
	else
		status = execve_cmd(rl, ft_find_path(cmd[0], rl->env), cmd);
	return (free_dp(cmd), status);
}

void	execute_multiple_cmds(t_cmdtable *rl)
{
	pid_t	pid;
	int		i;
	int		status;

	i = -1;
	while (++i < rl->n_cmd)
	{
		if (!check_red_files(rl, rl->all_cmd[i]))
			break ;
		if (i != rl->n_cmd - 1)
			check_perror(pipe(rl->pipe), "pipe");
		pid = check_perror(fork(), "fork");
		if (!pid)
			(redirect_child(rl, i), status = exec_command(rl,
					restore_spaces(ft_split(rl->all_cmd[i], ' '))),
				free_dp(rl->all_cmd), free(rl->line), exit(status));
		else
		{
			if (i != rl->n_cmd - 1)
				redirect_pipe(rl->pipe, 0);
		}
		close_fds(rl);
	}
	wait_cmds(rl);
}

void	execute_line(t_cmdtable *rl)
{
	check_perror(rl->std_in = dup(0), "dup");
	if (rl->n_cmd <= 0)
		error_msg(PIPE);
	if (rl->n_cmd == 1)
	{
		if (!check_red_files(rl, rl->all_cmd[0]))
			return ;
		exec_command(rl, restore_spaces(ft_split(rl->all_cmd[0], ' ')));
	}
	else
		execute_multiple_cmds(rl);
	(free_dp(rl->all_cmd), free(rl->line));
	(dup2(rl->std_in, 0), close(rl->std_in));
}
