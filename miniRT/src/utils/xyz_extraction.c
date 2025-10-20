//
// Created by rbaldin on 10/17/25.
//

# include "../inc/minirt.h"
/*
static  void    extracting_xyz_plane(t_scene *scene_coord, char *nums, char element)
{
        if ('p' == element)
        {
                scene_coord->light.coord.v.x = ft_atof_dp(&nums);
                if (*nums == ',')
                        nums++;
                scene_coord->light.coord.v.y = ft_atof_dp(&nums);
                if (*nums == ',')
                        nums++;
                scene_coord->light.coord.v.z = ft_atof_dp(&nums);
        }
}

static  void    extracting_xyz_sph(t_scene *scene_coord, char *nums, char element)
{

        t_sp    *sp;

        if ('s' == element)
        {
                sp = getting_latest_sphere(scene_coord);
                sp->coord_colours.v.x = ft_atof_dp(&nums);
                if (*nums == ',')
                        nums++;
                sp->coord_colours.v.y = ft_atof_dp(&nums);
                if (*nums == ',')
                        nums++;
                sp->coord_colours.v.z = ft_atof_dp(&nums);
        }
        else

                extracting_xyz_plane(scene_coord, nums, element);
}
*/
void    extracting_xyz(t_scene *scene_coord, char **nums, char element)
{
        if (!scene_coord)
                return ;
        if ('c' == element)
        {
                scene_coord->camera.coord_nov.v.x = ft_atof_dp(nums);
                if (**nums == ',')
                        (*nums)++;
                scene_coord->camera.coord_nov.v.y = ft_atof_dp(nums);
                if (**nums == ',')
                        (*nums)++;
                scene_coord->camera.coord_nov.v.z = ft_atof_dp(nums);
        }
        else if ('l' == element)
        {
                scene_coord->light.coord.v.x = ft_atof_dp(nums);
                if (**nums == ',')
                        (*nums)++;
                scene_coord->light.coord.v.y = ft_atof_dp(nums);
                if (**nums == ',')
                        (*nums)++;
                scene_coord->light.coord.v.z = ft_atof_dp(nums);
        }
       // else
          //      extracting_xyz_plane(scene_coord, nums, element);
}

void    extracting_nov_xyz(t_scene *scene_nov, char **novs, char element)
{
        if ('c' == element)
        {
                scene_nov->camera.coord_nov.nov_x = ft_atof_dp(novs);
                if (**novs == ',')
                        (*novs)++;
                scene_nov->camera.coord_nov.nov_y = ft_atof_dp(novs);
                if (**novs == ',')
                        (*novs)++;
                scene_nov->camera.coord_nov.nov_z = ft_atof_dp(novs);
        }
}