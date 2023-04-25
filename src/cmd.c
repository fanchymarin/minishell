/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:32:59 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/04/25 17:13:48 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_cmd(void)
{
	char	abs_path[100000];

	ft_putstr_fd(getcwd(abs_path, sizeof(abs_path)), STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

int	cd_cmd(char **cmd)
{
	int	status;

	status = 0;
	if (!cmd[1])
		status = check_perror(chdir(getenv("HOME")), "cd");
	else
		status = check_perror(chdir(cmd[1]), "cd");
	if (status)
		return (exit_status(1));
	return (0);
}

void	echo_cmd(char **word)
{
	int	i;

	i = 1;
	if (!word[1])
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	if (!ft_strncmp(word[1], "-n\0", 3))
		i++;
	while (word[i])
	{
		if (ft_strncmp(word[i], "-n\0", 3))
		{
			ft_putstr_fd(word[i], STDOUT_FILENO);
			if (word[i + 1])
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
		i++;
	}
	if (ft_strncmp(word[1], "-n\0", 3))
		ft_putchar_fd('\n', STDOUT_FILENO);
}

int	execve_cmd(t_cmdtable *rl, char *abs_path, char **cmd)
{
	char	**array_env;
	int		status;

	status = 0;
	if (rl->n_cmd == 1 && fork())
		return (waiting_parent(rl), free(abs_path), 0);
	array_env = lstoarr(rl->env);
	if (!abs_path || execve(abs_path, cmd, array_env) == -1)
		(ft_printf("minishell: %s: command not found\n", cmd[0]), status = 127);
	free(abs_path);
	free_dp(array_env);
	if (rl->n_cmd == 1)
		exit(status);
	return (status);
}
