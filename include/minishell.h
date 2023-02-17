/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:34:40 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/17 16:59:21 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define SIMPLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define PIPE 124
# define LESS_THAN 60
# define MORE_THAN 62
# define DOLLAR 36

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
	int		status;
}	t_cmdtable;

typedef struct s_dbarray
{
	int	lines;
	int	new_lines;
}	t_dbarray;

extern char	**environ;

// utils
void	free_dp(char **dp);
void	free_struct(t_cmdtable *rl);
int		check_syntax_n_size(char **new_vars);
int		cmd_counter(t_cmdtable *rl);
char	*ft_find_path(char *cmd);
int		check_blank_line(char *line);
char	*nested_shell(char *line, char *keyword);

// cmds
void	pwd_cmd(void);
void	cd_cmd(char **cmd);
void	exit_cmd(t_cmdtable *rl, char **cmd);
void	echo_cmd(char **word);
void	env_cmd(char **environ);
char	**export_cmd(char **new_vars, char ***env_address);
void	execve_cmd(char *abs_path, char **cmd);

//pipes
void	red_pipe_child(t_cmdtable *rl, int i);
void	parent_process(t_cmdtable *rl, int i);

// check_files
void	check_red_files(t_cmdtable *rl);
char	*metachar_checker(char *line);
char	**expand_metachar(char **rev_cmd);

#endif
