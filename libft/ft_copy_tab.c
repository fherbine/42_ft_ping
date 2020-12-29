/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <fherbine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 18:32:51 by fherbine          #+#    #+#             */
/*   Updated: 2018/02/25 18:39:20 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_copy_tab(char **tab)
{
	int		i;
	char	**new;

	if (!(new = (char **)malloc(sizeof(char *) * (ft_tab_len(tab) + 1))))
		exit(EXIT_FAILURE);
	i = 0;
	while (tab[i])
	{
		new[i] = ft_strdup(tab[i]);
		i++;
	}
	new[i] = 0;
	return (new);
}
