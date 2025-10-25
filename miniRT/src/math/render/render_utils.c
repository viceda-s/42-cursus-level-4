/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:21:32 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/21 09:32:13 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>

#include "minirt.h"
#include "../../../inc/minirt.h"

/*
// OLD code without debug
static t_gd getting_object_color(void *hit_o, t_object_type hit_t, t_gd co)
{
    t_sp    *sphere;
    t_gd    *plane;
    t_cy    *cylinder;

    if (hit_t == SPHERE)
    {
        sphere = (t_sp *)hit_o;
        co.r = sphere->coord_colours.r;
        co.g = sphere->coord_colours.g;
        co.b = sphere->coord_colours.b;
    }
    else if (hit_t == PLANE)
    {
        plane = (t_gd *)hit_o;
        co.r = plane->r;
        co.g = plane->g;
        co.b = plane->b;
    }
    else if (hit_t == CYLINDER)
    {
        cylinder = (t_cy *)hit_o;
        co.r = cylinder->data.r;
        co.g = cylinder->data.g;
        co.b = cylinder->data.b;
    }
    return (co);
}
*/

static t_gd getting_object_color(void *hit_o, t_object_type hit_t, t_gd co)
{
    t_sp    *sphere;
    t_gd    *plane;
    t_cy    *cylinder;

    if (hit_t == SPHERE)
    {
        sphere = (t_sp *)hit_o;
        co.r = sphere->coord_colours.r;
        co.g = sphere->coord_colours.g;
        co.b = sphere->coord_colours.b;
    }
    else if (hit_t == PLANE)
    {
        plane = (t_gd *)hit_o;
        co.r = plane->r;
        co.g = plane->g;
        co.b = plane->b;
    }
    else if (hit_t == CYLINDER)
    {
        cylinder = (t_cy *)hit_o;
        co.r = cylinder->data.r;
        co.g = cylinder->data.g;
        co.b = cylinder->data.b;
    }
    return (co);
}

static t_vector getting_normal_for_object(void *ho, t_object_type ht, t_vector hp)
{
    t_vector	normal;
    t_sp    *sphere;
    t_gd    *plane;
    t_cy    *cylinder;


    if (SPHERE == ht)
    {
        sphere = (t_sp *)ho;
        sphere->coord_colours.nov = vector_normalize(vector_sub(hp, sphere->coord_colours.v));
        normal = sphere->coord_colours.nov;
    }
    else if (PLANE == ht)
    {
        plane = (t_gd *)ho;
        normal = plane->nov;
    }
    else
    {
        cylinder  = (t_cy *)ho;
        normal = cylinder->data.nov;
    }
    return (normal);
}

static  bool    is_in_shadow(t_vector hp, t_l light, t_scene *scene)
{
    t_ray   shadow_ray;
    void    *hit_o;
    t_object_type hit_t;
    float   t;
    float   l_distance;
    t_vector    diff_to_light;

    diff_to_light = vector_sub(light.coord.v, hp);
    l_distance = vector_length(diff_to_light);
    shadow_ray.direction = vector_normalize(diff_to_light);
    shadow_ray.origin = vector_add(hp, vector_scale(shadow_ray.direction, 0.001f));
    t = find_closest_intersection(shadow_ray, scene, &hit_o, &hit_t);
    if (t > 0 && t < l_distance)
        return (true);
    return (false);
}
// Calculate Lighting (Phong Model)
t_gd calculate_lighting(t_vector hpoint, t_vector normal, t_scene *scene, t_gd material_color)
{
    t_gd    final_color;
    t_l light;
    t_vector    light_dir;
    bool    in_shadow;
    float   diff_intensity;

    final_color.r = material_color.r * scene->ambient.ratio;
    final_color.g = material_color.g * scene->ambient.ratio;
    final_color.b = material_color.b * scene->ambient.ratio;
    light = scene->light;
    light_dir = vector_normalize(vector_sub(light.coord.v, hpoint));
    in_shadow = is_in_shadow(hpoint, light, scene);
    if (!in_shadow)
    {
        diff_intensity = fmax(0.0f, vector_dot(normal, light_dir));
        final_color.r += material_color.r * light.br * diff_intensity;
        final_color.g += material_color.g * light.br * diff_intensity;
        final_color.b += material_color.b * light.br * diff_intensity;
    }
    final_color.r = fmin(255, fmax(0, final_color.r));
    final_color.g = fmin(255, fmax(0, final_color.g));
    final_color.b = fmin(255, fmax(0, final_color.b));
    return (final_color);
}

/*
// OLD code without debug
t_gd	trace_ray(t_ray ray, t_scene *scene)
{
    t_gd			color;
    void			*hit_object;
    t_object_type	hit_type;
    t_vector    hit_point;  //
    t_vector    normal;     //
    float			t;
    // Inicializar cor de fundo (importante!)
    color.r = 50;
    color.g = 50;
    color.b = 100;
    // Teste das intersecções
    t = find_closest_intersection(ray, scene, &hit_object, &hit_type);
    if (t > 0)  // Se há intersecção
    {
        // Calcular o ponto de colisão
        hit_point = vector_add(ray.origin, vector_scale(ray.direction, t));
        // Calcular a normal no ponto de colisão (a implementar depois)
        normal = getting_normal_for_object(hit_object, hit_type, hit_point);
        // Obter a cor do objeto atingido
        color = getting_object_color(hit_object, hit_type, color);
        // Aplicar iluminação (a implementar depois)
        color = calculate_lighting(hit_point, normal, scene, color);
    }
    return (color);
}
*/

t_gd	trace_ray(t_ray ray, t_scene *scene)
{
    t_gd			color;
    void			*hit_object;
    t_object_type	hit_type;
    t_vector		hit_point;
    t_vector		normal;
    float			t;
    
    color.r = 50;
    color.g = 50;
    color.b = 100;
    
    t = find_closest_intersection(ray, scene, &hit_object, &hit_type);
    
    if (t > 0)
    {
        hit_point = vector_add(ray.origin, vector_scale(ray.direction, t));
        normal = getting_normal_for_object(hit_object, hit_type, hit_point);
        color = getting_object_color(hit_object, hit_type, color);
        color = calculate_lighting(hit_point, normal, scene, color);
    }
    return (color);
}

int	color_to_int(t_gd color) // Converts t_gd color to integer format for MLX
{
    return ((color.r << 16) | (color.g << 8) | color.b);
}
