/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clcarrer <clcarrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:36:43 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/23 10:54:14 by clcarrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*nested_shell(char *line, char *keyword)
{
	char	*appended_line;
	char	*new_line;
	char	*old_line;

	appended_line = readline(">");
	while (ft_strnstr(appended_line, keyword, ft_strlen(appended_line)))
	{
		new_line = readline(">");
		old_line = appended_line;
		appended_line = ft_strjoin(appended_line, new_line);
		free(old_line);
		free(new_line);
	}
	if (line)
	{
		new_line = ft_strjoin(line, appended_line);
		free(line);
		free(appended_line);
	}
	else
		new_line = appended_line;
	return (new_line);
}

void	exec_command(t_cmdtable *rl, char **cmd)
{
	int		exit_code;

	exit_code = 0;
	if (!ft_strncmp(cmd[0], "exit\0", 5))
		exit_code = 200;
	else if (!ft_strncmp(cmd[0], "pwd\0", 4))
		pwd_cmd();
	else if (!ft_strncmp(cmd[0], "cd\0", 3))
		exit_code = 201;
	else if (!ft_strncmp(cmd[0], "echo\0", 5))
		echo_cmd(cmd);
	else if (!ft_strncmp(cmd[0], "env\0", 4))
		env_cmd(rl->env);
	else if (!ft_strncmp(cmd[0], "export\0", 7))
		exit_code = 202;
	else if (!ft_strncmp(cmd[0], "unset\0", 6))
		exit_code = 203;
	else
		execve_cmd(rl->env, ft_find_path(cmd[0], rl->env), cmd);
	free_dp(cmd);
	free_dp(rl->all_cmd);
	free(rl->line);
	exit(exit_code);
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
	(free_dp(rl->all_cmd), free(rl->line), free(rl->outfile));
	(dup2(rl->std_in, 0), close(rl->std_in));
	rl->infile = 0;
}

void	manage_line(t_cmdtable *rl)
{
	rl->line = metachar_checker(rl->line);
	rl->all_cmd = expand_metachar(rl, ft_split(rl->line, '|'));
	rl->n_cmd = cmd_counter(rl);
	check_red_files(rl);
	forks_n_pipes(rl);
}

int	main(void)
{
	t_cmdtable	rl;

	rl = init_struct();
	while (1)
	{
		rl.line = readline("minishell$ ");
		if (!rl.line)
			(ft_lstclear(rl.env, (*free)), exit(WEXITSTATUS(rl.status)));
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
