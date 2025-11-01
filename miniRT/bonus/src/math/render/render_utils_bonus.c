/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:59:42 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/30 14:09:34 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:21:32 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/29 15:47:24 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	build_tbn_from_normal(t_vector n, t_vector *t, t_vector *b)
{
	/* Robustly pick a tangent not parallel to n */
	const t_vector up = {0.0f, 1.0f, 0.0f};
	const t_vector right = {1.0f, 0.0f, 0.0f};
	t_vector ref = (fabsf(vector_dot(n, (t_vector){0,1,0})) < 0.99f) ? up : right;
	*t = vector_normalize(vector_cross(ref, n));
	*b = vector_cross(n, *t);
}

static float	fracf(float x)
{
	return (x - floorf(x));
}

static float	height_fn(float u, float v)
{
	/* Simple periodic bump pattern */
	const float k = (float)(2.0 * M_PI);
	return 0.5f + 0.5f * sinf(k * u) * sinf(k * v);
}

static t_vector	perturb_from_height(float u, float v, float strength,
					 t_vector T, t_vector B, t_vector N)
{
	const float du = 0.002f;
	const float dv = 0.002f;
	float h = height_fn(u, v);
	float hx = height_fn(u + du, v) - h;
	float hy = height_fn(u, v + dv) - h;
	/* Tangent-space normal from height field gradient */
	t_vector n_tan = { -strength * hx / du, -strength * hy / dv, 1.0f };
	n_tan = vector_normalize(n_tan);
	/* Transform to world */
	t_vector n_world;
	n_world.x = n_tan.x * T.x + n_tan.y * B.x + n_tan.z * N.x;
	n_world.y = n_tan.x * T.y + n_tan.y * B.y + n_tan.z * N.y;
	n_world.z = n_tan.x * T.z + n_tan.y * B.z + n_tan.z * N.z;
	return vector_normalize(n_world);
}

static void	apply_bump_if_any(t_shade *s)
{
	if (s->hit_type == SPHERE)
	{
		t_sp *sp = (t_sp *)s->hit_object;
		if (!sp->coord_colours.has_bump)
			return;
		/* Sphere UV from normal */
		t_vector N = s->normal;
		t_vector T, B;
		build_tbn_from_normal(N, &T, &B);
		float u = 0.5f + atan2f(N.z, N.x) / (2.0f * (float)M_PI);
		float v = 0.5f - asinf(N.y) / (float)M_PI;
		u = fracf(u * (sp->coord_colours.bump_uv.x != 0.0f ? sp->coord_colours.bump_uv.x : 1.0f));
		v = fracf(v * (sp->coord_colours.bump_uv.y != 0.0f ? sp->coord_colours.bump_uv.y : 1.0f));
		s->normal = perturb_from_height(u, v, sp->coord_colours.bump_strength, T, B, N);
	}
	else if (s->hit_type == PLANE)
	{
		t_gd *pl = (t_gd *)s->hit_object;
		if (!pl->has_bump)
			return;
		/* Plane UV from projection onto T,B basis */
		t_vector N = vector_normalize(pl->nov);
		t_vector T, B;
		build_tbn_from_normal(N, &T, &B);
		t_vector p_local = vector_sub(s->hit_point, pl->v);
		float u = vector_dot(p_local, T);
		float v = vector_dot(p_local, B);
		u = fracf(u * (pl->bump_uv.x != 0.0f ? pl->bump_uv.x : 1.0f));
		v = fracf(v * (pl->bump_uv.y != 0.0f ? pl->bump_uv.y : 1.0f));
		s->normal = perturb_from_height(u, v, pl->bump_strength, T, B, N);
	}
	else if (s->hit_type == CYLINDER)
	{
		/* Optional: can be added later; keep geometric normal for now */
		(void)s; /* no-op to silence warnings if compiled separately */
	}
}

/**
 * @brief Retrieves the material color from an object based on its type.
 * 
 * Extracts the RGB color information from the object's data structure.
 * Different object types store their color in different fields.
 * 
 * @param object_data Pointer to the object's data structure.
 * @param type The type of the object (SPHERE, PLANE, or CYLINDER).
 * @return The material color as a t_gd struct, or a default black color if
 *         the type is unknown.
 */
static t_gd	getting_material_color(void *object_data, t_object_type type)
{
	if (type == SPHERE)
		return (((t_sp *)object_data)->coord_colours);
	else if (type == PLANE)
		return (*((t_gd *)object_data));
	else if (type == CYLINDER)
		return (((t_cy *)object_data)->data);
	return ((t_gd){
		.r = 50,
		.g = 50,
		.b = 100,
		.v = {0, 0, 0},
		.nov = {0, 0, 0}
	});
}

/**
 * @brief Calculates the surface normal at a point on a sphere.
 * 
 * The normal at any point on a sphere is the normalized vector from the
 * sphere's center to that point.
 * 
 * @param object_data Pointer to the sphere object data.
 * @param hit_point The point on the sphere's surface
 * where intersection occurred.
 * @return The normalized surface normal vector at the hit point.
 */
static t_vector	get_sphere_normal(void *object_data, t_vector hit_point)
{
	t_sp	*sphere;

	sphere = (t_sp *)object_data;
	return (vector_normalize(vector_sub(hit_point, sphere->coord_colours.v)));
}

/**
 * @brief Calculates the surface normal at a point on a cylinder.
 * 
 * Computes the perpendicular distance from the hit point to the cylinder's
 * central axis to determine the surface normal.
 * 
 * @param object_data Pointer to the cylinder object data.
 * @param hit_point The point on the cylinder's surface
 * where intersection occurred.
 * @return The normalized surface normal vector at the hit point.
 */
static t_vector	get_cylinder_normal(void *object_data, t_vector hit_point)
{
	t_cy		*cylinder;
	t_vector	oc;
	float		m;
	t_vector	normal;

	cylinder = (t_cy *)object_data;
	oc = vector_sub(hit_point, cylinder->data.v);
	m = vector_dot(oc, cylinder->data.nov);
	normal = vector_sub(oc, vector_scale(cylinder->data.nov, m));
	return (vector_normalize(normal));
}

/**
 * @brief Gets the surface normal for any object type at a given hit point.
 * 
 * Dispatches to the appropriate normal calculation function based on the
 * object type.
 * 
 * @param object_data Pointer to the object's data structure.
 * @param type The type of the object (SPHERE, PLANE, or CYLINDER).
 * @param hit_point The point on the object's surface
 * where intersection occurred.
 * @return The normalized surface normal vector at the hit point, or a default
 *         upward vector if the type is unknown.
 */
static t_vector	getting_normal_for_object(void *object_data,
			t_object_type type, t_vector hit_point)
{
	if (type == SPHERE)
		return (get_sphere_normal(object_data, hit_point));
	else if (type == PLANE)
		return (vector_normalize(((t_gd *)object_data)->nov));
	else if (type == CYLINDER)
		return (get_cylinder_normal(object_data, hit_point));
	return ((t_vector){0, 1, 0});
}

/**
 * @brief Traces a ray through the scene and computes the color.
 * 
 * Finds the closest intersection point along the ray, calculates the surface
 * normal, and applies lighting to determine the final pixel color. Returns
 * a background color if no intersection is found.
 * 
 * @param ray The ray being traced through the scene.
 * @param scene The scene containing all objects and lighting.
 * @return The computed color for the ray, or a default background color
 *         if no intersection occurs.
 */
t_gd	trace_ray(t_ray ray, t_scene *scene)
{
	float			t;
	void			*hit_object;
	t_object_type	hit_type;
	t_shade			s;

	t = find_closest_intersection(ray, scene, &hit_object, &hit_type);
	if (t > 0)
	{
		s.hit_point = vector_add(ray.origin, vector_scale(ray.direction, t));
		s.normal = getting_normal_for_object(hit_object, hit_type, s.hit_point);
		s.view_dir = ray.direction;
		s.material_color = getting_material_color(hit_object, hit_type);
		s.scene = scene;
		s.hit_object = hit_object;
		s.hit_type = hit_type;
		apply_bump_if_any(&s);
		return (calculate_lighting(&s));
	}
	return ((t_gd){
		.r = 50,
		.g = 50,
		.b = 100,
		.v = {0, 0, 0},
		.nov = {0, 0, 0}
	});
}
