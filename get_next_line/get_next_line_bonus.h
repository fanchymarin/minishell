/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:15:48 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/03/03 10:21:49 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# define BUFFER_SIZE 4092

typedef struct s_list
{
	int				fd;
	char			*memory;
	struct s_list	*next;

}	t_list;

char	*get_next_line(int fd);
char	*ft_strchr_gnl(const char *s, int c);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
char	*ft_concat_str(char *buf, char *memory);
size_t	ft_strlen_gnl(const char *str);
int		free_list(t_list **head, t_list *node, t_list *tmp);
int		storage_memory(int fd, t_list **head, char *memory);

#endif
