# carpet

Small C++ game engine using SFML and OpenGL.

## Running

You will need the DLLs for SFML 2.4.2 in a `lib` directory. The project also makes use of a compiled object file for GLEW, built from the glew.c source file.
If you choose, you can instead modify the Makefile to use a DLL.

The object files are set to be built in an `obj` folder, so you'll need to create one.

Once you have these files and folders, you can run a make command within the root directory. 
Please note that the Makefile contains Windows-specific commands in the `clean` task.

