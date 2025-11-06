/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 21:51:18 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/05 21:53:17 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	cleanup_map_image(void *mlx, t_texture *map)
{
	if (map && map->img)
	{
		mlx_destroy_image(mlx, map->img);
		map->img = NULL;
	}
}

static void	cleanup_object_maps(void *mlx, t_texture *texture,
				t_texture *bump_map)
{
	cleanup_map_image(mlx, texture);
	cleanup_map_image(mlx, bump_map);
}

void	cleanup_object_texture(void *mlx, t_objects *obj)
{
	if (!obj || !mlx)
		return ;
	if (obj->type == CUBE)
		cleanup_object_maps(mlx, ((t_cu *)obj->object_data)->texture,
			((t_cu *)obj->object_data)->bump_map);
	else if (obj->type == SPHERE)
		cleanup_object_maps(mlx, ((t_sp *)obj->object_data)->texture,
			((t_sp *)obj->object_data)->bump_map);
	else if (obj->type == CYLINDER)
		cleanup_object_maps(mlx, ((t_cy *)obj->object_data)->texture,
			((t_cy *)obj->object_data)->bump_map);
	else if (obj->type == PLANE)
		cleanup_object_maps(mlx, ((t_gd *)obj->object_data)->texture,
			((t_gd *)obj->object_data)->bump_map);
}

void	cleanup_scene_textures(void *mlx, t_scene *scene)
{
	t_list		*obj_node;
	t_objects	*obj;

	if (!scene || !mlx)
		return ;
	obj_node = scene->objects_list;
	while (obj_node)
	{
		obj = (t_objects *)obj_node->content;
		cleanup_object_texture(mlx, obj);
		obj_node = obj_node->next;
	}
}

void	cleanup_scene(t_scene *scene)
{
	if (!scene)
		return ;
	ft_lstclear(&scene->objects_list, free_object);
	ft_lstclear(&scene->lights_list, free_light);
	free(scene);
	scene = NULL;
}
