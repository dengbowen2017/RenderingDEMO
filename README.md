# RenderingDEMO

## Outline
This is my implementation of a simple game engine. The main concept is to use RHI to manage different rendering APIs. For now, it can support OpenGL and DirectX11 only on Windows.
![preview](Imgs/preview.png)

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
- skybox

## TODO list
### Priority
- 3D graphics math library
- Add smiple resource loader
- Add simple 3D rigid body physics
- Add rendering features (PBR, Deferred Rendering...)
- Add batch rendering

### In the future
- Add smiple scene manager
- Add basic editor (including ECS and UI)
- Add smiple scripting system (C#)
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