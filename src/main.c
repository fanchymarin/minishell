/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:36:43 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/16 14:47:28 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_cmdtable *rl)
{
	if (!ft_strncmp(rl->cmd[0], "exit\0", 5))
		exit(free_dp(rl->cmd, 1));
	else if (!ft_strncmp(rl->cmd[0], "pwd\0", 4))
		exit(pwd_cmd());
	else if (!ft_strncmp(rl->cmd[0], "cd\0", 3))
		exit(cd_cmd(rl->cmd[1]));
	else if (!ft_strncmp(rl->cmd[0], "echo\0", 5))
		exit(echo_cmd(rl->cmd));
	else if (!ft_strncmp(rl->cmd[0], "env\0", 4))
		exit(env_cmd(environ));
	// else if (!ft_strncmp(rl->cmd[0], "export\0", 7))
	// 	environ = export_cmd(rl->cmd, rl->env_address);
	// else if (!ft_strncmp(rl->cmd[0], "#", 1))
	// 	return ;
	else
		if (execve(ft_find_path(rl->cmd[0]), rl->cmd, environ) == -1)
		{
			printf("bash: %s: command not found\n", rl->cmd[0]);
			exit(0);
		}
}

void	red_pipe_child(t_cmdtable *rl, int i)
{
	if (i == 0 && rl->infile)
		dup2(rl->infile, 0);
	if ((i == (int)rl->n_cmd -1) && rl->outfile)
		dup2(rl->outfile, 1);
	if (i != (int)rl->n_cmd -1)
	{
		close(rl->pipe[0]);
		dup2(rl->pipe[1], 1);
		close(rl->pipe[1]);
	}
}

void	red_pipe_parent(t_cmdtable *rl)
{
	close(rl->pipe[1]);
	rl->fd_in = rl->pipe[0];
	dup2(rl->fd_in, 0);
	close(rl->fd_in);
}

void	manage_line(t_cmdtable *rl)
{
	int		pid;
	int		i;
	int		status;

	rl->all_cmd = ft_split(rl->line, '|');
	free(rl->line);
	rl->n_cmd = cmd_counter(rl);
	// check_red_files(rl);
	if ((rl->std_in = dup(0)) == -1)
		perror("dup");
	rl->fd_in = dup(rl->std_in);
	i = -1;
	while (i < (int)rl->n_cmd -1)
	{
		i++;
		rl->cmd = ft_split(rl->all_cmd[i], ' ');
		free(rl->all_cmd[i]);
		if (i != (int)rl->n_cmd -1)
			if (pipe(rl->pipe) == -1)
				perror("pipe");
		pid = fork();
		if (!pid)
			(red_pipe_child(rl, i), exec_command(rl));
		if (i != (int)rl->n_cmd -1)
			red_pipe_parent(rl);
		free_dp(rl->cmd, 0);
		wait(&status);
		if (WEXITSTATUS(status) == 1)
			exit(0);
	}
	dup2(rl->std_in, 0);
	close(rl->std_in);
}

int	main(void)
{
	t_cmdtable	rl;

	while (1)
	{
		rl.line = readline("minishell$ ");
		if (!*rl.line)
		{
			free(rl.line);
			continue ;
		}
		add_history(rl.line);
		manage_line(&rl);
	}
	return (0);
}
