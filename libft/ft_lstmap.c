/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:57:38 by fherbine          #+#    #+#             */
/*   Updated: 2017/11/13 16:24:51 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*cp;

	cp = NULL;
	new = NULL;
	while (lst != NULL)
	{
		if (cp == NULL)
		{
			cp = f(lst);
			new = cp;
		}
		else
		{
			cp->next = f(lst);
			cp = cp->next;
		}
		lst = lst->next;
	}
	return (new);
}
