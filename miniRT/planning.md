You're absolutely right! Here's the corrected order:
MiniRT Implementation Plan
Phase 1: Project Setup & Display

Set up project structure

Create Makefile with MLX42 library
Organize folders: /src, /include, /scenes
Define main data structures


MLX integration

Initialize window
Create image buffer
Test pixel writing with simple pattern
Handle window close events



Phase 2: Parsing

Implement .rt file parser

Parse ambient lighting (A), camera (C), light (L)
Parse sphere (sp), plane (pl), cylinder (cy)
Add error handling



Phase 3: Math Foundation

Vector operations library

Vector arithmetic, normalization, dot/cross products


Ray generation

Define ray structure (origin + direction)
Implement camera ray generation per pixel



Phase 4: Intersection Algorithms

Ray-object intersections

Sphere (quadratic equation)
Plane (dot product)
Cylinder (quadratic + caps)



Phase 5: Lighting & Rendering

Normal calculation for each object type
Phong illumination model

Ambient, diffuse, specular components
Shadow rays to light source


Core raytracer loop

Cast rays, find intersections, calculate lighting
Write to MLX image buffer



Phase 6: Testing & Bonus

Debug with simple scenes, add bonus features if desired
