/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_prints.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <fherbine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:14:28 by fherbine          #+#    #+#             */
/*   Updated: 2018/01/30 14:33:48 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_di(intmax_t n, char *str)
{
	char	*tmp;

	if (!(tmp = ft_itoa(n)))
		exit(EXIT_FAILURE);
	if (!(str = ft_strjoin(str, tmp)))
		exit(EXIT_FAILURE);
	free(tmp);
	return (str);
}

char		*ft_xo(uintmax_t n, char *str, char param)
{
	char	*tmp;

	if (!(tmp = (param == 'x') ? ft_itoa_base(n, 16) : ft_itoa_base(n, 8)))
		exit(EXIT_FAILURE);
	if (!(str = ft_strjoin(str, tmp)))
		exit(EXIT_FAILURE);
	free(tmp);
	return (str);
}

char		*ft_s(char *str2, char *str)
{
	char	*new_str;

	if (!(new_str = (!str2) ? ft_strdup("(null)") : ft_strdup(str2)))
		exit(EXIT_FAILURE);
	if (!(str = ft_strjoin(str, new_str)))
		exit(EXIT_FAILURE);
	free(new_str);
	return (str);
}

char		*ft_c(int c, char *str)
{
	char *to_join;

	if (!(to_join = (char *)malloc(sizeof(char) * 3)))
		exit(EXIT_FAILURE);
	to_join[0] = (char)c;
	to_join[1] = '\0';
	if (!(str = ft_strjoin(str, to_join)))
		exit(EXIT_FAILURE);
	free(to_join);
	return (str);
}
