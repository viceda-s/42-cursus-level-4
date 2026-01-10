/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:09:03 by rbaldin           #+#    #+#             */
/*   Updated: 2025/11/06 13:23:06 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

char	*parse_texture_path(char **ptr)
{
	char	*start;
	char	*path;
	int		len;

	if (!ptr || !*ptr)
		return (NULL);
	skipping_emptiness(ptr);
	if (ft_strncmp(*ptr, "tx:", 3) != 0)
		return (NULL);
	*ptr += 3;
	start = *ptr;
	len = 0;
	while (start[len] && start[len] != ' ' && start[len] != '\t'
		&& start[len] != '\n')
		len++;
	if (len == 0)
		return (NULL);
	path = ft_substr(start, 0, len);
	*ptr += len;
	skipping_emptiness(ptr);
	return (path);
}

char	*parse_bump_map_path(char **ptr)
{
	char	*start;
	char	*path;
	int		len;

	if (!ptr || !*ptr)
		return (NULL);
	skipping_emptiness(ptr);
	if (ft_strncmp(*ptr, "bm:", 3) != 0)
		return (NULL);
	*ptr += 3;
	start = *ptr;
	len = 0;
	while (start[len] && start[len] != ' ' && start[len] != '\t'
		&& start[len] != '\n')
		len++;
	if (len == 0)
		return (NULL);
	path = ft_substr(start, 0, len);
	*ptr += len;
	skipping_emptiness(ptr);
	return (path);
}

void	skip_texture(char **ptr)
{
	if (!ptr || !*ptr)
		return ;
	skipping_emptiness(ptr);
	if (ft_strncmp(*ptr, "tx:", 3) == 0)
	{
		*ptr += 3;
		while (**ptr && **ptr != ' ' && **ptr != '\t' && **ptr != '\n')
			(*ptr)++;
		skipping_emptiness(ptr);
	}
}
