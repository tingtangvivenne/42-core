/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttang <ttang@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 00:00:00 by ttang             #+#    #+#             */
/*   Updated: 2026/09/28 00:00:00 by ttang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	**tail;
	void	*content;

	result = NULL;
	tail = &result;
	while (lst)
	{
		content = f(lst->content);
		*tail = ft_lstnew(content);
		if (*tail == NULL)
		{
			del(content);
			ft_lstclear(&result, del);
			return (NULL);
		}
		tail = &(*tail)->next;
		lst = lst->next;
	}
	return (result);
}
