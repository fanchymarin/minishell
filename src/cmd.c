/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:32:59 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/17 12:41:05 by fmarin-p         ###   ########.fr       */
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

void	env_cmd(char **environ)
{
	int	i;

	i = 0;
	while (environ[i])
		printf("%s\n", environ[i++]);
}

void	execve_cmd(char *abs_path, char **cmd)
{
	if (execve(abs_path, cmd, environ) == -1)
		printf("bash: %s: command not found\n", cmd[0]);
	free(abs_path);
}
