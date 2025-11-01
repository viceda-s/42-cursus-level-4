/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:53:04 by rbaldin           #+#    #+#             */
/*   Updated: 2024/12/13 15:24:17 by rbaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*joining(char *part1, char *part2)
{
	char	*buf;

	buf = ft_strjoin(part1, part2);
	free(part1);
	return (buf);
}

static	char	*reading(int fd, char *buf)
{
	ssize_t	br;
	char	*tb;

	if (buf == NULL)
		buf = ft_calloc(1, 1);
	if (buf == NULL)
		return (NULL);
	tb = (char *)malloc(BUFFER_SIZE + 1);
	if (!tb)
		return (free(buf), NULL);
	br = 1;
	while (br > 0)
	{
		br = read(fd, tb, BUFFER_SIZE);
		if (br < 0)
			return (free(buf), free(tb), NULL);
		tb[br] = '\0';
		buf = joining(buf, tb);
		if (!buf)
			return (free(tb), NULL);
		if (ft_strchr(tb, '\n'))
			break ;
	}
	return (free(tb), buf);
}

static	char	*cleaning(char *rem)
{
	char	*rl;
	int		i;

	if (!rem)
		return (NULL);
	i = 0;
	while (rem[i] != '\n' && rem[i] != '\0')
		i++;
	if (rem[i] == '\n')
		i++;
	rl = (char *)malloc(i + 1);
	if (!rl)
		return (NULL);
	rl[i] = '\0';
	while (--i >= 0)
		rl[i] = rem[i];
	return (rl);
}

static	char	*remaining(char *rem)
{
	char	*whatsleft;
	char	*copy;
	int		i;
	int		brem;

	if (!rem)
		return (NULL);
	brem = ft_strlen(rem);
	i = 0;
	while (rem[i] != '\n' && i < brem)
		i++;
	whatsleft = (char *)malloc(brem - i + 1);
	if (!whatsleft)
		return (free(rem), NULL);
	copy = whatsleft;
	if (rem[i] == '\n')
		i++;
	while (rem[i] != '\0')
		*copy++ = rem[i++];
	*copy = '\0';
	free(rem);
	return (whatsleft);
}

char	*get_next_line(int fd)
{
	static char		*montage;
	char			*l;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	montage = reading(fd, montage);
	if (montage == NULL)
		return (NULL);
	l = cleaning(montage);
	if (!l || !(l[0]))
	{
		free(montage);
		montage = NULL;
		return (free(l), NULL);
	}
	montage = remaining(montage);
	return (l);
}
