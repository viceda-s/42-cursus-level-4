/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/12/02 16:33:13 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	skip_spaces(char **str)
{
	while (**str == ' ' || (**str >= 9 && **str <= 13))
		(*str)++;
}

static void	skip_comma(char **str)
{
	if (**str == ',')
		(*str)++;
}

static int	parse_color_value(char **str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	skip_spaces(str);
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

static int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	parse_rgb(t_cub3d *cub, char *str)
{
	int	r;
	int	g;
	int	b;

	skip_spaces(&str);
	r = parse_color_value(&str);
	skip_comma(&str);
	g = parse_color_value(&str);
	skip_comma(&str);
	b = parse_color_value(&str);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		err_exit(cub, ERR_COLOR_RANGE);
	return (rgb_to_int(r, g, b));
}
