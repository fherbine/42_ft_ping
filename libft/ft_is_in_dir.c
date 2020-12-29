/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_in_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <fherbine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 16:34:21 by fherbine          #+#    #+#             */
/*   Updated: 2018/02/20 16:49:16 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_is_in_dir(char *name, char *path)
{
	DIR				*dir;
	struct dirent	*new;

	dir = NULL;
	new = NULL;
	if ((dir = opendir(path)))
	{
		if (!(new = readdir(dir)))
			return (0);
		while (new)
		{
			if (ft_strcmp(name, new->d_name) == 0)
				return (1);
			new = readdir(dir);
		}
		closedir(dir);
	}
	return (0);
}
