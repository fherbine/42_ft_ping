/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_tab_elem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <fherbine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 19:12:52 by fherbine          #+#    #+#             */
/*   Updated: 2018/02/25 19:17:01 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_add_tab_elem(char **tab, char *elem)
{
	char	**new;
	int		i;

	if (!(new = (char **)malloc(sizeof(char *) * (ft_tab_len(tab) + 2))))
		exit(EXIT_FAILURE);
	i = 0;
	while (tab[i])
	{
		new[i] = ft_strdup(tab[i]);
		i++;
	}
	ft_free_tab(tab);
	new[i] = ft_strdup(elem);
	new[i + 1] = 0;
	return (new);
}
