/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:32:59 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/18 01:39:08 by fmarin-p         ###   ########.fr       */
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
	if (chdir(cmd[1]) == -1)
		perror("cd");
	free_dp(cmd);
}

void	echo_cmd(char **word)
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

void	execve_cmd(t_list **env, char *abs_path, char **cmd)
{
	char	**array_env;

	array_env = lstoarr(env);
	if (execve(abs_path, cmd, 0) == -1)
		printf("bash: %s: command not found\n", cmd[0]);
	free(abs_path);
	free(array_env);
}
