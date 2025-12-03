/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:11:30 by viceda-s          #+#    #+#             */
/*   Updated: 2025/12/02 15:58:31 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	init_mlx(&cub);
	load_textures(&cub);
	setup_hooks(&cub);
	mlx_loop(cub.mlx);
	cleanup(&cub);
	return (0);
}
