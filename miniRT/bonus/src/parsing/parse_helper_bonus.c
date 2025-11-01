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

static float	parse_optional_strength(char **ptr, bool *found)
{
	float val;

	*found = false;
	skipping_emptiness(ptr);
	if (**ptr == '=')
	{
		*ptr += 1;
		val = ft_atof_dp(ptr);
		*found = true;
		return (val);
	}
	return (1.0f);
}

static void	parse_optional_buv(char **ptr, t_vector *buv, bool *found)
{
	*found = false;
	skipping_emptiness(ptr);
	if (ft_strncmp(*ptr, "buv=", 4) == 0)
	{
		*ptr += 4;
		buv->x = ft_atof_dp(ptr);
		skip_comma(ptr);
		buv->y = ft_atof_dp(ptr);
		buv->z = 0.0f;
		*found = true;
		skipping_emptiness(ptr);
	}
}

void	parse_bump_plane(char **ptr, t_gd *gd)
{
	bool f1;
	bool f2;
	float strength;
	t_vector buv;

	if (!ptr || !*ptr || !gd)
		return ;
	gd->has_bump = false;
	gd->bump_strength = 1.0f;
	gd->bump_uv = (t_vector){1.0f, 1.0f, 0.0f};
	skipping_emptiness(ptr);
	if (ft_strncmp(*ptr, "bump", 4) == 0)
	{
		*ptr += 4;
		gd->has_bump = true;
		strength = parse_optional_strength(ptr, &f1);
		if (f1)
			gd->bump_strength = strength;
		parse_optional_buv(ptr, &buv, &f2);
		if (f2)
			gd->bump_uv = buv;
	}
}

void	parse_bump_sphere(char **ptr, t_sp *sp)
{
	bool f1;
	bool f2;
	float strength;
	t_vector buv;

	if (!ptr || !*ptr || !sp)
		return ;
	sp->coord_colours.has_bump = false;
	sp->coord_colours.bump_strength = 1.0f;
	sp->coord_colours.bump_uv = (t_vector){1.0f, 1.0f, 0.0f};
	skipping_emptiness(ptr);
	if (ft_strncmp(*ptr, "bump", 4) == 0)
	{
		*ptr += 4;
		sp->coord_colours.has_bump = true;
		strength = parse_optional_strength(ptr, &f1);
		if (f1)
			sp->coord_colours.bump_strength = strength;
		parse_optional_buv(ptr, &buv, &f2);
		if (f2)
			sp->coord_colours.bump_uv = buv;
	}
}

void	parse_bump_cylinder(char **ptr, t_cy *cy)
{
	bool f1;
	bool f2;
	float strength;
	t_vector buv;

	if (!ptr || !*ptr || !cy)
		return ;
	cy->data.has_bump = false;
	cy->data.bump_strength = 1.0f;
	cy->data.bump_uv = (t_vector){1.0f, 1.0f, 0.0f};
	skipping_emptiness(ptr);
	if (ft_strncmp(*ptr, "bump", 4) == 0)
	{
		*ptr += 4;
		cy->data.has_bump = true;
		strength = parse_optional_strength(ptr, &f1);
		if (f1)
			cy->data.bump_strength = strength;
		parse_optional_buv(ptr, &buv, &f2);
		if (f2)
			cy->data.bump_uv = buv;
	}
}

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
