/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:42:20 by rbaldin           #+#    #+#             */
/*   Updated: 2024/12/13 15:23:34 by rbaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		s++;
		i++;
	}
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;
	size_t	total;
	size_t	i;

	if (nmemb != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	total = nmemb * size;
	mem = malloc(total);
	if (mem == NULL)
		return (NULL);
	i = 0;
	while (i < nmemb)
		((unsigned char *)mem)[i++] = '\0';
	return (mem);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (unsigned char) c)
			return ((char *) s);
		s++;
	}
	if ((char) c == '\0')
		return ((char *) s);
	else
		return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ch;
	size_t	l;
	char	*temp;

	if (!s1)
		return (NULL);
	l = ft_strlen(s1) + ft_strlen(s2) + 1;
	ch = (char *)malloc(l * sizeof(char));
	if (!ch)
		return (NULL);
	temp = ch;
	while (*s1)
		*ch++ = *s1++;
	while (*s2)
		*ch++ = *s2++;
	*ch = '\0';
	return (temp);
}
