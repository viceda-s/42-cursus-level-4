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
    {
        return (false);
    }
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

void    *getting_latest_object(t_scene *scene_o, t_object_type type_o)
{
    t_objects   *container;

    if (!scene_o || !scene_o->objects_list || !scene_o->objects_list->content)
        return (NULL);
    container = (t_objects *)scene_o->objects_list->content;
    if (container->type != type_o)
        return (NULL);
    return (container->object_data);
}

/*
void	*getting_latest_object(t_scene *scene_o, t_object_type type_o)
{
    t_list		*last_node;
    t_objects	*obj;

    if (!scene_o || !scene_o->objects_list)
        return (NULL);
    
    last_node = ft_lstlast(scene_o->objects_list);
    if (!last_node || !last_node->content)
        return (NULL);
    
    obj = (t_objects *)last_node->content;
    
    if (obj->type == type_o)
        return (obj->object_data);
    
    return (NULL);
}
*/