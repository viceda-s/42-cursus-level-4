/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:33:09 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/31 15:53:31 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt_bonus.h"

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

void	parse_color(char **ptr, t_gd *col)
{
	if (!ptr || !*ptr || !col)
		return ;

	col->r = ft_atoi_dp(ptr);
	skip_comma(ptr);
	col->g = ft_atoi_dp(ptr);
	skip_comma(ptr);
	col->b = ft_atoi_dp(ptr);
	col->checker = false;
}

void	parse_checker_plane(char **ptr, t_gd *gd)
{
	if (!ptr || !*ptr || !gd)
		return ;
	skipping_emptiness(ptr);
	gd->checker = false;
	if (ft_strncmp(*ptr, "checker", 7) == 0)
	{
		*ptr += 7;
		gd->checker = true;
		skipping_emptiness(ptr);
	}
}

void	parse_checker_sphere(char **ptr, t_sp *sp)
{
	if (!ptr || !*ptr || !sp)
		return ;
	skipping_emptiness(ptr);
	sp->coord_colours.checker = false;
	if (ft_strncmp(*ptr, "checker", 7) == 0)
	{
		*ptr += 7;
		sp->coord_colours.checker = true;
		skipping_emptiness(ptr);
	}
}

void	parse_checker_cylinder(char **ptr, t_cy *cy)
{
	if (!ptr || !*ptr || !cy)
		return ;
	skipping_emptiness(ptr);
	cy->data.checker = false;
	if (ft_strncmp(*ptr, "checker", 7) == 0)
	{
		*ptr += 7;
		cy->data.checker = true;
		skipping_emptiness(ptr);
	}
}
