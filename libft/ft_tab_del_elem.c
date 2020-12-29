/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_del_elem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <fherbine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 18:05:12 by fherbine          #+#    #+#             */
/*   Updated: 2018/02/27 17:15:28 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_name_aux(char *value)
{
	char	*ret;
	int		i;

	i = 0;
	if (!(ret = (char *)malloc(sizeof(char) * (ft_strlen(value) + 1))))
		exit(EXIT_FAILURE);
	while (value[i] && value[i] != '=')
	{
		ret[i] = value[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char		**ft_tab_del_elem(char **tab, char *name)
{
	int		i;
	int		i2;
	char	**new;
	char	*tmp;

	i = 0;
	i2 = 0;
	if (!(new = (char **)ft_memalloc(sizeof(char *) * (ft_tab_len(tab) + 1))))
		exit(EXIT_FAILURE);
	while (tab[i])
	{
		tmp = get_name_aux(tab[i]);
		if (ft_strcmp(name, tmp) != 0)
		{
			new[i2] = ft_strdup(tab[i]);
			i2++;
		}
		free(tmp);
		i++;
	}
	new[i2] = 0;
	ft_free_tab(tab);
	return (new);
}
