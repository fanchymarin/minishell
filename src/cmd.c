/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:32:59 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/04/20 20:08:43 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_cmd(void)
{
	char	abs_path[100000];

	printf("%s\n", getcwd(abs_path, 100000));
}

int	cd_cmd(char **cmd)
{
	int	status;

	if (!cmd[1])
		status = check_perror(chdir(getenv("HOME")), "cd");
	else
		status = check_perror(chdir(cmd[1]), "cd");
	return (status);
}

void	echo_cmd(char **word)
{
	int	i;

	i = 1;
	if (!word[1])
		(write(STDOUT_FILENO, "\n", 1), exit(0));
	if (!ft_strncmp(word[1], "-n\0", 3))
		i++;
	while (word[i])
	{
		if (ft_strncmp(word[i], "-n\0", 3))
		{
			printf("%s", word[i]);
			if (word[i + 1])
				printf(" ");
		}
		i++;
	}
	if (ft_strncmp(word[1], "-n\0", 3))
		printf("\n");
}

int	execve_cmd(t_cmdtable *rl, char *abs_path, char **cmd)
{
	char	**array_env;
	int		status;

	if (rl->n_cmd == 1 && fork())
	{
		(signal(SIGINT, SIG_IGN), wait(&rl->status));
		if (WTERMSIG(rl->status) == SIGINT)
			(write(STDOUT_FILENO, "\n", 1), rl->status = 33280);
		else if (WTERMSIG(rl->status) == SIGQUIT)
			(write(STDOUT_FILENO, "\n", 1), rl->status = 33536);
		return (free(abs_path), 0);
	}
	status = 0;
	array_env = lstoarr(rl->env);
	if (!abs_path || execve(abs_path, cmd, array_env) == -1)
		(ft_printf("minishell: %s: command not found\n", cmd[0]), status = 127);
	free(abs_path);
	free_dp(array_env);
	if (rl->n_cmd == 1)
		exit(status);
	return (status);
}
