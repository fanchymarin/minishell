/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:36:43 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/23 16:53:23 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	exec_command_parent(t_cmdtable *rl, char **cmd)
{
	int	stat;

	stat = 0;
	if (!ft_strncmp(cmd[0], "exit\0", 5))
		(ft_lstclear(rl->env, (*free)), exit(0));
	else if (!ft_strncmp(cmd[0], "cd\0", 3))
		(cd_cmd(cmd), stat++);
	else if (!ft_strncmp(cmd[0], "export\0", 7))
	{
		rl->env = export_cmd(rl->env, cmd);
		stat++;
	}
	else if (!ft_strncmp(cmd[0], "unset\0", 6))
	{
		rl->env = export_cmd(rl->env, cmd);
		stat++;
	}
	return (stat);
}

void	forks_n_pipes(t_cmdtable *rl)
{
	int		i;
	pid_t	pid;

	rl->std_in = dup(0);
	if (rl->std_in == -1)
		perror("dup");
	i = -1;
	while (++i < rl->n_cmd)
	{
		check_red_files(rl, rl->all_cmd[i]);
		if (i != rl->n_cmd - 1)
			if (pipe(rl->pipe) == -1)
				perror("pipe");
		if (exec_command_parent(rl, ft_split(rl->all_cmd[i], ' ')))
			continue ;
		pid = fork();
		if (!pid)
			(red_pipe_child(rl, i),
				exec_command_child(rl, ft_split(rl->all_cmd[i], ' ')));
		else
			parent_process(rl, i);
	}
	(free_dp(rl->all_cmd), free(rl->line));
	(dup2(rl->std_in, 0), close(rl->std_in), rl->infile = 0, rl->outfile = 0);
}

void	signal_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

int	main(void)
{
	t_cmdtable	rl;

	rl = init_struct();
	while (1)
	{
		signal(SIGINT, &signal_handler);
		rl.line = readline("minishell$ ");
		if (!rl.line)
			(ft_lstclear(rl.env, (*free)), exit(WEXITSTATUS(rl.status)));
		if (!*rl.line || !check_blank_line(rl.line))
		{
			free(rl.line);
			continue ;
		}
		add_history(rl.line);
		rl.line = metachar_checker(rl.line);
		rl.all_cmd = expand_metachar(&rl, ft_split(rl.line, '|'));
		rl.n_cmd = cmd_counter(&rl);
		forks_n_pipes(&rl);
	}
	return (0);
}
