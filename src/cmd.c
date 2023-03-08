/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:32:59 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/07 18:16:21 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_cmd(void)
{
	char	abs_path[100000];

	printf("%s\n", getcwd(abs_path, 100000));
}

void	cd_cmd(char **cmd)
{
	if (!cmd[1])
		check_perror(chdir(getenv("HOME")), "cd");
	else
		check_perror(chdir(cmd[1]), "cd");
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

void	execve_cmd(t_list **env, char *abs_path, char **cmd)
{
	char	**array_env;

	array_env = lstoarr(env);
	if (!abs_path || execve(abs_path, cmd, array_env) == -1)
		ft_printf("minishell: %s: command not found\n", cmd[0]);
	free(abs_path);
	free_dp(array_env);
}
