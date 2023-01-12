/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:11:00 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/03/29 14:28:47 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	void	*content;

	head = 0;
	while (lst)
	{
		content = f(lst->content);
		if (!content)
			del(content);
		else
			ft_lstadd_back(&head, ft_lstnew(content));
		lst = lst->next;
	}
	return (head);
}
