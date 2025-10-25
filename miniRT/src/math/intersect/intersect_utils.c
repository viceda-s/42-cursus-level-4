/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 08:38:10 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/25 09:01:36 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Encontra a intersecção mais próxima entre todas as esferas da cena
float	find_closest_sphere_intersection(t_ray ray, t_scene *scene, t_sp **hit_sphere)
{
	t_list	*current;
	t_objects *obj;
	t_sp	*sphere;
	float	closest_t;
	float	t;

	closest_t = -1.0f;			// Inicializa com "sem intersecção"
	*hit_sphere = NULL;			// Inicializa ponteiro da esfera atingida
	current = scene->objects_list;	// Percorre lista de objetos

	while (current)
	{
		obj = (t_objects *)current->content;
		if (obj->type == SPHERE)	// Verifica se é uma esfera
		{
			sphere = (t_sp *)obj->object_data;
			t = intersect_sphere(ray, sphere);	// Calcula intersecção

			// Se há intersecção válida e é mais próxima que a anterior
			if (t > 0.001f && (closest_t < 0 || t < closest_t))
			{
				closest_t = t;
				*hit_sphere = sphere;	// Guarda referência da esfera atingida
			}
		}
		current = current->next;
	}

	return (closest_t);	// Retorna distância da intersecção mais próxima
}

// Encontra a intersecção mais próxima entre todos os planos da cena
float	find_closest_plane_intersection(t_ray ray, t_scene *scene, t_gd **hit_plane)
{
	t_list	*current;
	t_objects *obj;
	t_gd	*plane;
	float	closest_t;
	float	t;

	closest_t = -1.0f;			// Inicializa com "sem intersecção"
	*hit_plane = NULL;			// Inicializa ponteiro do plano atingido
	current = scene->objects_list;	// Percorre lista de objetos

	while (current)
	{
		obj = (t_objects *)current->content;
		if (obj->type == PLANE)		// Verifica se é um plano
		{
			plane = (t_gd *)obj->object_data;
			t = intersect_plane(ray, plane);	// Calcula intersecção

			// Se há intersecção válida e é mais próxima que a anterior
			if (t > 0.001f && (closest_t < 0 || t < closest_t))
			{
				closest_t = t;
				*hit_plane = plane;	// Guarda referência do plano atingido
			}
		}
		current = current->next;
	}

	return (closest_t);	// Retorna distância da intersecção mais próxima
}

// Encontra a intersecção mais próxima entre todos os cilindros da cena
float	find_closest_cylinder_intersection(t_ray ray, t_scene *scene, t_cy **hit_cylinder)
{
    t_list		*current;
    t_objects	*obj;
    t_cy		*cylinder;
    float		closest_t;
    float		t;

    closest_t = -1.0f;			// Inicializa com "sem intersecção"
    *hit_cylinder = NULL;		// Inicializa ponteiro do cilindro atingido
    current = scene->objects_list;	// Percorre lista de objetos
    while (current)
    {
        obj = (t_objects *)current->content;
        if (obj->type == CYLINDER)	// Verifica se é um cilindro
        {
            cylinder = (t_cy *)obj->object_data;
            t = intersect_cylinder(ray, cylinder); // Calcula intersecção

            // Se há intersecção válida e é mais próxima que a anterior
            if (t > 0.001f && (closest_t < 0 || t < closest_t))
            {
                closest_t = t;
                *hit_cylinder = cylinder;	// Guarda referência do cilindro atingido
            }
        }
        current = current->next;
    }
    return (closest_t);	// Retorna distância da intersecção mais próxima
}


/*
// OLD buggy code
// Encontra a intersecção mais próxima de qualquer objeto (esfera, plano ou cilindro)
float	find_closest_intersection(t_ray ray, t_scene *scene, void **hit_object, t_object_type *hit_type)
{
    t_sp	*hit_sphere;
    t_gd	*hit_plane;
    t_cy	*hit_cylinder;
    float	sphere_t;
    float	plane_t;
    float	cylinder_t;
    float	closest_t;

    closest_t = INFINITY;
    *hit_object = NULL;

    // Encontra intersecção mais próxima com esferas
    sphere_t = find_closest_sphere_intersection(ray, scene, &hit_sphere);
    if (sphere_t > 0.001f && sphere_t < closest_t)
    {
        closest_t = sphere_t;
        *hit_object = hit_sphere;
        *hit_type = SPHERE;
    }

    // Encontra intersecção mais próxima com planos
    plane_t = find_closest_plane_intersection(ray, scene, &hit_plane);
    if (plane_t > 0.001f && plane_t < closest_t)
    {
        closest_t = plane_t;
        *hit_object = hit_plane;
        *hit_type = PLANE;
    }

    // Encontra intersecção mais próxima com cilindros
    cylinder_t = find_closest_cylinder_intersection(ray, scene, &hit_cylinder);
    if (cylinder_t > 0.001f && cylinder_t < closest_t)
    {
        closest_t = cylinder_t;
        *hit_object = hit_cylinder;
        *hit_type = CYLINDER;
    }

    if (closest_t == INFINITY)
        return (-1.0f);

    return (closest_t);	// Retorna distância do objeto mais próximo
}
*/
// Encontra a intersecção mais próxima de qualquer objeto (esfera, plano ou cilindro)
float	find_closest_intersection(t_ray ray, t_scene *scene, void **hit_object, t_object_type *hit_type)
{
    t_sp	*hit_sphere;
    t_gd	*hit_plane;
    t_cy	*hit_cylinder;
    float	sphere_t;
    float	plane_t;
    float	cylinder_t;
    float	closest_t;

    closest_t = -1.0f;
    *hit_object = NULL;

    // Encontra intersecção mais próxima com esferas
    sphere_t = find_closest_sphere_intersection(ray, scene, &hit_sphere);
    if (sphere_t > 0.001f)
    {
        closest_t = sphere_t;
        *hit_object = hit_sphere;
        *hit_type = SPHERE;
    }

    // Encontra intersecção mais próxima com planos
    plane_t = find_closest_plane_intersection(ray, scene, &hit_plane);
    if (plane_t > 0.001f && (closest_t < 0 || plane_t < closest_t))
    {
        closest_t = plane_t;
        *hit_object = hit_plane;
        *hit_type = PLANE;
    }

    // Encontra intersecção mais próxima com cilindros
    cylinder_t = find_closest_cylinder_intersection(ray, scene, &hit_cylinder);
    if (cylinder_t > 0.001f && (closest_t < 0 || cylinder_t < closest_t))
    {
        closest_t = cylinder_t;
        *hit_object = hit_cylinder;
        *hit_type = CYLINDER;
    }

    return (closest_t);	// Retorna distância do objeto mais próximo
}