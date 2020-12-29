/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_slash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <fherbine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 16:05:03 by fherbine          #+#    #+#             */
/*   Updated: 2018/02/19 16:59:29 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_append_slash(char *path)
{
	if (path[ft_strlen(path) - 1] != '/')
		path = ft_strjoin(path, "/");
	return (path);
}
