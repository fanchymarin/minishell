/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:32:59 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/03 18:27:10 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_cmd(void)
{
	char	abs_path[100000];

	printf("%s\n", getcwd(abs_path, 100000));
}

void	cd_cmd(char *dir)
{
	if (chdir(dir))
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

char	**export_cmd(char **environ, char *new_var)
{
	char		**new_environ;
	int			i;
	int			j;
	t_dbarray	size;

	if (check_syntax(new_var))
		return (NULL);
	size = find_size_dbarray(environ);
	new_environ = malloc(sizeof(char *) * size.lines + 2);
	i = 0;
	while (i < size.lines)
	{
		new_environ[i] = malloc(sizeof(char) * size.chars[i] + 1);
		j = 0;
		while (j < size.chars[i])
		{
			new_environ[i][j] = environ[i][j];
			j++;
		}
		new_environ[i++][j] = 0;
	}
	return (new_environ);
}