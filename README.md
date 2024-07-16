# RenderingDEMO

## Outline
This is my implementation of a simple game engine. The main concept is to use RHI to manage different rendering APIs. For now, it can support OpenGL and DirectX11.

## How to use
After cloning the repository
### Windows
#### Method 1
Open the root folder with Visual Studio and run the cmake file 
#### Method 2
```
$ cd RenderingDEMO
$ mkdir build
$ cd build
$ cmake ..
```
Then run the .sln file.

## Finished 
- basic RHI 
- basic 3D rendering camera system
- basic render pass
- phong lighting
- simple shadow mapping

## TODO list
- Add editor (including ECS and UI)
- Add scene manager
- Add batch rendering
- Add PBR
- Add cross compiling

## References
### Rendering API
[LearnOpenGL](https://learnopengl.com/Getting-started/OpenGL)

[LearnD3D11](https://graphicsprogramming.github.io/learnd3d11/1-introduction/1-1-getting-started/1-1-0-overview/)
### Engine Framework
[UnrealEngine](https://github.com/folgerwang/UnrealEngine)

[Piccolo](https://github.com/BoomingTech/Piccolo)

[Hazel](https://github.com/TheCherno/Hazel)