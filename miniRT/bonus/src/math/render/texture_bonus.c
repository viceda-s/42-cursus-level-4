/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 00:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/05 22:03:44 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_texture	*load_texture(void *mlx, char *filepath)
{
	t_texture	*tex;

	if (!mlx || !filepath)
		return (NULL);
	tex = malloc(sizeof(t_texture));
	if (!tex)
		return (NULL);
	tex->img = mlx_xpm_file_to_image(mlx, filepath,
			&tex->width, &tex->height);
	if (!tex->img)
	{
		free(tex);
		return (NULL);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
	{
		mlx_destroy_image(mlx, tex->img);
		free(tex);
		return (NULL);
	}
	return (tex);
}

static int	load_texture_from_path(void *mlx, t_texture *tex)
{
	if (!mlx || !tex || !tex->filepath)
		return (0);
	tex->img = mlx_xpm_file_to_image(mlx, tex->filepath,
			&tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Warning: Failed to load texture: %s\n", tex->filepath);
		return (0);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
	{
		mlx_destroy_image(mlx, tex->img);
		tex->img = NULL;
		return (0);
	}
	return (1);
}

static void	load_maps(void *mlx, t_texture *texture, t_texture *bump_map)
{
	if (texture)
		load_texture_from_path(mlx, texture);
	if (bump_map)
		load_texture_from_path(mlx, bump_map);
}

static void	load_object_textures(void *mlx, t_objects *obj)
{
	if (obj->type == SPHERE)
		load_maps(mlx, ((t_sp *)obj->object_data)->texture,
			((t_sp *)obj->object_data)->bump_map);
	else if (obj->type == PLANE)
		load_maps(mlx, ((t_gd *)obj->object_data)->texture,
			((t_gd *)obj->object_data)->bump_map);
	else if (obj->type == CYLINDER)
		load_maps(mlx, ((t_cy *)obj->object_data)->texture,
			((t_cy *)obj->object_data)->bump_map);
	else if (obj->type == CUBE)
		load_maps(mlx, ((t_cu *)obj->object_data)->texture,
			((t_cu *)obj->object_data)->bump_map);
}

void	load_scene_textures(void *mlx, t_scene *scene)
{
	t_list		*obj_node;
	t_objects	*obj;

	if (!mlx || !scene)
		return ;
	obj_node = scene->objects_list;
	while (obj_node)
	{
		obj = (t_objects *)obj_node->content;
		load_object_textures(mlx, obj);
		obj_node = obj_node->next;
	}
}
