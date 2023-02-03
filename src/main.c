/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:36:43 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/03 18:18:29 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_path(char *cmd)
{
	int		i;
	char	**split_path;
	char	*path;

	if (!cmd)
		return (0);
	split_path = ft_split(getenv("PATH"), ':');
	i = 0;
	while (split_path[i])
	{
		path = ft_strjoin(ft_strjoin(split_path[i], "/"), cmd);
		if (access(path, 0) == 0)
			return (path);
		i++;
	}
	free(path);
	return (0);
}

void	child_process(t_prompt *tty, int i)
{
	extern char	**environ;

	execve(ft_find_path(tty->word[0]), ft_split(tty->cmd_lines[i], ' '), environ);
}

void	split_commands(t_prompt *tty)
{
	int	i;
	
	i = 0;
	tty->n_child = 1;
	while (tty->word[i])
		if (!ft_strncmp(tty->word[i++], "|", 1))
			tty->n_child++;
	tty->cmd_lines = ft_split(tty->line, '|');
	i = 0;
	while ((tty->cmd_lines[i] = ft_strtrim(tty->cmd_lines[i], " ")), tty->cmd_lines[i])
		i++;
}

int	parent_process(t_prompt *tty)
{
	pid_t	pid;
	int		i;

	split_commands(tty);
	i = 0;
	while (tty->n_child)
	{
		if ((pid = fork()) < 0)
			perror("fork");
		else if (pid == 0)
		{
			child_process(tty, i);
			return (0);
		}
		(tty->n_child--, i++, wait(NULL));
	}
	return (0);
}

void	exec_command(t_prompt *tty)
{
	if (!ft_strncmp(tty->word[0], "exit\0", 5))
		free_struct(tty, 1);
	else if (!ft_strncmp(tty->word[0], "pwd\0", 4))
		pwd_cmd();
	else if (!ft_strncmp(tty->word[0], "cd\0", 3))
		cd_cmd(tty->word[1]);
	else if (!ft_strncmp(tty->word[0], "echo\0", 5))
		echo_cmd(tty->word);
	else if (!ft_strncmp(tty->word[0], "env\0", 4))
		env_cmd(tty->environ);
	else if (!ft_strncmp(tty->word[0], "export\0", 7))
		export_cmd(tty->environ, "");
	//else
	//	parent_process(tty);
}

int	main(void)
{
	t_prompt	*tty;
	extern char	**environ;

	tty = malloc(sizeof(t_prompt));
	tty->environ = environ;
	while (1)
	{
		tty->rl_line = readline("minishell$ ");
		tty->line = ft_strtrim(tty->rl_line, " ");
		if (!*tty->line)
		{
			free(tty->rl_line);
			free(tty->line);
			continue ;
		}
		add_history(tty->line);
		tty->word = ft_split(tty->line, ' ');
		exec_command(tty);
		free_struct(tty, 0);
	}
	return (0);
}
