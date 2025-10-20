//
// Created by rbaldin on 10/18/25.
//

#include "minirt.h"

bool    creating_object(t_scene *scene_o, t_object_type type_o, size_t size_o)
{
    void    *object_ptr;
    t_objects   *container;
    t_list     *new_object_node;

    object_ptr = malloc(size_o);
    if (!object_ptr)
        return (false);
    container = malloc(sizeof(t_objects));
    if (!container)
    {
        free(object_ptr);
        return (false);
    }
    container->type = type_o;
    container->object_data = object_ptr;
    new_object_node = ft_lstnew(container);
    if (!new_object_node)
    {
        free(object_ptr);
        free(container);
        return (false);
    }
    ft_lstadd_front(&scene_o->objects_list, new_object_node);
    return (true);
}
