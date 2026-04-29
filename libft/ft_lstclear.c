/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakemur <ttakemur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 20:43:45 by ttakemur          #+#    #+#             */
/*   Updated: 2026/04/27 00:27:08 by ttakemur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cur;
	t_list	*to_del;

	cur = *lst;
	while (cur != NULL)
	{
		to_del = cur;
		cur = cur->next;
		ft_lstdelone(to_del, del);
	}
	*lst = NULL;
}
