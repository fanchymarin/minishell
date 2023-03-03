/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:36:43 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/03 08:52:16 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_command_parent(t_cmdtable *rl, char **cmd)
{
	int	stat;

	stat = 0;
	if (!cmd[0] && rl->n_cmd > 1)
		return (error_msg(PIPE), free_dp(cmd), 2);
	if (!cmd[0])
		return (free_dp(cmd), 1);
	if (!ft_strncmp(cmd[0], "exit\0", 5))
		(ft_lstclear(rl->env, (*free)), free_dp(cmd), exit(0));
	else if (!ft_strncmp(cmd[0], "cd\0", 3))
		(cd_cmd(cmd), stat++);
	else if (!ft_strncmp(cmd[0], "export\0", 7))
	{
		rl->env = export_cmd(rl->env, cmd);
		stat++;
	}
	else if (!ft_strncmp(cmd[0], "unset\0", 6))
	{
		rl->env = unset_cmd(rl->env, cmd);
		stat++;
	}
	return (free_dp(cmd), stat);
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

void	forks_n_pipes(t_cmdtable *rl)
{
	int	i;
	int	stat;

	rl->std_in = dup(0);
	if (rl->std_in == -1)
		perror("dup");
	i = -1;
	while (++i < rl->n_cmd)
	{
		if (!check_red_files(rl, rl->all_cmd[i]))
			break ;
		restore_pipes(rl->all_cmd[i]);
		stat = exec_command_parent(rl, struct_quotes(rl->all_cmd[i]));
		if (stat == 1)
			continue ;
		else if (stat == 2)
			break ;
		if (i != rl->n_cmd - 1)
			if (pipe(rl->pipe) == -1)
				perror("pipe");
		(fork_process(rl, i), rl->infile = 0, rl->outfile = 0);
	}
	(free_dp(rl->all_cmd), free(rl->line));
	(dup2(rl->std_in, 0), close(rl->std_in));
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
			(ft_lstclear(rl.env, (*free)), exit(0));
		if (!*rl.line || !check_blank_line(rl.line))
		{
			free(rl.line);
			continue ;
		}
		add_history(rl.line);
		rl.line = quotes_checker(rl.line);
		if (!rl.line)
			continue ;
		rl.all_cmd = expand_metachar(&rl, ft_split(rl.line, '|'));
		rl.n_cmd = cmd_counter(rl.all_cmd);
		forks_n_pipes(&rl);
	}
	return (0);
}
