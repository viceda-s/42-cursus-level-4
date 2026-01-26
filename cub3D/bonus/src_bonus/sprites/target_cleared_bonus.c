/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target_cleared_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:30:00 by viceda-s          #+#    #+#             */
/*   Updated: 2026/01/26 14:30:00 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	all_targets_cleared(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (i < cub->target_count)
	{
		if (cub->targets[i].state == TARGET_ACTIVE)
			return (0);
		i++;
	}
	return (1);
}
