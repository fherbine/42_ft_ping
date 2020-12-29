/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <fherbine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 23:27:44 by fherbine          #+#    #+#             */
/*   Updated: 2018/09/03 07:45:44 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	is_searched_var(char *line, char *search)
{
	short	i;

	i = 0;
	if (!line || !search)
		return (0);
	while (line[i] && line[i] != '=')
		i++;
	if (!ft_strncmp(line, search, i))
		return (1);
	return (0);
}

static char	*get_var_value(char *line)
{
	short	i;
	short	i2;
	char	*ret;

	i = 0;
	i2 = 0;
	while (line[i] && line[i] != '=')
		i++;
	if (!line[i] || line[i] != '=')
		return (NULL);
	ret = (char *)ft_memalloc(sizeof(char) * ft_strlen(line) - i + 1);
	i++;
	while (line[i])
	{
		ret[i2] = line[i];
		i++;
		i2++;
	}
	return (ret);
}

char		*ft_getenv(char **envp, char *search)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (is_searched_var(envp[i], search))
			return (get_var_value(envp[i]));
		i++;
	}
	return (NULL);
}
