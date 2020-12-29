/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <fherbine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 13:35:14 by fherbine          #+#    #+#             */
/*   Updated: 2018/01/30 14:33:55 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_catching_non_spec(char *format, size_t *index, char *str)
{
	char		*tmp;
	size_t		i;

	i = 0;
	while (format[i] && format[i] != '%')
		i++;
	if (!(tmp = (char *)malloc(sizeof(char) * (i + 1))))
		exit(EXIT_FAILURE);
	i = 0;
	while (format[i] && format[i] != '%')
	{
		tmp[i] = format[i];
		i++;
	}
	tmp[i] = '\0';
	if (!(str = ft_strjoin(str, tmp)))
		exit(EXIT_FAILURE);
	free(tmp);
	(*index) += (size_t)i;
	return (str);
}

static char		*ft_specifier(va_list ap, char *format, char *str)
{
	if (format[0])
	{
		if (format[0] == 'd' || format[0] == 'i')
			str = ft_di(va_arg(ap, intmax_t), str);
		else if (format[0] == 'x')
			str = ft_xo(va_arg(ap, uintmax_t), str, 'x');
		else if (format[0] == 'o')
			str = ft_xo(va_arg(ap, uintmax_t), str, 'o');
		else if (format[0] == 's')
			str = ft_s(va_arg(ap, char *), str);
		else if (format[0] == 'c')
			str = ft_c(va_arg(ap, int), str);
		else
			str = ft_c((int)(format[0]), str);
	}
	return (str);
}

static char		*ft_reading_format(va_list ap, char *format, char *str)
{
	size_t		i;

	i = 0;
	while (format[i])
	{
		str = ft_catching_non_spec(&(format[i]), &i, str);
		i += (format[i] == '%') ? 1 : 0;
		str = ft_specifier(ap, &(format[i]), str);
		i += (format[i] != '\0') ? 1 : 0;
	}
	return (str);
}

int				ft_prints_fd(int fd, char *format, ...)
{
	va_list		ap;
	int			n;
	char		*str;

	if (!(str = (char *)malloc(sizeof(char) * 2)))
		exit(EXIT_FAILURE);
	str[0] = '\0';
	va_start(ap, format);
	str = ft_reading_format(ap, format, str);
	n = ft_strlen(str);
	ft_putstr_fd(str, fd);
	free(str);
	va_end(ap);
	return (n);
}

int				ft_prints(char *format, ...)
{
	va_list		ap;
	int			n;
	char		*str;

	if (!(str = (char *)malloc(sizeof(char) * 2)))
		exit(EXIT_FAILURE);
	str[0] = '\0';
	va_start(ap, format);
	str = ft_reading_format(ap, format, str);
	n = ft_strlen(str);
	ft_putstr(str);
	free(str);
	va_end(ap);
	return (n);
}
