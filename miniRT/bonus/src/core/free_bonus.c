/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:50:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/05 21:58:21 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	free_light(void *light_content)
{
	t_l	*l;

	if (!light_content)
		return ;
	l = (t_l *)light_content;
	free(l->scene);
	l->scene = NULL;
	free(l);
}

void	free_texture(void *mlx, t_texture *tex)
{
	if (!tex)
		return ;
	if (tex->img && mlx)
		mlx_destroy_image(mlx, tex->img);
	if (tex->filepath)
		free(tex->filepath);
	free(tex);
}

static void	free_cube(t_cu *cube)
{
	if (!cube)
		return ;
	if (cube->param.axis)
		free(cube->param.axis);
	if (cube->texture)
		free_texture(NULL, cube->texture);
	if (cube->bump_map)
		free_texture(NULL, cube->bump_map);
}

static void	free_object_maps(t_texture *texture, t_texture *bump_map)
{
	if (texture)
		free_texture(NULL, texture);
	if (bump_map)
		free_texture(NULL, bump_map);
}

void	free_object(void *content)
{
	t_objects	*object;

	if (!content)
		return ;
	object = (t_objects *)content;
	if (object->type == CUBE)
		free_cube((t_cu *)object->object_data);
	else if (object->type == SPHERE)
		free_object_maps(((t_sp *)object->object_data)->texture,
			((t_sp *)object->object_data)->bump_map);
	else if (object->type == CYLINDER)
		free_object_maps(((t_cy *)object->object_data)->texture,
			((t_cy *)object->object_data)->bump_map);
	else if (object->type == PLANE)
		free_object_maps(((t_gd *)object->object_data)->texture,
			((t_gd *)object->object_data)->bump_map);
	if (object->object_data)
		free(object->object_data);
	free(object);
}
