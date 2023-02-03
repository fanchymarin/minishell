/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:36:43 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/02 19:05:57 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_dp(char **dp)
{
	int	i;

	i = 0;
	while (dp[i])
		free(dp[i++]);
	free(dp);
}

void	free_struct(t_prompt *tty, int stat)
{
	free(tty->rl_line);
	free(tty->line);
	free_dp(tty->word);
	if (stat)
	{
		free(tty);
		exit(0/*system("leaks minishell")*/);
	}
}

void	echo_command(char **word)
{
	int	i;

	i = 1;
	if (!ft_strncmp(word[1], "-n\0", 3))
		i++;
	while (word[i])
	{
		printf("%s", word[i]);
		if (word[i++ + 1])
			printf(" ");
	}
	if (ft_strncmp(word[1], "-n\0", 3))
		printf("\n");
}

<<<<<<< Updated upstream
void	exec_command(t_prompt *tty)
{
=======
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

void	child_process(t_prompt *tty)
{
	extern char	**environ;

	execve(ft_find_path(tty->word[0]), tty->word, environ);
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

void	parent_process(t_prompt *tty)
{
	// pid_t	pid;

	split_commands(tty);
	while (n_child)
	{
		if ((pid = fork()) < 0)
			perror("fork");
		else if (pid == 0)
		{
			child_process(tty);
			return (0);
		}
		else
			wait(NULL);
		n_child--;
	}
}

void	exec_command(t_prompt *tty)
{
>>>>>>> Stashed changes
	if (!ft_strncmp(tty->word[0], "exit\0", 5))
		free_struct(tty, 1);
	else if (!ft_strncmp(tty->word[0], "pwd\0", 4))
	{
		tty->abs_path = malloc(sizeof(char) * 1000);
		printf("%s\n", getcwd(tty->abs_path, 1000));
		free(tty->abs_path);
	}
	else if (!ft_strncmp(tty->word[0], "cd\0", 3))
	{
		if (chdir(tty->word[1]))
			perror("cd");
	}
	else if (!ft_strncmp(tty->word[0], "echo\0", 5))
		echo_command(tty->word);
<<<<<<< Updated upstream
=======
	else
		parent_process(tty);
>>>>>>> Stashed changes
}

int	main(void)
{
	t_prompt	*tty;

	tty = malloc(sizeof(t_prompt));
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
