/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:34:40 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/03 18:18:49 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h> 

typedef struct s_prompt
{
	char	*rl_line;
	char	**environ;
	char	*line;
	char	**word;
	char	**cmd_lines;
	int		first_word[100];
	int		n_child;
}	t_prompt;

typedef struct s_dbarray
{
	int	lines;
	int	*chars;
}	t_dbarray;


void		free_dp(char **dp);
void		free_struct(t_prompt *tty, int stat);
t_dbarray	find_size_dbarray(char **environ);

void		pwd_cmd(void);
void		cd_cmd(char *dir);
void		echo_cmd(char **word);
void		env_cmd(char **environ);
char	**export_cmd(char **environ, char *new_var);

#endif
