/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_aa_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:20:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/03 16:12:06 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	stratified_sample(int i, int samples, float *offset_x, float *offset_y)
{
	int		grid_size;
	int		grid_x;
	int		grid_y;
	float	jitter_x;
	float	jitter_y;

	grid_size = (int)sqrtf((float)samples);
	grid_x = i % grid_size;
	grid_y = i / grid_size;
	jitter_x = ((float)rand() / (float)RAND_MAX) * 0.8f + 0.1f;
	jitter_y = ((float)rand() / (float)RAND_MAX) * 0.8f + 0.1f;
	*offset_x = ((float)grid_x + jitter_x) / (float)grid_size - 0.5f;
	*offset_y = ((float)grid_y + jitter_y) / (float)grid_size - 0.5f;
}

float	gaussian_weight(float x, float y, float center_x, float center_y)
{
	float	dx;
	float	dy;
	float	dist_sq;
	float	sigma;

	dx = x - center_x;
	dy = y - center_y;
	dist_sq = dx * dx + dy * dy;
	sigma = 0.5f;
	return (expf(-dist_sq / (2.0f * sigma * sigma)));
}
