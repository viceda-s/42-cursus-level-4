/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:09:03 by rbaldin           #+#    #+#             */
/*   Updated: 2025/11/05 19:53:21 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	skipping_emptiness(char **str)
{
	while (**str == ' ' || (**str >= 9 && **str <= 13))
		(*str)++;
}

void	skip_comma(char **str)
{
	if (**str == ',')
		(*str)++;
}

static float	getting_float(char **str, float res)
{
	float	power;

	power = 1.0;
	while (ft_isdigit(**str))
	{
		res = res * 10.0 + (**str - '0');
		(*str)++;
	}
	if (**str == '.')
	{
		(*str)++;
		while (ft_isdigit(**str))
		{
			power /= 10.0;
			res = res + (**str - '0') * power;
			(*str)++;
		}
	}
	return (res);
}

float	ft_atof_dp(char **str)
{
	float	result;
	float	sign;

	result = 0.0;
	sign = 1.0;
	skipping_emptiness(str);
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1.0;
		(*str)++;
	}
	return (getting_float(str, result) * sign);
}

int	ft_atoi_dp(char **str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	skipping_emptiness(str);
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	while (ft_isdigit(**str))
	{
		result = result * 10 + (**str - '0');
		(*str)++;
	}
	return (result * sign);
}

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
