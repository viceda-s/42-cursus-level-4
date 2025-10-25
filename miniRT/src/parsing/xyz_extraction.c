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
void    extracting_xyz(t_scene *scene_coord, char **nums, char object_type)
{
        if (!scene_coord)
                return ;
        if ('c' == object_type)
        {
                scene_coord->camera.position.x = ft_atof_dp(nums);
                if (**nums == ',')
                        (*nums)++;
                scene_coord->camera.position.y = ft_atof_dp(nums);
                if (**nums == ',')
                        (*nums)++;
                scene_coord->camera.position.z = ft_atof_dp(nums);
        }
        else if ('l' == object_type)
        {
                scene_coord->light.coord.v.x = ft_atof_dp(nums);
                if (**nums == ',')
                        (*nums)++;
                scene_coord->light.coord.v.y = ft_atof_dp(nums);
                if (**nums == ',')
                        (*nums)++;
                scene_coord->light.coord.v.z = ft_atof_dp(nums);
        }
}

void    extracting_nov_cam(t_scene *scene_nov, char **novs)
{
        scene_nov->camera.forward.x = ft_atof_dp(novs);
        if (**novs == ',')
                (*novs)++;
        scene_nov->camera.forward.y = ft_atof_dp(novs);
        if (**novs == ',')
                (*novs)++;
        scene_nov->camera.forward.z = ft_atof_dp(novs);
}