/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xyz_extraction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:22:34 by rbaldin           #+#    #+#             */
/*   Updated: 2025/11/04 13:52:52 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../../inc/minirt.h"

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
	skipping_emptiness(ptr);
	if (col->r < 0 || col->r > 255 || col->g < 0 || col->g > 255
		|| col->b < 0 || col->b > 255)
		return (1);
	return (0);
}
