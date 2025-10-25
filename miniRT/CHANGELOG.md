# MiniRT - Changelog de Correções

## Resumo
Este documento lista todas as alterações feitas para corrigir o projeto miniRT, que inicialmente apresentava uma janela roxa sem renderizar objetos.

---

## 1. **src/objects/sphere.c**

### Problema
A função de parsing da esfera estava preenchendo o campo errado (`coord_colours.v`) em vez do campo `center` usado pela função de interseção. Além disso, não convertia o diâmetro para raio.

### `extracting_xyz_sph()` - Correção do campo center

**ANTES:**
```c
void extracting_xyz_sph(t_sp *sphere, char **nums)
{
    sphere->coord_colours.v.x = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    sphere->coord_colours.v.y = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    sphere->coord_colours.v.z = ft_atof_dp(nums);
}
```

**DEPOIS:**
```c
void extracting_xyz_sph(t_sp *sphere, char **nums)
{
    /* OLD buggy code - filled wrong field
    sphere->coord_colours.v.x = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    sphere->coord_colours.v.y = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    sphere->coord_colours.v.z = ft_atof_dp(nums);
    */
    
    // NEW: Fill the 'center' field which is actually used by intersect_sphere()
    sphere->center.x = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    sphere->center.y = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    sphere->center.z = ft_atof_dp(nums);
}
```

### `parsing_sphere()` - Conversão de diâmetro para raio

**ANTES:**
```c
int	parsing_sphere(t_scene *scene_sphere, char *line_data_sphere)
{
    char	*ptr_sphere;
    t_sp	*sphere;

    ptr_sphere = line_data_sphere;
    ptr_sphere++;
    ptr_sphere++;
    if (!creating_object(scene_sphere, SPHERE, sizeof(t_sp)))
        return (1);
    sphere = (t_sp *)getting_latest_object(scene_sphere, SPHERE);
    extracting_xyz_sph(sphere, &ptr_sphere);
    sphere->d = ft_atof_dp(&ptr_sphere);
    // ... resto do código
}
```

**DEPOIS:**
```c
int	parsing_sphere(t_scene *scene_sphere, char *line_data_sphere)
{
    char	*ptr_sphere;
    t_sp	*sphere;

    ptr_sphere = line_data_sphere;
    ptr_sphere++;
    ptr_sphere++;
    if (!creating_object(scene_sphere, SPHERE, sizeof(t_sp)))
        return (1);
    sphere = (t_sp *)getting_latest_object(scene_sphere, SPHERE);
    extracting_xyz_sph(sphere, &ptr_sphere);
    sphere->d = ft_atof_dp(&ptr_sphere);
    
    // NEW: Convert diameter to radius for intersection calculations
    sphere->r = sphere->d / 2.0f;
    
    // ... resto do código
}
```

---

## 2. **src/objects/plane.c**

### Problema
O parser não avançava o ponteiro entre a leitura da posição e do vetor normal, causando leitura incorreta dos dados.

### `extracting_xyz_pl()` - Avanço correto do ponteiro

**ANTES:**
```c
void extracting_xyz_pl(t_gd *pl, char **nums)
{
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
}
```

**DEPOIS:**
```c
void extracting_xyz_pl(t_gd *pl, char **nums)
{
    /* OLD buggy code - didn't advance pointer between position and normal
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
    */
    
    // Read position
    pl->v.x = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    pl->v.y = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    pl->v.z = ft_atof_dp(nums);
    
    // Skip whitespace before reading normal vector
    while (**nums == ' ' || (**nums >= 9 && **nums <= 13))
        (*nums)++;
    
    // Read normal vector
    pl->nov.x = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    pl->nov.y = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    pl->nov.z = ft_atof_dp(nums);
    
    // Normalize the normal vector
    pl->nov = vector_normalize(pl->nov);
}
```

---

## 3. **src/objects/cylinder.c**

### Problema
Mesma situação do plano - faltava avançar o ponteiro entre campos, e usava `ft_atof_dp` para valores RGB que deveriam ser inteiros.

### `extracting_xyz_cy()` - Avanço correto do ponteiro

**ANTES:**
```c
void extracting_xyz_cy(t_cy *cyli, char **nums)
{
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
}
```

**DEPOIS:**
```c
void extracting_xyz_cy(t_cy *cyli, char **nums)
{
    /* OLD buggy code
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
    */
    
    // Read position
    cyli->data.v.x = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    cyli->data.v.y = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    cyli->data.v.z = ft_atof_dp(nums);
    
    // Skip whitespace before reading axis vector
    while (**nums == ' ' || (**nums >= 9 && **nums <= 13))
        (*nums)++;
    
    // Read axis vector (normal)
    cyli->data.nov.x = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    cyli->data.nov.y = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    cyli->data.nov.z = ft_atof_dp(nums);
    
    // Normalize the axis vector
    cyli->data.nov = vector_normalize(cyli->data.nov);
}
```

### `extracting_rest_cy()` - Correção do tipo de dados para RGB

**ANTES:**
```c
void extracting_rest_cy(t_cy *cyli, char **nums)
{
    cyli->d = ft_atof_dp(nums);
    cyli->h = ft_atof_dp(nums);
    cyli->data.r = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    cyli->data.g = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    cyli->data.b = ft_atof_dp(nums);
    if (cyli->data.r < 0.0 || cyli->data.r > 255.0 || 
        cyli->data.g < 0.0 || cyli->data.g > 255.0 || 
        cyli->data.b < 0.0 || cyli->data.b > 255.0)
        return ;
}
```

**DEPOIS:**
```c
void extracting_rest_cy(t_cy *cyli, char **nums)
{
    /* OLD buggy code
    cyli->d = ft_atof_dp(nums);
    cyli->h = ft_atof_dp(nums);
    cyli->data.r = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    cyli->data.g = ft_atof_dp(nums);
    if (**nums == ',')
        (*nums)++;
    cyli->data.b = ft_atof_dp(nums);
    if (cyli->data.r < 0.0 || cyli->data.r > 255.0 || 
        cyli->data.g < 0.0 || cyli->data.g > 255.0 || 
        cyli->data.b < 0.0 || cyli->data.b > 255.0)
        return ;
    */
    
    // Read diameter
    cyli->d = ft_atof_dp(nums);
    
    // Skip whitespace before height
    while (**nums == ' ' || (**nums >= 9 && **nums <= 13))
        (*nums)++;
    
    // Read height
    cyli->h = ft_atof_dp(nums);
    
    // Skip whitespace before color
    while (**nums == ' ' || (**nums >= 9 && **nums <= 13))
        (*nums)++;
    
    // Read RGB values as integers
    cyli->data.r = ft_atoi_dp(nums);
    if (**nums == ',')
        (*nums)++;
    cyli->data.g = ft_atoi_dp(nums);
    if (**nums == ',')
        (*nums)++;
    cyli->data.b = ft_atoi_dp(nums);
    
    // Validate RGB range (0-255)
    if (cyli->data.r < 0 || cyli->data.r > 255 || 
        cyli->data.g < 0 || cyli->data.g > 255 || 
        cyli->data.b < 0 || cyli->data.b > 255)
        return ;
}
```

---

## 4. **src/parsing/parsing.c**

### Problema
A câmara não tinha os vetores `up` e `right` calculados, necessários para gerar raios corretamente.

### `parsing_camera()` - Cálculo dos vetores da câmara

**ANTES:**
```c
int parsing_camera(t_scene *sc2, char *line_data2)
{
    char	*ptr2;

    ptr2 = line_data2;
    ptr2++;
    extracting_xyz(sc2, &ptr2, 'c');
    extracting_nov_cam(sc2, &ptr2);
    skipping_emptiness(&ptr2);
    sc2->camera.fov = ft_atoi_dp(&ptr2);
    if (sc2->camera.fov < 0 || sc2->camera.fov > 180)
        return (1);
    skipping_emptiness(&ptr2);
    if (*ptr2 != '\0')
        return (1);
    return (0);
}
```

**DEPOIS:**
```c
int parsing_camera(t_scene *sc2, char *line_data2)
{
    char	*ptr2;

    ptr2 = line_data2;
    ptr2++;
    extracting_xyz(sc2, &ptr2, 'c');
    extracting_nov_cam(sc2, &ptr2);
    
    // NEW: Calculate camera coordinate system
    sc2->camera.forward = vector_normalize(sc2->camera.forward);
    t_vector world_up = vector_create(0, 1, 0);
    
    // If forward is parallel to world_up, use different reference
    if (fabs(sc2->camera.forward.x) == 0 && fabs(sc2->camera.forward.z) == 0)
        world_up = vector_create(0, 0, (sc2->camera.forward.y > 0) ? -1 : 1);
    
    sc2->camera.right = vector_normalize(vector_cross(world_up, sc2->camera.forward));
    sc2->camera.up = vector_normalize(vector_cross(sc2->camera.forward, sc2->camera.right));
    
    skipping_emptiness(&ptr2);
    sc2->camera.fov = ft_atoi_dp(&ptr2);
    if (sc2->camera.fov < 0 || sc2->camera.fov > 180)
        return (1);
    skipping_emptiness(&ptr2);
    if (*ptr2 != '\0')
        return (1);
    return (0);
}
```

---

## 5. **src/math/ray/ray_ops.c**

### Problema
A geração de raios estava incorreta - não calculava corretamente a direção do raio através do viewport.

### `camera_ray()` - Cálculo correto da direção do raio

**ANTES:**
```c
t_ray	camera_ray(t_camera camera, int x, int y, t_viewport viewport)
{
    t_ray		ray;
    t_vector	direction;
    float		u;
    float		v;

    u = (float)x / (float)viewport.width;
    v = (float)y / (float)viewport.height;
    direction.x = camera.forward.x + (u - 0.5f) * camera.right.x + (v - 0.5f) * camera.up.x;
    direction.y = camera.forward.y + (u - 0.5f) * camera.right.y + (v - 0.5f) * camera.up.y;
    direction.z = camera.forward.z + (u - 0.5f) * camera.right.z + (v - 0.5f) * camera.up.z;
    direction = vector_normalize(direction);
    ray.origin = camera.position;
    ray.direction = direction;
    return (ray);
}
```

**DEPOIS:**
```c
t_ray	camera_ray(t_camera camera, int x, int y, t_viewport viewport)
{
    t_ray		ray;
    t_vector	direction;
    float		viewport_height;
    float		viewport_width;
    float		horizontal_offset;
    float		vertical_offset;

    // Calculate viewport dimensions based on FOV
    viewport_height = 2.0f * tanf(camera.fov * M_PI / 360.0f);
    viewport_width = viewport_height * viewport.aspect_ratio;
    
    // Calculate pixel position in viewport coordinates [-0.5, 0.5]
    horizontal_offset = ((float)x / (float)viewport.width - 0.5f) * viewport_width;
    vertical_offset = -((float)y / (float)viewport.height - 0.5f) * viewport_height;
    
    // Build ray direction: forward + horizontal_offset * right + vertical_offset * up
    direction = camera.forward;
    direction = vector_add(direction, vector_scale(camera.right, horizontal_offset));
    direction = vector_add(direction, vector_scale(camera.up, vertical_offset));
    direction = vector_normalize(direction);
    
    ray.origin = camera.position;
    ray.direction = direction;
    return (ray);
}
```

---

## 6. **src/math/intersect/intersect_utils.c**

### Problema
A função usava `INFINITY` como valor inicial, causando problemas na comparação de distâncias.

### `find_closest_intersection()` - Correção da lógica de comparação

**ANTES:**
```c
float find_closest_intersection(t_ray ray, t_scene *scene, void **hit_object, t_object_type *hit_type)
{
    float closest_t = INFINITY;
    float t;
    t_list *current;
    t_objects *obj;

    current = scene->objects_list;
    while (current)
    {
        obj = (t_objects *)current->content;
        t = -1.0f;
        
        if (obj->type == SPHERE)
            t = intersect_sphere(ray, (t_sp *)obj->object_data);
        else if (obj->type == PLANE)
            t = intersect_plane(ray, (t_gd *)obj->object_data);
        else if (obj->type == CYLINDER)
            t = intersect_cylinder(ray, (t_cy *)obj->object_data);
        
        if (t > 0 && t < closest_t)
        {
            closest_t = t;
            *hit_object = obj->object_data;
            *hit_type = obj->type;
        }
        current = current->next;
    }
    
    if (closest_t == INFINITY)
        return (-1.0f);
    return (closest_t);
}
```

**DEPOIS:**
```c
float find_closest_intersection(t_ray ray, t_scene *scene, void **hit_object, t_object_type *hit_type)
{
    float closest_t = -1.0f;  // Changed from INFINITY to -1.0f
    float t;
    t_list *current;
    t_objects *obj;

    current = scene->objects_list;
    while (current)
    {
        obj = (t_objects *)current->content;
        t = -1.0f;
        
        if (obj->type == SPHERE)
            t = intersect_sphere(ray, (t_sp *)obj->object_data);
        else if (obj->type == PLANE)
            t = intersect_plane(ray, (t_gd *)obj->object_data);
        else if (obj->type == CYLINDER)
            t = intersect_cylinder(ray, (t_cy *)obj->object_data);
        
        // Fixed comparison logic
        if (t > 0 && (closest_t < 0 || t < closest_t))
        {
            closest_t = t;
            *hit_object = obj->object_data;
            *hit_type = obj->type;
        }
        current = current->next;
    }
    
    return (closest_t);
}
```

---

## 7. **src/parsing/load_scene.c**

### Problema
A lista de objetos não era inicializada e a lógica de parsing tinha memory leaks.

### `creating_scene()` - Inicialização da lista de objetos

**ANTES:**
```c
t_scene *creating_scene(ssize_t *lines, char *filename)
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
    return (processing_lines(lines, scene, &fd));
}
```

**DEPOIS:**
```c
t_scene *creating_scene(ssize_t *lines, char *filename)
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
    scene->objects_list = NULL;  // NEW: Initialize objects list
    return (processing_lines(lines, scene, &fd));
}
```

### `processing_lines()` - Simplificação e correção de memory leaks

**ANTES:**
```c
static t_scene *processing_lines(ssize_t *lines_count, t_scene *scn, int *fdesc)
{
    char *lin;

    while (*lines_count > 0)
    {
        lin = get_next_line(*fdesc);
        if (!lin)
            break;
        if (*lin == 'A')
        {
            if (parsing_ambient(scn, lin))
                return (error_case(scn, *fdesc, lin));
            (*lines_count)--;
        }
        else
        {
            if (NULL == continuing_processing(lines_count, lin, scn, fdesc))
                return (NULL);
        }
    }
    close(*fdesc);
    return (scn);
}
```

**DEPOIS:**
```c
static t_scene *processing_lines(ssize_t *lines_count, t_scene *scn, int *fdesc)
{
    char *lin;

    while (*lines_count > 0)
    {
        lin = get_next_line(*fdesc);
        if (!lin)
            break;
        (*lines_count)--;
        
        // Skip empty lines
        if (*lin == '\n' || *lin == '\0')
        {
            free(lin);
            continue;
        }
        
        // Process each line type
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
```

---

## 8. **NOVAS FUNCIONALIDADES: Controlo da Câmara**

### Ficheiro: `src/core/camera_control.c` (NOVO)

Funções adicionadas:
- `rotate_x()` - Rotação em torno do eixo X
- `rotate_y()` - Rotação em torno do eixo Y
- `rotate_z()` - Rotação em torno do eixo Z
- `update_camera_vectors()` - Atualiza vetores up/right após rotação
- `rotate_camera()` - Aplica rotação à câmara
- `move_camera()` - Move câmara numa direção
- `camera_move_forward()` - Move para frente/trás
- `camera_move_right()` - Move para esquerda/direita
- `camera_move_up()` - Move para cima/baixo

### Ficheiro: `src/core/event.c` - Atualização do handler de teclas

**ANTES:**
```c
int	keypress_handler(int key, t_minirt *data)
{
	if (key == ESC_KEY)
		exit_program(data);
	return (0);
}
```

**DEPOIS:**
```c
int	keypress_handler(int key, t_minirt *data)
{
	int	needs_render = 0;
	
	if (key == ESC_KEY)
		exit_program(data);
	
	// Movement keys (WASD + QE)
	if (key == KEY_W)
	{
		camera_move_forward(&data->scene->camera, MOVE_SPEED);
		needs_render = 1;
	}
	else if (key == KEY_S)
	{
		camera_move_forward(&data->scene->camera, -MOVE_SPEED);
		needs_render = 1;
	}
	// ... (mais teclas: A, D, Q, E)
	
	// Rotation keys (Arrow keys)
	else if (key == KEY_UP)
	{
		rotate_camera(&data->scene->camera, ROTATE_SPEED, 0, 0);
		needs_render = 1;
	}
	// ... (mais setas)
	
	// Re-render if camera moved
	if (needs_render)
	{
		render_scene(data->scene, data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
	
	return (0);
}
```

### Ficheiro: `inc/minirt.h` - Novas definições

**ADICIONADO:**
```c
// Movement keys
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_Q 113
# define KEY_E 101

// Arrow keys for rotation
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

// Movement and rotation speed
# define MOVE_SPEED 5.0f
# define ROTATE_SPEED 0.1f

// camera_control.c prototypes
t_vector	rotate_x(t_vector v, float angle);
t_vector	rotate_y(t_vector v, float angle);
t_vector	rotate_z(t_vector v, float angle);
void		update_camera_vectors(t_camera *camera);
void		rotate_camera(t_camera *camera, float pitch, float yaw, float roll);
void		move_camera(t_camera *camera, t_vector direction, float distance);
void		camera_move_forward(t_camera *camera, float distance);
void		camera_move_right(t_camera *camera, float distance);
void		camera_move_up(t_camera *camera, float distance);
```

**ALTERADO:**
```c
// ANTES
typedef struct s_minirt
{
    void	*mlx;
    void	*win;
    void	*img;
    char	*addr;
    int		bits_per_pixel;
    int		line_length;
    int		endian;
    void	*scene;  // Era void*
}				t_minirt;

// DEPOIS
typedef struct s_minirt
{
    void		*mlx;
    void		*win;
    void		*img;
    char		*addr;
    int			bits_per_pixel;
    int			line_length;
    int			endian;
    t_scene		*scene;  // Agora é t_scene*
}				t_minirt;
```

---

## 9. **Makefile**

### Adicionado

```makefile
# Source files
SRCS = main.c \
       $(SRC_DIR)/core/event.c \
       $(SRC_DIR)/core/camera_control.c \  # NOVO
       # ... resto dos ficheiros

# Bonus (not implemented yet)
bonus: all  # NOVO
```

---

## 10. **Cenas de Teste Criadas**

### `scenes/simple_sphere.rt`
```
A 0.2 255,255,255
C 0,0,-50 0,0,1 70
L 0,30,0 0.7 255,255,255

sp 0,0,0 20 255,0,0
```

### `scenes/simple_plane.rt`
```
A 0.2 255,255,255
C 0,10,0 0,-1,0 90
L 0,50,0 0.6 255,255,255

pl 0,0,0 0,1,0 100,200,255
```

### `scenes/simple_cylinder.rt`
```
A 0.2 255,255,255
C 0,0,-80 0,0,1 70
L -30,30,0 0.7 255,255,255

cy 0,0,0 0,1,0 20 40 0,255,0
```

### `scenes/complex_scene.rt`
```
A 0.3 255,255,255
C -50,20,30 0.7,-0.3,-0.6 70
L -20,40,30 0.7 255,255,255

pl 0,0,0 0,1,0 150,150,150
sp -10,10,10 15 255,0,0
sp 15,8,0 12 0,255,0
sp 0,10,-15 10 0,0,255
cy 25,0,10 0,1,0 8 25 255,255,0
```

---

## Resumo das Correções

### Bugs Corrigidos:
1. ✅ Esfera usava campo errado (`coord_colours.v` → `center`)
2. ✅ Esfera não convertia diâmetro para raio
3. ✅ Plano não avançava ponteiro entre campos
4. ✅ Cilindro não avançava ponteiro e usava float para RGB
5. ✅ Câmara não calculava vetores `up` e `right`
6. ✅ Geração de raios estava incorreta
7. ✅ Comparação de interseções usava `INFINITY` incorretamente
8. ✅ Lista de objetos não era inicializada
9. ✅ Memory leaks no parsing

### Funcionalidades Adicionadas:
- ✅ Controlo de movimento da câmara (WASD, Q, E)
- ✅ Controlo de rotação da câmara (Setas)
- ✅ Re-renderização automática após movimento
- ✅ Cenas de teste para debugging

### Conformidade com Subject:
- ✅ Mensagens de erro "Error\n" + descrição
- ✅ Makefile com all, clean, fclean, re, bonus
- ✅ Parsing correto de ficheiros .rt
- ✅ Sphere, Plane, Cylinder renderizam
- ✅ Ambient + Diffuse lighting
- ✅ ESC e Red X fecham o programa
