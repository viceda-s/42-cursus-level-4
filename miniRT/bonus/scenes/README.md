# 🎨 MiniRT Scene Collection

## 📁 Available Scenes

### 🌟 **texture_showcase.rt**
**Complex showcase with all features**
- Multiple textured objects (Earth spheres)
- Checkerboard patterns on various shapes
- Bump mapping demonstrations
- Multiple light sources
- Perfect for showing off all capabilities

```bash
./miniRT scenes/texture_showcase.rt
```

---

### 🌍 **simple_texture.rt**
**Beginner-friendly texture demo**
- Single textured Earth sphere
- Checkerboard floor
- Simple lighting
- Great for testing basic texture functionality

```bash
./miniRT scenes/simple_texture.rt
```

---

### ♟️ **checkerboard_gallery.rt**
**Checkerboard pattern showcase**
- Multiple spheres with different colored checkerboards
- Checkerboard cylinders in various orientations
- Checkerboard cubes
- Demonstrates checker pattern on all object types

```bash
./miniRT scenes/checkerboard_gallery.rt
```

---

### 🎭 **mixed_features.rt**
**Combined feature demonstration**
- Textures + Checkerboard + Bump mapping
- Multiple light sources (warm/cool/rim lighting)
- Organized layout showing each feature
- Best for comparing different surface treatments

```bash
./miniRT scenes/mixed_features.rt
```

---

### 🧱 **material_showcase.rt**
**All XPM texture materials**
- Earth texture (blue/green planet)
- Brick texture (brown/orange bricks)
- Wood texture (natural wood grain)
- Metal texture (shiny metallic surface)
- Grass texture (green grass field)
- Includes checkerboard comparisons

```bash
./miniRT scenes/material_showcase.rt
```

---

## 🎨 Available Textures

All textures are located in `textures/` directory:

| Texture | File | Description |
|---------|------|-------------|
| 🌍 Earth | `earth.xpm` | Blue/green planet texture |
| 🧱 Brick | `brick.xpm` | Brown brick wall pattern |
| 🪵 Wood | `wood.xpm` | Natural wood grain |
| ⚙️ Metal | `metal.xpm` | Shiny metallic surface |
| 🌿 Grass | `grass.xpm` | Green grass field |

---

## 🎮 Controls

| Key | Action |
|-----|--------|
| `ESC` | Exit program |
| `F` | Toggle Fast Render (for Valgrind) |
| `W/A/S/D` | Move camera forward/left/back/right |
| `Q/E` | Move camera up/down |
| `↑/↓/←/→` | Rotate camera |
| `I/J/K/L/U/O` | Move light source |
| `TAB` | Select next object |
| `Numpad 2/4/6/8` | Move selected object |
| `Numpad 7/9` | Rotate selected object |

---

## 📝 Scene File Format

### Basic Structure
```
A ambient_ratio R,G,B
C x,y,z orientation_x,orientation_y,orientation_z fov
L x,y,z brightness R,G,B
```

### Objects with Features

**Sphere:**
```
sp x,y,z diameter R,G,B [options]
```

**Plane:**
```
pl x,y,z normal_x,normal_y,normal_z R,G,B [options]
```

**Cylinder:**
```
cy x,y,z axis_x,axis_y,axis_z diameter height R,G,B [options]
```

**Cube:**
```
cu x,y,z side_length R,G,B [options]
```

### Available Options

- **Texture:** `tx:path/to/texture.xpm`
- **Checkerboard:** `ck`
- **Bump Mapping:** `bm:strength,scale_u,scale_v`

### Examples

```
# Textured Earth sphere
sp 0,0,0 10 100,150,255 tx:textures/earth.xpm

# Checkerboard floor
pl 0,-5,0 0,1,0 200,200,200 ck

# Bumpy metal cylinder
cy 0,0,0 0,1,0 5 10 180,180,200 bm:1.5,2.0,2.0

# Brick cube with texture
cu 5,5,5 4 150,100,80 tx:textures/brick.xpm
```

---

## 🚀 Quick Start

1. **Compile:**
   ```bash
   cd bonus
   make re
   ```

2. **Run a scene:**
   ```bash
   ./miniRT scenes/texture_showcase.rt
   ```

3. **Test with Valgrind (use Fast Render):**
   ```bash
   valgrind --leak-check=full ./miniRT scenes/simple_texture.rt
   # Press 'F' immediately after window opens
   ```

4. **Create your own scene:**
   ```bash
   cp scenes/simple_texture.rt scenes/my_scene.rt
   # Edit my_scene.rt with your favorite editor
   ./miniRT scenes/my_scene.rt
   ```

---

## 💡 Tips

- **Performance:** Press `F` to toggle fast render mode (disables anti-aliasing)
- **Debugging:** Use `simple_texture.rt` for quick tests
- **Learning:** Study `material_showcase.rt` to see all texture types
- **Showcasing:** Run `texture_showcase.rt` or `mixed_features.rt` for impressive results

---

## 🎯 Scene Complexity Ranking

1. ⭐ **simple_texture.rt** - Easiest, fastest to render
2. ⭐⭐ **checkerboard_gallery.rt** - Medium, good for pattern testing
3. ⭐⭐⭐ **material_showcase.rt** - Medium-complex, all textures
4. ⭐⭐⭐⭐ **mixed_features.rt** - Complex, combined features
5. ⭐⭐⭐⭐⭐ **texture_showcase.rt** - Most complex, ultimate showcase

---

**Happy Rendering! 🎨**
