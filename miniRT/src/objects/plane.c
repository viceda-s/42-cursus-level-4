//
// Created by rbaldin on 10/18/25.
//
# include "../../inc/minirt.h"
/* Excluir funções comentadas depois de testes
static  void    extracting_nov_xyz_obj(t_scene *scene_ob, char **pob, t_object_type typ)
{
    t_gd    *geometric_ob;

    geometric_ob = (t_gd *) getting_latest_object(scene_ob, typ);
    if (!geometric_ob)
        return ;
    geometric_ob->nov_x = ft_atof_dp(pob);
    if (**pob == ',')
        (*pob)++;
    geometric_ob->nov_y = ft_atof_dp(pob);
    if (**pob == ',')
        (*pob)++;
    geometric_ob->nov_z = ft_atof_dp(pob);
}

static t_gd    *extracting_xyz_pl(t_scene *scene_coord, char **nums)
{
    t_gd    *pl;

    pl = (t_gd *) getting_latest_object(scene_coord, PLANE);
    if (!pl)
        return (NULL);
    pl->v.x = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    pl->v.y = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    pl->v.z = ft_atof_dp(nums);
    return (pl);
}


int parsing_plane(t_scene *scene_plane, char *line_data_plane)
{
    char    *ptr_pl;
    t_gd    *pla;

    ptr_pl = line_data_plane;
    ptr_pl += 2;
    pla = extracting_xyz_pl(scene_plane, &ptr_pl);
    if (!pla)
        return (1);
    extracting_nov_xyz_obj(scene_plane, &ptr_pl, PLANE);
    if (pla->nov_z < -1.0 || pla->nov_z > 1.0 || pla->nov_x < -1.0 || pla->nov_x > 1.0
        || pla->nov_y < -1.0 || pla->nov_y > 1.0)
        return (1);
    pla->r = ft_atoi_dp(&ptr_pl);
    if (*ptr_pl == ',')
        ptr_pl++;
    pla->g = ft_atoi_dp(&ptr_pl);
    if (*ptr_pl == ',')
        ptr_pl++;
    pla->b = ft_atoi_dp(&ptr_pl);
    if (pla->r < 0 || pla->r >255 || pla->b < 0 || pla->b > 255 || pla->g < 0 || pla->g > 255)
        return (1);
    skipping_emptiness(&ptr_pl);
    if (*ptr_pl != '\0')
        return (1);
    return (0);
}
*/

/*
// OLD buggy code - lia o vetor normal dos mesmos valores de posição
static  t_gd    *extracting_xyz_pl(t_scene *scene_coord, char **nums)
{
    t_gd    *pl;

    pl = (t_gd *) getting_latest_object(scene_coord, PLANE);
    if (!pl)
        return (NULL);
    pl->v.x = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    pl->v.y = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    pl->v.z = ft_atof_dp(nums);
    pl->nov.x = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    pl->nov.y = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    pl->nov.z = ft_atof_dp(nums);
    return (pl);
}
*/

static  t_gd    *extracting_xyz_pl(t_scene *scene_coord, char **nums)
{
    t_gd    *pl;

    pl = (t_gd *) getting_latest_object(scene_coord, PLANE);
    if (!pl)
        return (NULL);
    // Ler coordenadas de posição
    pl->v.x = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    pl->v.y = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    pl->v.z = ft_atof_dp(nums);
    
    // Ler vetor normal
    pl->nov.x = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    pl->nov.y = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    pl->nov.z = ft_atof_dp(nums);
    
    // Normalizar o vetor normal
    pl->nov = vector_normalize(pl->nov);
    
    return (pl);
}

int parsing_plane(t_scene *scene_plane, char *line_data_plane)
{
    char    *ptr_pl;
    t_gd    *pla;

    ptr_pl = line_data_plane;
    ptr_pl += 2;
    pla = extracting_xyz_pl(scene_plane, &ptr_pl);
    if (!pla)
    {
        return (1);
    }
    if (pla->nov.z < -1.0 || pla->nov.z > 1.0 || pla->nov.x < -1.0 || pla->nov.x > 1.0
        || pla->nov.y < -1.0 || pla->nov.y > 1.0)
    {
        return (1);
    }
    pla->r = ft_atoi_dp(&ptr_pl);
    if (*ptr_pl == ',')
        ptr_pl++;
    pla->g = ft_atoi_dp(&ptr_pl);
    if (*ptr_pl == ',')
        ptr_pl++;
    pla->b = ft_atoi_dp(&ptr_pl);
    if (pla->r < 0 || pla->r >255 || pla->b < 0 || pla->b > 255 || pla->g < 0 || pla->g > 255)
    {
        return (1);
    }
    skipping_emptiness(&ptr_pl);
    if (*ptr_pl != '\0')
    {
        return (1);
    }
    return (0);
}