//
// Created by rbaldin on 10/21/25.
//

#include "../../inc/minirt.h"

/*
// OLD buggy code - lia o vetor normal dos mesmos valores de posição
static  t_cy    *extracting_xyz_cy(t_scene *scene_coord, char **nums)
{
    t_cy    *cyli;

    cyli = (t_cy *) getting_latest_object(scene_coord, CYLINDER);
    if (!cyli)
        return (NULL);
    cyli->data.v.x = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    cyli->data.v.y = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    cyli->data.v.z = ft_atof_dp(nums);
    cyli->data.nov.x = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    cyli->data.nov.y = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    cyli->data.nov.z = ft_atof_dp(nums);
    if (cyli->data.nov.x < -1.0 || cyli->data.nov.x > 1.0 || cyli->data.nov.y < -1.0 || cyli->data.nov.y > 1.0
        || cyli->data.nov.z < -1.0 || cyli->data.nov.z > 1.0)
        return (NULL);
    return (cyli);
}
*/

static  t_cy    *extracting_xyz_cy(t_scene *scene_coord, char **nums)
{
    t_cy    *cyli;

    cyli = (t_cy *) getting_latest_object(scene_coord, CYLINDER);
    if (!cyli)
        return (NULL);
    
    // Ler coordenadas de posição
    cyli->data.v.x = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    cyli->data.v.y = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    cyli->data.v.z = ft_atof_dp(nums);
    
    // Ler vetor normal (eixo do cilindro)
    cyli->data.nov.x = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    cyli->data.nov.y = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    cyli->data.nov.z = ft_atof_dp(nums);
    
    // Normalizar o vetor normal
    cyli->data.nov = vector_normalize(cyli->data.nov);
    
    if (cyli->data.nov.x < -1.0 || cyli->data.nov.x > 1.0 || cyli->data.nov.y < -1.0 || cyli->data.nov.y > 1.0
        || cyli->data.nov.z < -1.0 || cyli->data.nov.z > 1.0)
        return (NULL);
    return (cyli);
}

/*
// OLD buggy code - não avançava o ponteiro entre campos
static int extracting_rest_cy(t_cy *rest_cy, char **pcy)
{
    rest_cy->d = ft_atof_dp(pcy);
    rest_cy->h = ft_atof_dp(pcy);
    rest_cy->data.r = ft_atof_dp(pcy);
    if (**pcy == ',')
        (*pcy)++;
    rest_cy->data.g = ft_atof_dp(pcy);
    if (**pcy == ',')
        (*pcy)++;
    rest_cy->data.b = ft_atof_dp(pcy);
    if (rest_cy->data.r < 0.0 || rest_cy->data.r >255 || rest_cy->data.b < 0.0
        || rest_cy->data.b > 255 || rest_cy->data.g < 0.0 || rest_cy->data.g > 255
        || rest_cy->d <= 0.0 || rest_cy->h <= 0.0)
    {
        return (1);
    }
    return (0);
}
*/

static int extracting_rest_cy(t_cy *rest_cy, char **pcy)
{
    // Avançar espaços antes do diâmetro
    while (**pcy == ' ' || (**pcy >= 9 && **pcy <= 13))
        (*pcy)++;
    
    rest_cy->d = ft_atof_dp(pcy);
    
    // Avançar espaços antes da altura
    while (**pcy == ' ' || (**pcy >= 9 && **pcy <= 13))
        (*pcy)++;
    
    rest_cy->h = ft_atof_dp(pcy);
    
    // Avançar espaços antes da cor
    while (**pcy == ' ' || (**pcy >= 9 && **pcy <= 13))
        (*pcy)++;
    
    rest_cy->data.r = ft_atoi_dp(pcy);
    if (**pcy == ',')
        (*pcy)++;
    rest_cy->data.g = ft_atoi_dp(pcy);
    if (**pcy == ',')
        (*pcy)++;
    rest_cy->data.b = ft_atoi_dp(pcy);
    
    if (rest_cy->data.r < 0 || rest_cy->data.r > 255 || rest_cy->data.b < 0
        || rest_cy->data.b > 255 || rest_cy->data.g < 0 || rest_cy->data.g > 255
        || rest_cy->d <= 0.0 || rest_cy->h <= 0.0)
    {
        return (1);
    }
    return (0);
}

// User input to parse (example):
// cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
int parsing_cylinder(t_scene *scene_cylinder, char *line_data_cylinder)
{
    char    *ptr_cy;
    t_cy    *cyl;

    ptr_cy = line_data_cylinder;
    ptr_cy += 2;
    cyl = extracting_xyz_cy(scene_cylinder, &ptr_cy);
    if (!cyl)
    {
        return (1);
    }
    if (extracting_rest_cy(cyl, &ptr_cy))
        return (1);
    skipping_emptiness(&ptr_cy);
    if (*ptr_cy != '\0')
    {
        return (1);
    }
    return (0);
}
