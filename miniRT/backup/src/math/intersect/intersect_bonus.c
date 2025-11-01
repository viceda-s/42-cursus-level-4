/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 07:50:10 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/27 13:59:33 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * @brief Solves a quadratic equation ax^2 + bx + c = 0.
 *
 * Calculates the discriminant and computes both roots of the quadratic equation.
 * The roots are stored in the t1 and t2 fields of the quadratic struct.
 *
 * @param q Pointer to a quadratic struct holding coefficients a, b, c.
 *          The roots t1 and t2 will be stored in this struct.
 * @return Returns true if real roots are found, false otherwise.
 */
static bool	solve_quadratic(t_quadratic *q)
{
	float	discriminant;

	discriminant = q->b * q->b - 4.0f * q->a * q->c;
	if (discriminant < 0)
		return (false);
	q->t1 = (-q->b - sqrtf(discriminant)) / (2.0f * q->a);
	q->t2 = (-q->b + sqrtf(discriminant)) / (2.0f * q->a);
	return (true);
}

/**
 * @brief Calculates the intersection of a ray with a sphere.
 *
 * Uses the geometric ray-sphere intersection formula by solving a quadratic
 * equation. Returns the closest valid intersection point along the ray.
 *
 * @param ray The ray being cast.
 * @param sphere The sphere object to intersect with.
 * @return The distance along the ray to the intersection point, or -1.0f
 *         if no valid intersection occurs.
 */
float	intersect_sphere(t_ray ray, t_sp *sphere)
{
	t_vector	oc;
	t_quadratic	q;
	float		radius;

	radius = sphere->d / 2.0f;
	oc = vector_sub(ray.origin, sphere->coord_colours.v);
	q.a = vector_dot(ray.direction, ray.direction);
	q.b = 2.0f * vector_dot(oc, ray.direction);
	q.c = vector_dot(oc, oc) - (radius * radius);
	if (!solve_quadratic(&q))
		return (-1.0f);
	if (q.t1 > 0.001f && q.t2 > 0.001f)
		return (fminf(q.t1, q.t2));
	if (q.t1 > 0.001f)
		return (q.t1);
	if (q.t2 > 0.001f)
		return (q.t2);
	return (-1.0f);
}

/**
 * @brief Calculates the intersection of a ray with a plane.
 *
 * Uses the ray-plane intersection formula by computing the dot product
 * between the plane normal and ray direction. Returns -1 if the ray is
 * parallel to the plane or if the intersection is behind the ray origin.
 *
 * @param ray The ray being cast.
 * @param plane The plane object to intersect with.
 * @return The distance along the ray to the intersection point, or -1.0f
 *         if no valid intersection occurs.
 */
float	intersect_plane(t_ray ray, t_gd *plane)
{
	float		denom;
	float		t;
	t_vector	p0l0;
	t_vector	plane_normal;

	plane_normal = vector_create(plane->nov.x, plane->nov.y, plane->nov.z);
	denom = vector_dot(plane_normal, ray.direction);
	if (fabs(denom) < 0.0001f)
		return (-1);
	p0l0 = vector_sub(plane->v, ray.origin);
	t = vector_dot(p0l0, plane_normal) / denom;
	if (t > 0.001f)
		return (t);
	return (-1);
}

/**
 * @brief Checks for intersection with the cylinder's top and bottom caps.
 *
 * Treats each cap as a circular disk and checks if the ray intersects
 * either cap within the cylinder's radius. Updates the closest intersection
 * distance if a valid cap intersection is found.
 *
 * @param ray The ray being cast.
 * @param cyl The cylinder object.
 * @param t Pointer to the current closest intersection distance. This value will
 *          be updated if a closer intersection with a cap is found.
 * @return The updated closest intersection distance.
 */
static float	check_caps(t_ray ray, t_cy *cyl, float *t)
{
	float		t_cap;
	t_vector	p;
	t_vector	center_cap;
	float		denom;

	denom = vector_dot(ray.direction, cyl->data.nov);
	if (fabs(denom) < 0.0001f)
		return (*t);
	t_cap = (vector_dot(cyl->data.v, cyl->data.nov) \
- vector_dot(ray.origin, cyl->data.nov)) / denom;
	if (t_cap > 0.001f && t_cap < *t)
	{
		p = ray_at(ray, t_cap);
		if (vector_length(vector_sub(p, cyl->data.v)) < (cyl->d / 2.0f))
			*t = t_cap;
	}
	center_cap = vector_add(cyl->data.v, vector_scale(cyl->data.nov, cyl->h));
	t_cap = (vector_dot(center_cap, cyl->data.nov) \
- vector_dot(ray.origin, cyl->data.nov)) / denom;
	if (t_cap > 0.001f && t_cap < *t)
	{
		p = ray_at(ray, t_cap);
		if (vector_length(vector_sub(p, center_cap)) < (cyl->d / 2.0f))
			*t = t_cap;
	}
	return (*t);
}

/**
 * @brief Calculates the intersection of a ray with a cylinder.
 *
 * Computes intersections with the infinite cylinder surface and checks if
 * the intersection points lie within the cylinder's height bounds. Also
 * checks for intersections with the top and bottom caps.
 *
 * @param ray The ray being cast.
 * @param cylinder The cylinder object to intersect with.
 * @return The distance to the closest intersection point, or -1.0f if no
 *         valid intersection occurs.
 */
float	intersect_cylinder(t_ray ray, t_cy *cylinder)
{
	t_vector	oc;
	t_quadratic	q;
	float		y1;
	float		y2;
	float		closest_t;

	oc = vector_sub(ray.origin, cylinder->data.v);
	q.a = vector_dot(ray.direction, ray.direction) \
- powf(vector_dot(ray.direction, cylinder->data.nov), 2);
	q.b = 2.0f * (vector_dot(ray.direction, oc) \
- (vector_dot(ray.direction, cylinder->data.nov) \
* vector_dot(oc, cylinder->data.nov)));
	q.c = vector_dot(oc, oc) - powf(vector_dot(oc, cylinder->data.nov), 2) \
- powf(cylinder->d / 2.0f, 2);
	if (!solve_quadratic(&q))
		return (-1.0f);
	y1 = vector_dot(oc, cylinder->data.nov) + q.t1 \
* vector_dot(ray.direction, cylinder->data.nov);
	y2 = vector_dot(oc, cylinder->data.nov) + q.t2 \
* vector_dot(ray.direction, cylinder->data.nov);
	closest_t = INFINITY;
	if (q.t1 > 0.001f && y1 >= 0 && y1 <= cylinder->h)
		closest_t = q.t1;
	if (q.t2 > 0.001f && y2 >= 0 && y2 <= cylinder->h && q.t2 < closest_t)
		closest_t = q.t2;
	closest_t = check_caps(ray, cylinder, &closest_t);
	if (closest_t == INFINITY)
		return (-1.0f);
	return (closest_t);
}
