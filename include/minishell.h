/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:34:40 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/02/22 18:10:23 by fmarin-p         ###   ########.fr       */
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
# define BUF_SIZE 4096

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/signal.h>

typedef struct s_cmdtable
{
	char	*line;
	char	**all_cmd;
	t_list	**env;
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

// utils
t_cmdtable	init_struct(void);
void		free_dp(char **dp);
int			cmd_counter(t_cmdtable *rl);
char		*ft_find_path(char *cmd, t_list **env);
int			check_blank_line(char *line);
char		*nested_shell(char *line, char *keyword);
char		*ft_getenv(t_list **env, char *name, char *value);
void		ft_lstdelnode(t_list **head, t_list *node, t_list *tmp);
int			quotes_closed(char *line, int i, char quote);

// cmds
void		pwd_cmd(void);
void		cd_cmd(char **cmd);
void		exit_cmd(t_cmdtable *rl, char **cmd);
void		echo_cmd(char **word);
void		env_cmd(t_list **environ);
t_list		**export_cmd(t_list **env, char **new_vars);
void		execve_cmd(t_list **env, char *abs_path, char **cmd);
t_list		**unset_cmd(t_list **env, char **name);

//pipes
void		red_pipe_child(t_cmdtable *rl, int i);
void		parent_process(t_cmdtable *rl, int i);

// check_files
void		check_red_files(t_cmdtable *rl);
char		*metachar_checker(char *line);
char		**expand_metachar(t_cmdtable *rl, char **rev_cmd);
char		**lstoarr(t_list **head);

#endif
