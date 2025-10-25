//
// Created by rbaldin on 10/10/25.
//


/*
Your program must take as its first argument a scene description file with the .rt
extension.
◦ Each type of element can be separated by one or more line breaks.
◦ Each type of information from an element can be separated by one or more
spaces.
◦ Each type of element can be set in any order in the file.
◦ Elements defined by a capital letter can only be declared once in the scene.
 */

 #include "minirt.h"

size_t lines_counting(char *filename)
{
    int fd;
    ssize_t lines;
    char *line;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (-1);
    lines = 0;
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        free(line);
        lines++;
    }
    close(fd);
    return (lines);
}

static  t_scene *error_case(t_scene *scene_error, int fd_error, char *l_error)
{
    close(fd_error);
    free(l_error);
    free(scene_error);
    return (NULL);
}

static t_scene  *processing_lines(ssize_t *lines_count, t_scene *scn, int *fdesc)
{
    char *lin;

    while (*lines_count > 0)
    {
        lin = get_next_line(*fdesc);
        if (!lin)
            break;
        (*lines_count)--;
        
        if (*lin == '\n' || *lin == '\0')
        {
            free(lin);
            continue;
        }
        
        if (*lin == 'A')
        {
            if (parsing_ambient(scn, lin))
                return (error_case(scn, *fdesc, lin));
            free(lin);
        }
        else if (*lin == 'C')
        {
            if (parsing_camera(scn, lin))
                return (error_case(scn, *fdesc, lin));
            free(lin);
        }
        else if (*lin == 'L')
        {
            if (parsing_light(scn, lin))
                return (error_case(scn, *fdesc, lin));
            free(lin);
        }
        else
        {
            if (parsing_objects(scn, lin))
                return (error_case(scn, *fdesc, lin));
            free(lin);
        }
    }
    close(*fdesc);
    return (scn);
}

t_scene    *creating_scene(ssize_t *lines, char *filename)
{
    t_scene *scene;
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (NULL);
    scene = malloc(sizeof(t_scene));
    if (!scene)
    {
        close(fd);
        return (NULL);
    }
    scene->objects_list = NULL;
    return (processing_lines(lines, scene, &fd));
}
t_scene	*load_scene(char *filename)
{
    ssize_t lines;
    t_scene *scene;

    lines = lines_counting(filename);
    if (lines < 0)
        return (NULL);
    scene = creating_scene(&lines, filename);
    if (!scene)
        return (NULL);
    return (scene);
}