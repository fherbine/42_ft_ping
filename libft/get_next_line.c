/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fherbine <fherbine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 15:52:36 by fherbine          #+#    #+#             */
/*   Updated: 2017/12/11 14:57:35 by fherbine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strjoin_nl(char *s1, char const *s2)
{
	char			*tab;
	int				i;
	int				j;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (!(tab = (char *)malloc(sizeof(char) * (i + j + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	while (s2[j] && s2[j] != '\n')
	{
		tab[i++] = s2[j++];
	}
	free(s1);
	tab[i] = '\0';
	return (tab);
}

int					ft_read(char **line, char *str, t_gnl *gnl)
{
	int				nb;
	int				i;

	while ((nb = read(gnl->fd, gnl->buf, BUFF_SIZE)))
	{
		gnl->buf[nb] = '\0';
		i = 0;
		str = ft_strjoin_nl(str, gnl->buf);
		while (gnl->buf[i] && gnl->buf[i] != '\n')
			i++;
		if (gnl->buf[i] == '\n')
		{
			*line = str;
			gnl->j = i + 1;
			return (1);
		}
	}
	*line = str;
	gnl->j = 0;
	if (!*str)
		return (0);
	return (1);
}

int					ft_gnl(char **line, t_gnl *gnl)
{
	char			*str;
	int				i;

	if (gnl->fd < 0 || read(gnl->fd, gnl->buf, 0) == -1 || !line)
		return (-1);
	str = ft_strnew(1);
	if (gnl->j != 0)
	{
		i = gnl->j;
		str = ft_strjoin_nl(str, gnl->buf + i);
		while (gnl->buf[i] && gnl->buf[i] != '\n')
			i++;
		if (gnl->buf[i] == '\n')
		{
			*line = str;
			gnl->j = i + 1;
			return (1);
		}
	}
	return (ft_read(line, str, gnl));
}

t_gnl				*ft_aux(t_gnl *catch, int fd)
{
	while (catch != NULL && catch->fd != fd)
		catch = catch->next;
	return (catch);
}

int					get_next_line(const int fd, char **line)
{
	static t_gnl	*first;
	t_gnl			*catch;

	catch = first;
	if (first == NULL)
	{
		if (!(catch = (t_gnl *)malloc(sizeof(t_gnl))))
			return (-1);
		catch->j = -1;
		catch->fd = fd;
		catch->next = NULL;
		first = catch;
		return (ft_gnl(line, first));
	}
	catch = ft_aux(catch, fd);
	if (catch == NULL)
	{
		if (!(catch = (t_gnl *)malloc(sizeof(t_gnl))))
			return (-1);
		catch->j = 0;
		catch->fd = fd;
		catch->next = first;
		first = catch;
	}
	return (ft_gnl(line, catch));
}
