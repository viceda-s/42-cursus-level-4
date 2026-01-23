/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:50:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/23 12:35:04 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	main(int argc, char **argv)
{
	t_cub3d	cub;

	if (argc != 2)
	{
		err_msg(ERR_ARGS);
		return (1);
	}
	init_cub(&cub);
	parse_file(&cub, argv[1]);
	validate_elements(&cub);
	validate_map(&cub);
	extract_player(&cub);
	init_mlx(&cub);
	load_textures(&cub);
	load_target_textures(&cub);
	load_weapon_sprite(&cub);
	init_player(&cub);
	init_doors(&cub);
	init_targets(&cub);
	setup_hooks(&cub);
	mlx_loop(cub.mlx);
	cleanup(&cub);
	return (0);
}
