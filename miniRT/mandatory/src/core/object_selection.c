/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_selection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg.>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:29:17 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/04 13:29:17 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_selection_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 00:00:00 by viceda-s          #+#    #+#             */
/*   Updated: 2025/11/03 14:27:48 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Initializes the selected object to be the first in the list.
 * 
 * @param scene The scene containing the objects.
 */
void	init_selection(t_scene *scene)
{
	if (scene && scene->objects_list)
		scene->selected_object = scene->objects_list->content;
	else
		scene->selected_object = NULL;
}

/**
 * @brief Selects the next object in the list.
 * 
 * If no object is selected, it selects the first one. If the last object is
 * selected, it wraps around to the first one.
 * 
 * @param scene The scene containing the objects.
 */
void	select_next_object(t_scene *scene)
{
	t_list	*current;

	if (!scene || !scene->objects_list)
		return ;
	if (!scene->selected_object)
	{
		init_selection(scene);
		return ;
	}
	current = scene->objects_list;
	while (current)
	{
		if (current->content == scene->selected_object)
		{
			if (current->next)
				scene->selected_object = current->next->content;
			else
				scene->selected_object = scene->objects_list->content;
			return ;
		}
		current = current->next;
	}
}
