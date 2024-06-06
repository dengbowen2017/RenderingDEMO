# RenderingDEMO

## Outline
This is my implementation of a simple game engine with only editor mode. The main concept is to use RHI to manage different rendering APIs. For now, it can support OpenGL and DirectX11.

## How to use
For now, this engine only supports Windows. Please clone the repository, open it with Visual Studio 2022, and run the source code in Visual Studio.

## TODO list
1. Render a triangle by using DirectX and HLSL
2. Add camera system which supports 3D rendering
3. Add Phone Lighting
4. Add UI system
5. Add resource loader to load 3D model and texture
6. Add batch rendering
7. Add PBR
8. Add cross compiling

## References

### Rendering API
[LearnOpenGL](https://learnopengl.com/Getting-started/OpenGL)

[LearnD3D11](https://graphicsprogramming.github.io/learnd3d11/1-introduction/1-1-getting-started/1-1-0-overview/)

### Engine Framework
[UnrealEngine](https://github.com/folgerwang/UnrealEngine)

[Piccolo](https://github.com/BoomingTech/Piccolo)

[Hazel](https://github.com/TheCherno/Hazel)