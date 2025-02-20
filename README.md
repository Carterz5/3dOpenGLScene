# 3D OpenGL Scene Example

A 3d scene created using C and opengl. Demonstrates motion of 3d objects, skyboxes, instancing, and billboarding.

Features:

- Camera movement using WASD and Mouse
- Spinning pyramid object
- Textured skybox using cubemap
- Billboarded grass to always face camera
- Instanced grass objects to improve performance
- Wind simulation to create swaying grass

![](https://github.com/Carterz5/3dOpenGLScene/blob/main/demonstration.gif)




Compilation instructions

* Ubuntu (24.04)
```
sudo apt install build-essential
sudo apt install libglew-dev
sudo apt install libglfw3
sudo apt install libglfw3-dev
sudo apt install libcglm-dev
git clone https://github.com/Carterz5/3dOpenGLScene.git

cd 3dOpenGLScene
make

```

* Windows

install MSYS2 https://www.msys2.org/
```
pacman -S mingw-w64-ucrt-x86_64-gcc
pacman -S mingw-w64-ucrt-x86_64-glew
pacman -S mingw-w64-ucrt-x86_64-glfw
pacman -S mingw-w64-ucrt-x86_64-cglm
pacman -S make
pacman -S git

git clone https://github.com/Carterz5/3dOpenGLScene.git

cd 3dOpenGLScene


make
```
