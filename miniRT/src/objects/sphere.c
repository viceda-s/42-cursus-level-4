//
// Created by rbaldin on 10/17/25.
//

# include "../inc/minirt.h"
/*
bool creating_sphere(t_scene *scene_sp)
{
    t_sp    *sphere;
    t_objects   *ball_container;
    t_list    *new_ball_node;

    sphere = malloc(sizeof(t_sp));
    if (!sphere)
        return (false);
    ball_container = malloc(sizeof(t_objects));
    if (!ball_container)
    {
        free(sphere);
        return (false);
    }
    ball_container->type = SPHERE;
    ball_container->object = sphere;
    new_ball_node = ft_lstnew(ball_container);
    if (!new_ball_node)
    {
        free(sphere);
        free(ball_container);
        return (false);
    }
    ft_lstadd_front(&scene_sp->objects, new_ball_node);
    return (true);
}

static  t_sp    *getting_latest_sphere(t_scene *scene_lb) // latest ball
{
    t_objects   *ball;

    if (!scene_lb || !scene_lb->objects || !scene_lb->objects->content)
        return (NULL);
    ball = (t_objects *)scene_lb->objects->content;
    if (ball->type != SPHERE)
            return (NULL);
    return ((t_sp *)ball->object);
}
*/

static  t_sp    *extracting_xyz_sph(t_scene *scene_coord, char **nums)
{
    t_sp    *sp;

    sp = (t_sp *)getting_latest_object(scene_coord, SPHERE);
    if (!sp)
    {
        return (NULL);
    }
    sp->coord_colours.v.x = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    sp->coord_colours.v.y = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    sp->coord_colours.v.z = ft_atof_dp(nums);
    return (sp);
}

/*
// NEW code that filled sphere->center and converted diameter to radius
int parsing_sphere(t_scene *scene_sphere, char *line_data_sphere)
{
    char    *ptr_sp;
    t_sp    *sphe;

    ptr_sp = line_data_sphere;
    ptr_sp += 2;
    sphe = extracting_xyz_sph(scene_sphere, &ptr_sp);
    if (!sphe)
    {
        return (1);
    }
    sphe->d = ft_atof_dp(&ptr_sp);
    sphe->r = sphe->d / 2.0f;  // Converter diâmetro para raio
    sphe->coord_colours.r = ft_atoi_dp(&ptr_sp);
    if (*ptr_sp == ',')
        ptr_sp++;
    sphe->coord_colours.g = ft_atoi_dp(&ptr_sp);
    if (*ptr_sp == ',')
        ptr_sp++;
    sphe->coord_colours.b = ft_atoi_dp(&ptr_sp);
    if (sphe->d <= 0.0 || sphe->coord_colours.r < 0 || sphe->coord_colours.r > 255
        || sphe->coord_colours.g < 0 || sphe->coord_colours.g > 255
        || sphe->coord_colours.b < 0 || sphe->coord_colours.b > 255)
    {
        return (1);
    }
    skipping_emptiness(&ptr_sp);
    if (*ptr_sp != '\0')
    {
        return (1);
    }
    return (0);
}
*/

// OLD code - uses diameter directly, no conversion to radius
int parsing_sphere(t_scene *scene_sphere, char *line_data_sphere)
{
    char    *ptr_sp;
    t_sp    *sphe;

    ptr_sp = line_data_sphere;
    ptr_sp += 2;
    sphe = extracting_xyz_sph(scene_sphere, &ptr_sp);
    if (!sphe)
    {
        return (1);
    }
    sphe->d = ft_atof_dp(&ptr_sp);
    sphe->coord_colours.r = ft_atoi_dp(&ptr_sp);
    if (*ptr_sp == ',')
        ptr_sp++;
    sphe->coord_colours.g = ft_atoi_dp(&ptr_sp);
    if (*ptr_sp == ',')
        ptr_sp++;
    sphe->coord_colours.b = ft_atoi_dp(&ptr_sp);
    if (sphe->d <= 0.0 || sphe->coord_colours.r < 0 || sphe->coord_colours.r > 255
        || sphe->coord_colours.g < 0 || sphe->coord_colours.g > 255
        || sphe->coord_colours.b < 0 || sphe->coord_colours.b > 255)
    {
        return (1);
    }
    skipping_emptiness(&ptr_sp);
    if (*ptr_sp != '\0')
    {
        return (1);
    }
    return (0);
}