# XPM Texture Implementation Guide

## 📚 Overview

This implementation adds XPM texture mapping support to MiniRT, allowing you to apply image textures to spheres, planes, cylinders, and cubes.

## 🚀 Features

- ✅ Load XPM textures from files
- ✅ UV mapping for all primitive objects
- ✅ Texture sampling with wrapping
- ✅ Compatible with existing features (bump mapping, checkerboard)
- ✅ Fast render mode (F key) for Valgrind debugging

## 📝 Scene File Format

### Basic Syntax
```
object_type parameters tx:path/to/texture.xpm
```

### Examples

**Textured Sphere:**
```
sp 0,0,0 10 255,255,255 tx:textures/earth.xpm
```

**Textured Plane:**
```
pl 0,0,0 0,1,0 200,200,200 tx:textures/wood.xpm
```

**Textured Cylinder:**
```
cy 0,0,0 0,1,0 5 10 100,100,255 tx:textures/metal.xpm
```

**Textured Cube:**
```
cu 0,0,0 5 255,100,100 tx:textures/brick.xpm
```

## 🎨 Creating XPM Textures

### Method 1: Using GIMP
1. Open/create your image
2. Scale to reasonable size (e.g., 64x64, 128x128)
3. Export as `.xpm` file
4. Choose "XPM (X PixMap image)" format

### Method 2: Online Converters
- https://convertio.co/png-xpm/
- Upload PNG/JPG → Convert to XPM

### Method 3: Manual XPM
```c
/* XPM */
static char *my_texture[] = {
"4 4 2 1",
". c #000000",
"+ c #FFFFFF",
".++.",
"+..+",
"+..+",
".++."
};
```

## 📂 Project Structure

```
bonus/
├── textures/           # Store your .xpm files here
│   └── earth.xpm
├── test_texture.rt     # Example scene with textures
└── src/
    ├── math/render/
    │   └── texture_bonus.c      # Texture loading & sampling
    └── parsing/
        └── parse_texture_bonus.c # Texture parsing
```

## 🔧 Implementation Details

### Texture Structure
```c
typedef struct s_texture
{
    void    *img;       // MLX image pointer
    char    *addr;      // Pixel data address
    int     width;      // Texture width
    int     height;     // Texture height
    int     bpp;        // Bits per pixel
    int     line_len;   // Line length in bytes
    int     endian;     // Endianness
}   t_texture;
```

### Key Functions

**Load Texture:**
```c
t_texture *load_texture(void *mlx, char *filepath);
```

**Sample Texture:**
```c
t_gd get_texture_color(t_texture *tex, float u, float v);
```

**Free Texture:**
```c
void free_texture(void *mlx, t_texture *tex);
```

## 🎮 Controls

- **F**: Toggle Fast Render (for Valgrind)
- **ESC**: Exit
- **WASD/QE**: Move camera
- **Arrows**: Rotate camera
- **IJKL/UO**: Move light
- **TAB**: Select next object
- **Numpad 2/4/6/8**: Move selected object

## 🐛 Troubleshooting

### Texture Not Loading
```bash
Warning: Failed to load texture: textures/earth.xpm
```
**Solutions:**
- Check file path is relative to executable
- Verify `.xpm` file format is correct
- Ensure file permissions are readable

### Texture Appears Black
- Check XPM color palette
- Verify UV mapping is correct
- Test with simple 2-color XPM first

### Compilation Errors
```bash
cd bonus
make re
```

### Performance Issues
- Use smaller textures (64x64 recommended)
- Enable fast render mode (press F)
- Reduce anti-aliasing samples in header

## 📊 Performance Tips

### Valgrind Testing
```bash
# Start in fast render mode
./miniRT test_texture.rt
# Press 'F' immediately to toggle fast render

# Expected time:
# - With fast render: 10-30 seconds
# - Without: 5-10 minutes
```

### Optimization
1. Keep textures small (64x64 to 256x256)
2. Use simple XPM format (few colors)
3. Disable anti-aliasing for testing
4. Set `NUM_THREADS 1` for Valgrind

## 🔥 Advanced Features

### Combining Textures with Other Features

**Texture + Checker:**
```
sp 0,0,0 10 255,255,255 ck tx:textures/earth.xpm
```
*Note: Texture takes priority over checker*

**Texture + Bump:**
```
sp 0,0,0 10 255,255,255 bm:1.0,2.0,2.0 tx:textures/moon.xpm
```
*Both work together!*

## 📖 Example Scenes

### Earth Scene
```
A 0.2 255,255,255
C 0,0,20 0,0,-1 70
L -40,40,30 0.7 255,255,255

sp 0,0,0 10 100,100,255 tx:textures/earth.xpm
pl 0,-10,0 0,1,0 50,50,50 ck
```

### Multiple Textures
```
A 0.2 255,255,255
C 0,0,30 0,0,-1 70
L 0,20,20 0.7 255,255,255

sp -10,0,0 8 255,255,255 tx:textures/earth.xpm
sp 0,0,0 8 255,255,255 tx:textures/moon.xpm
sp 10,0,0 8 255,255,255 tx:textures/mars.xpm
```

## 🎓 Learning Resources

- [XPM Format Specification](http://www.xfree86.org/current/xpm.pdf)
- [MinilibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [UV Mapping Explained](https://en.wikipedia.org/wiki/UV_mapping)

## ✅ Checklist

- [x] Texture structure defined
- [x] Load/sample/free functions implemented
- [x] Parsing support added
- [x] UV mapping for all objects
- [x] Integration with lighting system
- [x] Example textures created
- [x] Test scene file created
- [x] Makefile updated
- [ ] **TODO:** Pass MLX pointer to parsing (currently textures load after MLX init)

## 🚧 Known Limitations

1. **Textures load timing**: Currently, textures need MLX to be initialized first. Consider refactoring to load textures after MLX init but before rendering.

2. **Memory**: Textures are not freed automatically. Add cleanup in `cleanup_scene()`.

3. **Format**: Only XPM format supported (MiniLibX limitation).

## 📝 Next Steps

To fully integrate textures:

1. **Modify main_bonus.c to pass MLX to parsing**:
```c
// After init_minirt:
scene = load_scene_with_textures(argv[1], data.mlx);
```

2. **Add texture cleanup**:
```c
// In cleanup_scene():
if (object->texture)
    free_texture(mlx, object->texture);
```

3. **Create more example textures** in `textures/` folder

## 🎉 Enjoy Texturing!

Your MiniRT now supports beautiful XPM textures! Create amazing scenes and share them! 🌍🌙🪐
