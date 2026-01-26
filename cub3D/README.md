# cub3D

*This project has been created as part of the 42 curriculum by viceda-s.*

## Description

**cub3D** is a 3D graphical representation project inspired by the legendary Wolfenstein 3D game, the first-ever First-Person Shooter (FPS). This project uses raycasting techniques to render a 3D maze environment from a 2D map perspective.

The goal is to create a dynamic view inside a maze where the player can navigate using the keyboard, with textured walls, floor and ceiling colors, and proper collision detection. The bonus version extends the mandatory features with additional gameplay elements including interactive doors, animated sprites, weapon system, and mouse controls.

### Key Features

**Mandatory:**
- First-person 3D maze navigation using raycasting
- Textured walls with different textures for each cardinal direction (North, South, East, West)
- Customizable floor and ceiling colors
- Smooth player movement (W, A, S, D keys) and rotation (arrow keys)
- Collision detection with walls
- Window management (minimize, close, ESC key)

**Bonus:**
- Wall collision effects
- Minimap display
- Interactive doors that can be opened/closed
- Animated sprites and enemies
- Weapon system with shooting mechanics
- Mouse-based camera rotation
- Enhanced visual effects

## Instructions

### Prerequisites

- GCC compiler
- Make
- X11 development libraries (Linux)
- Linux operating system

### Compilation

To compile the mandatory part:
```bash
make
```

To compile the bonus part:
```bash
make bonus
```

To clean object files:
```bash
make clean
```

To clean everything (objects and executables):
```bash
make fclean
```

To recompile:
```bash
make re
```

### Execution

**Mandatory version:**
```bash
./cub3D maps/test.cub
```

**Bonus version:**
```bash
./cub3D_bonus maps/test_bonus.cub
```

### Map File Format

The program accepts `.cub` map files with the following format:

```
NO ./assets/textures/north_texture.xpm
SO ./assets/textures/south_texture.xpm
WE ./assets/textures/west_texture.xpm
EA ./assets/textures/east_texture.xpm

F 220,100,0
C 225,30,0

111111
100001
1000N1
100001
111111
```

- `NO`, `SO`, `WE`, `EA`: Texture paths for each wall direction
- `F`: Floor color in RGB format (R,G,B)
- `C`: Ceiling color in RGB format (R,G,B)
- Map characters:
  - `0`: Empty space (walkable)
  - `1`: Wall
  - `N/S/E/W`: Player starting position and orientation
  - `D`: Door (bonus)

### Controls

**Mandatory:**
- `W`, `A`, `S`, `D`: Move forward, left, backward, right
- `←`, `→`: Rotate camera left/right
- `ESC`: Exit the game

**Bonus:**
- Mouse movement: Rotate camera
- `E`: Interact with doors
- `Left Click`: Shoot weapon
- All mandatory controls

## Resources

### Documentation & Tutorials
- [Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html) - Comprehensive raycasting tutorial
- [Ray-Casting Tutorial For Game Development](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/) - Classic raycasting guide
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) - 42 graphics library documentation
- [Wolfenstein 3D Wikipedia](https://en.wikipedia.org/wiki/Wolfenstein_3D) - Historical context
- [42 Docs - cub3D](https://harm-smits.github.io/42docs/projects/cub3d) - Project-specific guidance

### Technical References
- Digital Differential Analysis (DDA) algorithm for raycasting
- Bresenham's line algorithm concepts
- Texture mapping in raycasting
- X11/XShm graphics programming

### AI Usage

AI tools were used in the following capacities during this project:

- **Code structure planning**: Assistance in organizing the project architecture and module separation
- **Algorithm explanation**: Understanding complex raycasting mathematics and DDA implementation
- **Debugging support**: Help identifying and resolving memory leaks, segmentation faults, and rendering issues
- **Documentation**: Assistance in writing clear code comments and this README file
- **Error handling**: Suggestions for robust input validation and error management strategies

**Note**: All core algorithms, raycasting logic, and game mechanics were implemented manually with AI serving as a supplementary learning and debugging resource. The fundamental understanding and implementation of raycasting, texture mapping, and game loop architecture were developed through independent study and practice.

## Project Structure

```
cub3D/
├── src/              # Mandatory source files
│   ├── core/         # Core game initialization and cleanup
│   ├── parsing/      # Map and configuration parsing
│   ├── player/       # Player movement and rotation
│   ├── raycasting/   # Raycasting algorithm implementation
│   └── render/       # Rendering and drawing functions
├── bonus/            # Bonus features implementation
│   └── src_bonus/    # Extended functionality
├── inc/              # Header files
├── lib/              # External libraries (libft, minilibx)
├── maps/             # Example map files
├── assets/           # Textures and sprites
└── Makefile          # Build configuration
```

## Author

**viceda-s** - [42 Network Profile](https://profile.intra.42.fr/users/viceda-s)

---

*This project is part of the 42 Common Core curriculum and demonstrates understanding of graphics programming, mathematical algorithms, and game development fundamentals.*
