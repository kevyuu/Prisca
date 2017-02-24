@echo off

set additinalLibPath=/LIBPATH:..\external\lib
set externallib=opengl32.lib user32.lib gdi32.lib kernel32.lib shell32.lib glfw3.lib glew32s.lib SOIL.lib
set cppfiles=..\demo\main.cpp
set includedir=/I..\external\include
set outputfile=prisca_demo
rmdir /S /Q build
mkdir bin

pushd bin

cl /Zi %cppfiles% %includedir% /MD %externallib% /Fe%outputfile% /link %additinalLibPath% /NODEFAULTLIB:libcmt.lib 
prisca_demo.exe

popd