/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:36:43 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/17 09:55:25 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_cmdtable *rl, char **cmd)
{
	char	*abs_path;
	int		status;

	status = 0;
	if (!ft_strncmp(cmd[0], "exit\0", 5))
		status = 1;
	else if (!ft_strncmp(cmd[0], "pwd\0", 4))
		pwd_cmd();
	else if (!ft_strncmp(cmd[0], "cd\0", 3))
		status = 2;
	else if (!ft_strncmp(cmd[0], "echo\0", 5))
		echo_cmd(cmd);
	else if (!ft_strncmp(cmd[0], "env\0", 4))
		env_cmd(environ);
//	else if (!ft_strncmp(cmd[0], "export\0", 7))
//		environ = export_cmd(cmd, rl->env_address);
	else if (!ft_strncmp(cmd[0], "status\0", 7))
		printf("status: %d\n", rl->status);
	else
	{
		abs_path = ft_find_path(cmd[0]);
		if (execve(abs_path, cmd, environ) == -1)
			printf("bash: %s: command not found\n", cmd[0]);
		free(abs_path);
	}
	free_dp(cmd);
	free_struct(rl);
	exit(status);
}

void	forks_n_pipes(t_cmdtable *rl)
{
	int	i;
	int	pid;

	rl->std_in = dup(0);
	if (rl->std_in == -1)
		perror("dup");
	i = -1;
	while (++i < rl->n_cmd)
	{
		if (i != rl->n_cmd - 1)
			if (pipe(rl->pipe) == -1)
				perror("pipe");
		pid = fork();
		if (!pid)
			(red_pipe_child(rl, i),
				exec_command(rl, ft_split(rl->all_cmd[i], ' ')));
		else
			parent_process(rl, i);
	}
	dup2(rl->std_in, 0);
	close(rl->std_in);
}

void	manage_line(t_cmdtable *rl)
{
	rl->all_cmd = ft_split(rl->line, '|');
	rl->n_cmd = cmd_counter(rl);
	rl->infile = 0;
	rl->outfile = 1;
	// check_red_files(rl);
	forks_n_pipes(rl);
}

int	main(void)
{
	t_cmdtable	rl;

	while (1)
	{
		rl.line = readline("minishell$ ");
		if (!*rl.line || !check_blank_line(rl.line))
		{
			free(rl.line);
			continue ;
		}
		add_history(rl.line);
		manage_line(&rl);
	}
	return (0);
}
