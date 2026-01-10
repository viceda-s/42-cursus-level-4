/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:11:31 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/03 15:55:26 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	init_thread(t_thread_data *td, t_minirt *data, int i, int slice_h)
{
	td[i].id = i;
	td[i].data = data;
	td[i].start_y = i * slice_h;
	if (i == NUM_THREADS - 1)
		td[i].end_y = data->win_height;
	else
		td[i].end_y = (i + 1) * slice_h;
}

void	render_scene(t_scene *scene, t_minirt *data)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	thread_data[NUM_THREADS];
	int				i;
	int				slice_height;

	(void)scene;
	slice_height = data->win_height / NUM_THREADS;
	i = 0;
	while (i < NUM_THREADS)
	{
		init_thread(thread_data, data, i, slice_height);
		pthread_create(&threads[i], NULL, render_slice, &thread_data[i]);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
