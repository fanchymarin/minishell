/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:36:43 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/01/12 17:46:09 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	char	*abs_path;

	abs_path = malloc(sizeof(char) * 1000);
	while (1)
	{
		getcwd(abs_path, 1000);
		line = ft_strtrim(readline("minishell$ "), " ");
		if (line && *line)
			add_history(line);
		if (!ft_strncmp(line, "exit\0", 5))
			break ;
		else if (!ft_strncmp(line, "pwd\0", 4))
			printf("%s\n", abs_path);
		else if (!ft_strncmp(line, "cd\0", 3) || !ft_strncmp(line, "cd ", 3))
			if (chdir(&line[3]))
				perror("cd");
		free(line);
		ft_bzero(abs_path, 1000);
	}
	free(abs_path);
	return (0);
}
