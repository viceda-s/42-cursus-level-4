/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 07:50:10 by viceda-s          #+#    #+#             */
/*   Updated: 2025/10/25 10:26:59 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Solves a quadratic equation ax^2 + bx + c = 0.
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

/*
// OLD code without debug
float	intersect_sphere(t_ray ray, t_sp *sphere)
{
    t_vector	oc;
    t_quadratic	q;

    oc = vector_sub(ray.origin, sphere->center);
    q.a = vector_dot(ray.direction, ray.direction);
    q.b = 2.0f * vector_dot(oc, ray.direction);
    q.c = vector_dot(oc, oc) - (sphere->r * sphere->r);
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
*/

/* Intersect ray with sphere: returns distance (negative if no hit) */
float	intersect_sphere(t_ray ray, t_sp *sphere)
{
    t_vector	oc;
    t_quadratic	q;
    float		radius;

    // Use coord_colours.v for position and d (diameter) for size
    radius = sphere->d / 2.0f;
    oc = vector_sub(ray.origin, sphere->coord_colours.v);
    q.a = vector_dot(ray.direction, ray.direction);
    q.b = 2.0f * vector_dot(oc, ray.direction);
    q.c = vector_dot(oc, oc) - (radius * radius);
    
    if (!solve_quadratic(&q))
        return (-1.0f);
    
    // Return the smallest positive intersection
    if (q.t1 > 0.001f && q.t2 > 0.001f)
        return (fminf(q.t1, q.t2));
    if (q.t1 > 0.001f)
        return (q.t1);
    if (q.t2 > 0.001f)
        return (q.t2);
    return (-1.0f);
}

/* Intersect ray with plane: returns distance (negative if no hit) */
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
    // Check intersection with the bottom cap
    t_cap = (vector_dot(cyl->data.v, cyl->data.nov) - vector_dot(ray.origin, cyl->data.nov)) / denom;
    if (t_cap > 0.001f && t_cap < *t)
    {
        p = ray_at(ray, t_cap);
        // Check if the intersection point is within the cap's radius
        if (vector_length(vector_sub(p, cyl->data.v)) < (cyl->d / 2.0f))
            *t = t_cap;
    }
    // Check intersection with the top cap
    center_cap = vector_add(cyl->data.v, vector_scale(cyl->data.nov, cyl->h));
    t_cap = (vector_dot(center_cap, cyl->data.nov) - vector_dot(ray.origin, cyl->data.nov)) / denom;
    if (t_cap > 0.001f && t_cap < *t)
    {
        p = ray_at(ray, t_cap);
        // Check if the intersection point is within the cap's radius
        if (vector_length(vector_sub(p, center_cap)) < (cyl->d / 2.0f))
            *t = t_cap;
    }
    return (*t);
}

/**
 * @brief Calculates the intersection of a ray with a cylinder.
 * @param ray The ray being cast.
 * @param cylinder The cylinder object.
 * @return The distance to the closest intersection point, or -1.0 if no
 *         intersection occurs.
 */
float	intersect_cylinder(t_ray ray, t_cy *cylinder)
{
    t_vector	oc;
    t_quadratic	q;
    float		y1;
    float		y2;
    float		closest_t;

    // Vector from ray origin to the cylinder's base center
    oc = vector_sub(ray.origin, cylinder->data.v);
    // Coefficients for the quadratic equation to find intersection with an
    // infinite cylinder.
    q.a = vector_dot(ray.direction, ray.direction) - powf(vector_dot(ray.direction, cylinder->data.nov), 2);
    q.b = 2.0f * (vector_dot(ray.direction, oc) - (vector_dot(ray.direction, cylinder->data.nov) * vector_dot(oc, cylinder->data.nov)));
    q.c = vector_dot(oc, oc) - powf(vector_dot(oc, cylinder->data.nov), 2) - powf(cylinder->d / 2.0f, 2);
    // If there are no real roots, the ray doesn't intersect the infinite cylinder.
    if (!solve_quadratic(&q))
        return (-1.0f);
    // Calculate the height (y-coordinate along the cylinder axis) of the
    // intersection points.
    y1 = vector_dot(oc, cylinder->data.nov) + q.t1 * vector_dot(ray.direction, cylinder->data.nov);
    y2 = vector_dot(oc, cylinder->data.nov) + q.t2 * vector_dot(ray.direction, cylinder->data.nov);
    closest_t = INFINITY;
    // Check if the first intersection point is valid and within the cylinder's height.
    if (q.t1 > 0.001f && y1 >= 0 && y1 <= cylinder->h)
        closest_t = q.t1;
    // Check if the second intersection point is valid, within the cylinder's
    // height, and closer than the first.
    if (q.t2 > 0.001f && y2 >= 0 && y2 <= cylinder->h && q.t2 < closest_t)
        closest_t = q.t2;
    // Check for intersections with the end caps, which might be closer.
    closest_t = check_caps(ray, cylinder, &closest_t);
    // If no valid intersection was found, return -1.
    if (closest_t == INFINITY)
        return (-1.0f);
    return (closest_t);
}
