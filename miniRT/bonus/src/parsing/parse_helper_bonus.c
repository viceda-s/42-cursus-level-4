/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checker_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/06 11:57:50 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_vector	parse_vector(char **ptr)
{
	t_vector	v;

	v.x = ft_atof_dp(ptr);
	skip_comma(ptr);
	v.y = ft_atof_dp(ptr);
	skip_comma(ptr);
	v.z = ft_atof_dp(ptr);
	skipping_emptiness(ptr);
	return (v);
}

int	parse_color(char **ptr, t_gd *col)
{
	if (!ptr || !*ptr || !col)
		return (1);
	col->r = ft_atoi_dp(ptr);
	skip_comma(ptr);
	col->g = ft_atoi_dp(ptr);
	skip_comma(ptr);
	col->b = ft_atoi_dp(ptr);
	col->checker = false;
	if (col->r < 0 || col->r > 255 || col->g < 0 || col->g > 255 || \
col->b < 0 || col->b > 255)
		return (1);
	return (0);
}

void	parse_checker(char **ptr, bool *checker)
{
	if (!ptr || !*ptr || !checker)
		return ;
	skipping_emptiness(ptr);
	*checker = false;
	if (ft_strncmp(*ptr, "checker", 7) == 0 || ft_strncmp(*ptr, "ck", 2) == 0)
	{
		if (ft_strncmp(*ptr, "checker", 7) == 0)
			*ptr += 7;
		else
			*ptr += 2;
		*checker = true;
		skipping_emptiness(ptr);
	}
}

static void	parse_bump_params(char **ptr, float *str, t_vector *uv)
{
	t_vector	buv;

	if (**ptr == '=')
	{
		*ptr += 1;
		*str = ft_atof_dp(ptr);
	}
	skipping_emptiness(ptr);
	if (ft_strncmp(*ptr, "buv=", 4) == 0)
	{
		*ptr += 4;
		buv.x = ft_atof_dp(ptr);
		skip_comma(ptr);
		buv.y = ft_atof_dp(ptr);
		buv.z = 0.0f;
		*uv = buv;
		skipping_emptiness(ptr);
	}
}

void	parse_bump(char **ptr, bool *has, float *str, t_vector *uv)
{
	if (!ptr || !*ptr)
		return ;
	*has = false;
	*str = 1.0f;
	*uv = (t_vector){1.0f, 1.0f, 0.0f};
	skipping_emptiness(ptr);
	if (ft_strncmp(*ptr, "bump", 4) != 0)
		return ;
	*ptr += 4;
	*has = true;
	skipping_emptiness(ptr);
	parse_bump_params(ptr, str, uv);
}
