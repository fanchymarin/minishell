/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:34:40 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/04/26 14:08:43 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define SIMPLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define PIPE 124
# define LESS_THAN 60
# define MORE_THAN 62
# define SPACE 32
# define APPEND 68
# define HERE_DOC 72
# define DOLLAR 36
# define BUF_SIZE 4096

# include "libft.h"
# include "ft_printf.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/signal.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_cmdtable
{
	char	*line;
	char	**all_cmd;
	t_list	**env;
	int		n_cmd;
	int		pipe[2];
	int		old_fd;
	int		infile;
	int		outfile;
	int		stdfiles[2];
	int		status;
}	t_cmdtable;

// utils
t_cmdtable	init_struct(void);
void		free_dp(char **dp);
int			cmd_counter(char **all_cmd);
char		*ft_find_path(char *cmd, t_list **env);
int			check_blank_line(char *line);
char		*nested_shell(char *line, char *keyword);
char		*ft_getenv(t_list **env, char *name, char *value);
void		ft_lstdelnode(t_list **head, t_list *node, t_list *tmp);
int			quotes_closed(char *line, int i, char quote);
char		*append_str(t_list **head);
int			check_syntax(t_list **env, char **new_vars);
void		replace_var(t_list **env, char *rep_var, char *var_name);
int			exit_status(int value);
char		*append_from_input(char *old_line, int fd);

// restore metachars
char		*restore_pipes(char *line);
char		*restore_vars(char *line);
char		*restore_quotes(char *line);
char		**restore_spaces(char **line);
char		*hide_quoted_metachars(int *i, int j, char *line, int quote);

// cmds
void		pwd_cmd(void);
int			cd_cmd(char **cmd);
void		echo_cmd(char **word);
void		env_cmd(t_list **environ);
t_list		**export_cmd(t_list **env, char **new_vars);
int			execve_cmd(t_cmdtable *rl, char *abs_path, char **cmd);
t_list		**unset_cmd(t_list **env, char **name);

//pipes
void		red_pipe_child(t_cmdtable *rl, int i);
void		execute_line(t_cmdtable *rl);
void		execute_single_cmd(t_cmdtable *rl);
void		execute_multiple_cmds(t_cmdtable *rl);
void		execute_single_cmd(t_cmdtable *rl);
void		close_fds(t_cmdtable *rl);
void		waiting_parent(t_cmdtable *rl);

// check_files
int			check_red_files(t_cmdtable *rl, char *cmd_line);
int			manage_line(t_cmdtable *rl, char *cmd_line, int i);
char		*quotes_checker(char *line);
char		**struct_quotes(char *old_cmd);
char		**expand_metachar(t_cmdtable *rl, char **rev_cmd);
char		**lstoarr(t_list **head);
char		*restore_metachar(char *line, int control);
void		here_doc(t_cmdtable *rl, char *keyword);
void		close_fd(t_cmdtable *rl);
void		error_msg(char c);
int			check_perror(int code, char *name);

// debug
char		*manage_pipe(char *line, int *i);

#endif
