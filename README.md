# RenderingDEMO

## Outline
This is my implementation of a simple game engine. For now, it can support OpenGL and DirectX11 only on Windows.

![preview](doc/preview.png)

## How to use
First, clone the repository
```
git clone https://github.com/dengbowen2017/RenderingDEMO.git path_to_your_folder --recursive
```
### Windows
#### Method 1
Open the root folder with Visual Studio and run the cmake file 
#### Method 2
```
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
- 3D graphics math library
- Add smiple resource loader
- Add simple 3D rigid body physics

## Notice
### Physics Engine

Simulation normally contains four stages.

BoardPhase -> NarrowPhase -> ResolvePhase -> Intergration

For now, the part is just a very simple one and need to be reconstructed in the future. No good collision detection, No good intergration with other system, Only supports one rigid body.

## TODO list
### Priority
- Add PBD physics simulation
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
[Learn OpenGL](https://learnopengl.com/Getting-started/OpenGL)

[Learn D3D11](https://graphicsprogramming.github.io/learnd3d11/1-introduction/1-1-getting-started/1-1-0-overview/)
### Game Engine Framework
[Unreal Engine](https://github.com/folgerwang/UnrealEngine)

[Piccolo](https://github.com/BoomingTech/Piccolo)

[Hazel](https://github.com/TheCherno/Hazel)
### Physics Engine Framework
[Jolt Physics](https://github.com/jrouwe/JoltPhysics)