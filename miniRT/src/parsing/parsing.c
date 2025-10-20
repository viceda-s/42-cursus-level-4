//
// Created by rbaldin on 10/15/25.
//

#include "minirt.h"

int parsing_ambient(t_scene *sc1, char *line_data1)
{
    char    *ptr1;

    ptr1 = line_data1;
    if (*ptr1 >= 'A' && *ptr1 <= 'Z')
        ptr1++;
    sc1->ambient.ratio = ft_atof_dp(&ptr1);
    if (sc1->ambient.ratio < 0.0 || sc1->ambient.ratio > 1.0)
        return (1);
    while (*ptr1 == ' ' || (*ptr1 >= 9 && *ptr1 <= 13))
        ptr1++;
    sc1->ambient.colours.r = ft_atoi_dp(&ptr1);
    if (*ptr1 == ',')
        ptr1++;
    sc1->ambient.colours.g = ft_atoi_dp(&ptr1);
    if (*ptr1 == ',')
        ptr1++;
    sc1->ambient.colours.b = ft_atoi_dp(&ptr1);
    skipping_emptiness(&ptr1);
    if (*ptr1 != '\0')
        return (1);
    return (0);
}

int parsing_camera(t_scene *sc2, char *line_data2)
{
    char    *ptr2;

    ptr2 = line_data2;
    ptr2++;
    extracting_xyz(sc2, &ptr2, 'c');
    extracting_nov_xyz(sc2, &ptr2, 'c');
    if (sc2->camera.coord_nov.nov_x < -1.0 || sc2->camera.coord_nov.nov_x > 1.0
        || sc2->camera.coord_nov.nov_y < -1.0 || sc2->camera.coord_nov.nov_y > 1.0
        || sc2->camera.coord_nov.nov_z < -1.0 || sc2->camera.coord_nov.nov_z > 1.0)
        return (1);
    sc2->camera.fov = ft_atoi_dp(&ptr2);
    if (sc2->camera.fov < 0 || sc2->camera.fov > 180)
        return (1);
    skipping_emptiness(&ptr2);
    if (*ptr2 != '\0')
        return (1);
    return (0);
}

int parsing_light(t_scene *sc3, char *line_data3)
{
    char    *ptr3;

    ptr3 = line_data3;
    ptr3++;
    extracting_xyz(sc3, &ptr3, 'l');
    sc3->light.br = ft_atof_dp(&ptr3);
    if (sc3->light.br < 0.0 || sc3->light.br > 1.0)
        return (1);
    sc3->light.coord.r = ft_atoi_dp(&ptr3);
    if (*ptr3 == ',')
        ptr3++;
    sc3->light.coord.g = ft_atoi_dp(&ptr3);
    if (*ptr3 == ',')
        ptr3++;
    sc3->light.coord.b = ft_atoi_dp(&ptr3);
    skipping_emptiness(&ptr3);
    if (*ptr3 != '\0')
        return (1);
    return (0);
}

int parsing_objects(t_scene *sc4, char *line_data4)
{
    if (ft_strncmp(line_data4, "sp ", 3) == 0)
    {
        if (creating_object(sc4, SPHERE, sizeof(t_sp)))
            return (parsing_sphere(sc4, line_data4));
        return (1);
    }
    else if (ft_strncmp(line_data4, "pl ", 3) == 0)
    {
        if (creating_object(sc4, PLANE, sizeof(t_pl)))
            return (parsing_plane(sc4, line_data4));
        return (1);
    }
    else if (ft_strncmp(line_data4, "cy ", 3) == 0)
    {
        if (creating_object(sc4, CYLINDER, sizeof(t_cy)))
            return (parsing_cylinder(sc4, line_data4));
        return (1);
    }
    else
        return (1);
}