/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:34:40 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/09 19:08:25 by fmarin-p         ###   ########.fr       */
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

typedef struct s_cmdtable
{
	char	*line;
	char	**all_cmd;
	size_t	n_cmd;
	char	**cmd;
	int		pipe[2];
	int		infile;
	int		outfile;
}	t_cmdtable;

typedef struct s_dbarray
{
	int	lines;
	int	new_lines;
}	t_dbarray;

extern char	**environ;

int			free_dp(char **dp, int status);
int			check_syntax_n_size(char **new_vars);

int			pwd_cmd(void);
int			cd_cmd(char *dir);
int			echo_cmd(char **word);
int			env_cmd(char **environ);
char		**export_cmd(char **new_vars, char ***env_address);

// execve_cmd
char		*ft_find_path(char *cmd);
void		ft_execute_cmd(t_cmdtable *rl);

size_t		cmd_counter(t_cmdtable *tty);


#endif
