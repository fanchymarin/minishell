/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:34:40 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/16 23:57:10 by fmarin-p         ###   ########.fr       */
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
# include <fcntl.h>

typedef struct s_cmdtable
{
	char	*line;
	char	**all_cmd;
	int		n_cmd;
	int		pipe[2];
	int		infile;
	int		outfile;
	int		std_in;
}	t_cmdtable;

typedef struct s_dbarray
{
	int	lines;
	int	new_lines;
}	t_dbarray;

extern char	**environ;

// utils
void		free_dp(char **dp);
void		free_struct(t_cmdtable *rl);
int			check_syntax_n_size(char **new_vars);
size_t		cmd_counter(t_cmdtable *rl);
char		*ft_find_path(char *cmd);
int			check_blank_line(char *line);

// cmds
void		pwd_cmd(void);
void		cd_cmd(char **cmd);
void		exit_cmd(t_cmdtable *rl, char **cmd);
void		echo_cmd(char **word);
void		env_cmd(char **environ);
char		**export_cmd(char **new_vars, char ***env_address);

//pipes
void		red_pipe_child(t_cmdtable *rl, int i);
void		red_pipe_parent(t_cmdtable *rl);

// check_files
void		check_red_files(t_cmdtable *rl);

#endif
