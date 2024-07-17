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
- basic forward rendering
- phong lighting
- simple shadow mapping

## TODO list
- Add basic editor (including ECS and UI)
- Add smiple scripting system (C#)
- Add smiple resource loader and asset manager
- Add smiple scene manager
- Add batch rendering
- Add simple 3D physics
- Add rendering features (PBR, Deferred Rendering...)
- Add multi-thread (logic thread and render thread)
- Add cross compiling (cmake presets)

## References
### Rendering API
[LearnOpenGL](https://learnopengl.com/Getting-started/OpenGL)

[LearnD3D11](https://graphicsprogramming.github.io/learnd3d11/1-introduction/1-1-getting-started/1-1-0-overview/)
### Engine Framework
[UnrealEngine](https://github.com/folgerwang/UnrealEngine)

[Piccolo](https://github.com/BoomingTech/Piccolo)

[Hazel](https://github.com/TheCherno/Hazel)