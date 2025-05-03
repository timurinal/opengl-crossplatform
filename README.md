# opengl-crossplatform
A cross-platform template for OpenGL that runs on Linux and Windows with only one CMake file<br>
The C++ files are just to show a simple quad, all you need is the `CMakeLists.txt` file that contains the specific compiler/linker setup to include the platform specific OpenGL libraries, as well as the `external` folder which contains GLFW, GLAD, and GLM.<br>
Ensure you have OpenGL installed on Linux for it to run, as the OpenGL headers are **not** natively installed on all distributions of Linux. Should work on all GPUs (tested on an NVIDIA GPU with no issues)<br>
Unlikely to work on macOS, but I have no way of testing this.
