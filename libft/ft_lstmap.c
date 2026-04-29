/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakemur <ttakemur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 20:43:45 by ttakemur          #+#    #+#             */
/*   Updated: 2026/04/27 00:17:02 by ttakemur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dest;
	t_list	*head;

	if (lst == NULL)
		return (NULL);
	dest = ft_lstnew(f(lst->content));
	head = dest;
	lst = lst->next;
	while (lst != NULL)
	{
		dest->next = ft_lstnew(f(lst->content));
		if (dest->next == NULL)
		{
			ft_lstclear(&head, del);
			break ;
		}
		lst = lst->next;
		dest = dest->next;
	}
	return (head);
}
