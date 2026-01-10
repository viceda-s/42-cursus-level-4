/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 00:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/05 16:52:18 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * parse_texture_sphere
 *
 * Parse optional texture for sphere from scene file.
 *
 * If texture is specified (tx:path), loads it using load_texture.
 * Texture pointer is stored in sphere structure.
 *
 * @param ptr Pointer to current position in line.
 * @param sp  Sphere structure to populate.
 * @param mlx MLX pointer for loading texture.
 * @note       Safe to call even if no texture is specified.
 */

void	parse_texture_sphere(char **ptr, t_sp *sp, void *mlx)
{
	char	*tex_path;

	if (!ptr || !*ptr || !sp)
		return ;
	sp->texture = NULL;
	skipping_emptiness(ptr);
	if (ft_strncmp(*ptr, "tx:", 3) != 0)
		return ;
	tex_path = parse_texture_path(ptr);
	if (!tex_path)
		return ;
	sp->texture = load_texture(mlx, tex_path);
	if (!sp->texture)
		printf("Warning: Failed to load texture: %s\n", tex_path);
	free(tex_path);
}

/**
 * parse_texture_plane
 *
 * Parse optional texture for plane from scene file.
 *
 * @param ptr Pointer to current position in line.
 * @param pl  Plane (t_gd) structure to populate.
 * @param mlx MLX pointer for loading texture.
 */

void	parse_texture_plane(char **ptr, t_gd *pl, void *mlx)
{
	char	*tex_path;

	if (!ptr || !*ptr || !pl)
		return ;
	pl->texture = NULL;
	skipping_emptiness(ptr);
	if (ft_strncmp(*ptr, "tx:", 3) != 0)
		return ;
	tex_path = parse_texture_path(ptr);
	if (!tex_path)
		return ;
	pl->texture = load_texture(mlx, tex_path);
	if (!pl->texture)
		printf("Warning: Failed to load texture: %s\n", tex_path);
	free(tex_path);
}

/**
 * parse_texture_cylinder
 *
 * Parse optional texture for cylinder from scene file.
 *
 * @param ptr Pointer to current position in line.
 * @param cy  Cylinder structure to populate.
 * @param mlx MLX pointer for loading texture.
 */

void	parse_texture_cylinder(char **ptr, t_cy *cy, void *mlx)
{
	char	*tex_path;

	if (!ptr || !*ptr || !cy)
		return ;
	cy->texture = NULL;
	skipping_emptiness(ptr);
	if (ft_strncmp(*ptr, "tx:", 3) != 0)
		return ;
	tex_path = parse_texture_path(ptr);
	if (!tex_path)
		return ;
	cy->texture = load_texture(mlx, tex_path);
	if (!cy->texture)
		printf("Warning: Failed to load texture: %s\n", tex_path);
	free(tex_path);
}

/**
 * parse_texture_cube
 *
 * Parse optional texture for cube from scene file.
 *
 * @param ptr Pointer to current position in line.
 * @param cu  Cube structure to populate.
 * @param mlx MLX pointer for loading texture.
 */

void	parse_texture_cube(char **ptr, t_cu *cu, void *mlx)
{
	char	*tex_path;

	if (!ptr || !*ptr || !cu)
		return ;
	cu->texture = NULL;
	skipping_emptiness(ptr);
	if (ft_strncmp(*ptr, "tx:", 3) != 0)
		return ;
	tex_path = parse_texture_path(ptr);
	if (!tex_path)
		return ;
	cu->texture = load_texture(mlx, tex_path);
	if (!cu->texture)
		printf("Warning: Failed to load texture: %s\n", tex_path);
	free(tex_path);
}
