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
    size_t lines;
    char *line;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        close(fd);
        return (-1);
    }
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

t_scene    *parsing_scene(size_t *lines, char *filename)
{
    t_scene *scene;
    char *line;
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        close(fd);
        return (NULL);
    }
    scene = malloc(sizeof(t_scene)); // Allocate a single scene structure
    if (!scene)
        return (NULL);
    // Inside t_scene, allocate arrays for objects/lights based on parsed counts
    while (*lines > 0)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        if (*line == 'A')
        {
            if (parsing_ambient(scene, line))
            {
                close(fd);
                free(line);
                free(scene);
                return (NULL);
            }
            (*lines)--;
        }
        if (*line == 'C')
        {
            if (parsing_camera(scene, line))
            {
                close(fd);
                free(line);
                free(scene);
                return (NULL);
            }
            (*lines)--;
        }
        if (*line == 'L')
        {
            if (parsing_light(scene, line))
            {
                close(fd);
                free(line);
                free(scene);
                return (NULL);
            }
            (*lines)--;
        }
        else
        {
            if (parsing_objects(scene, line))
            {
                close(fd);
                free(line);
                free(scene);
                return (NULL);
            }
        }

    }
    return (scene);
}
t_scene	*load_scene(char *filename)
{
    size_t lines;
    t_scene *scene;

    lines = lines_counting(filename);
    if (lines == (size_t)-1) // similar to < 0
        return (NULL);
    scene = parsing_scene(&lines, filename);
    if (!scene)
        return (NULL);
    return (scene);
}