/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:44:44 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/04/26 16:39:06 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_cmds(t_cmdtable *rl)
{
	int	i;

	i = -1;
	while (++i < rl->n_cmd)
		waiting_parent(rl);
}

void	redirect_child(t_cmdtable *rl, int i)
{
	if (rl->infile)
		(dup2(rl->infile, STDIN_FILENO), close(rl->infile));
	else if (i != 0)
		(dup2(rl->old_fd, 0), close(rl->old_fd));
	if (rl->outfile)
		(dup2(rl->outfile, STDOUT_FILENO), close(rl->outfile));
	else if (i != rl->n_cmd - 1)
		(close(rl->pipe[0]), dup2(rl->pipe[1], 1), close(rl->pipe[1]));
}

int	exec_command(t_cmdtable *rl, char **cmd)
{
	int	status;

	status = 0;
	if (!cmd[0])
		return (free_dp(cmd), 1);
	if (!ft_strncmp(cmd[0], "pwd\0", 4))
		pwd_cmd();
	else if (!ft_strncmp(cmd[0], "exit\0", 5))
		(ft_lstclear(rl->env, (*free)), free_dp(cmd), close(rl->stdfiles
				[STDIN_FILENO]), close(rl->stdfiles[STDOUT_FILENO]), exit(0));
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
	return (free_dp(cmd), exit_status(status));
}

void	execute_multiple_cmds(t_cmdtable *rl)
{
	int		i;

	i = -1;
	while (++i < rl->n_cmd)
	{
		if (!check_red_files(rl, rl->all_cmd[i]))
			break ;
		if (i != rl->n_cmd - 1)
			check_perror(pipe(rl->pipe), "pipe");
		if (!check_perror(fork(), "fork"))
			(redirect_child(rl, i), exec_command(rl, restore_spaces(ft_split
						(restore_pipes(rl->all_cmd[i]), ' '))), free_dp
				(rl->all_cmd), free(rl->line), close(rl->stdfiles[0]),
				close(rl->stdfiles[1]), close(rl->pipe[0]), close(rl->pipe[1]),
				exit(WEXITSTATUS(rl->status)));
		else
		{
			if (i != 0)
				close(rl->old_fd);
			if (i != rl->n_cmd - 1)
				(close(rl->pipe[1]), rl->old_fd = rl->pipe[0]);
		}
		close_fds(rl);
	}
	(wait_cmds(rl), rl->old_fd = 0);
}

void	execute_single_cmd(t_cmdtable *rl)
{
	if (!check_red_files(rl, rl->all_cmd[0]))
		return ;
	if (rl->infile)
		(dup2(rl->infile, STDIN_FILENO), close(rl->infile));
	if (rl->outfile)
		(dup2(rl->outfile, STDOUT_FILENO), close(rl->outfile));
	rl->status = exec_command(rl, restore_spaces(ft_split(
					restore_pipes(rl->all_cmd[0]), ' ')));
	close_fds(rl);
}
