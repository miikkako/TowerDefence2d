# DEFEND!
A tower defence game in development.  

## Build
This project utilises CMake to generate the Makefiles. The project is dependent on SFML libraries, version > 2.4 (https://www.sfml-dev.org).

### Installing SFML
__Option 1__: Install SFML libraries to your computer by using your favourite package installer.  

__Option 2 (Recommended)__: Build SFML from source:  
1. Clone the SFML repository into your preferred place: `git clone https://github.com/SFML/SFML.git`
2. Make your preferred build folder where you want the SFML build files to go and go inside that directory.
3. Pick a build option:
    * Static optimized libraries (Recommended): `cmake -DCMAKE_CXX_FLAGS="-stdlib=libc++" -DCMAKE_C_FLAGS="-stdlib=libc++" -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=FALSE -DSFML_USE_STATIC_STD_LIBS=TRUE path/to/sfml_root`
    * Dynamic optimized libraries: `cmake -DCMAKE_CXX_FLAGS="-stdlib=libc++" -DCMAKE_C_FLAGS="-stdlib=libc++" -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=TRUE path/to/sfml_root`
    * Dynamic debug libraries: `cmake -DCMAKE_CXX_FLAGS="-stdlib=libc++" -DCMAKE_C_FLAGS="-stdlib=libc++" -DCMAKE_BUILD_TYPE=Debug path/to/sfml_root`
4. Build targets: `sfml-audio sfml-graphics sfml-network sfml-system sfml-window`. If using GNU make: `make sfml-audio sfml-graphics sfml-network sfml-system sfml-window`.
5. Optional: `make install`. This installs the resulted libraries and headers into a well-known location (see below for explanation) so that the SFML repository and the build files can be removed safely because they are no longer needed to run the libraries. Removing the build files: `make clean`.

Finally build the project into a separate folder (Out-of-sourc, recommended):  
1. Clone the SFML repository into your preferred place: `git clone https://github.com/miikkako/TowerDefence2d.git`
2. Make your preferred build directory where you want the project build files to go and go inside that directory.
3. Pick a build option: (If SFML libraries are not located in a standard path, use `-DSFML_ROOT="path/to/sfml_libraries;path/to/sfml_root"`, where "sfml_libraries" is the directory where the built libraries lie in, and "sfml_root" is the directory where the "include"-directory with the headers lie in.) 
    * Static optimized binary linked with static SFML libraries (Recommended): `cmake -DCMAKE_BUILD_TYPE=Release -DSFML_STATIC_LIBRARIES=TRUE path/to/project_root`
    * Static optimized binary linked with dynamic SFML libraries: `cmake -DCMAKE_BUILD_TYPE=Release path/to/project_root`
    * Debug binary linked with static SFML libraries: `cmake -DCMAKE_BUILD_TYPE=Debug -DSFML_STATIC_LIBRARIES=TRUE path/to/project_root`
    * Debug binary linked with dynamic SFML libraries: `cmake -DCMAKE_BUILD_TYPE=Debug path/to/project_root`
4. Build the target binary: `make`
5. Run the binary program: `./2dgame`  


## CMake notes:
cmake can be invoked with:
* `-DCMAKE_C_COMPILER` and `-DCMAKE_CXX_COMPILER` can be used to control the selected compiler.
* `-G"build platform"` can be used to control the build platform, e.g. `-G"NMake Makefiles"` or `-G"MinGW Makefiles"`.
* `-DCMAKE_INSTALL_PREFIX=path/to/install_prefix` can be used to control where the build system is going to install the resulted targets if the install command is executed: e.g. Makefile system `make install` (the default install prefix is a path most typical for the current operating system, e.g. "/usr/local" or "C:\Program Files", so this parameter rarely needs to be touched). 
* `-DCMAKE_MODULE_PATH=path/to/cmake_module_path` can be used to control where the "findSFML.cmake" script used by the project's CMakeLists.txt lies in (Default is the one located in the project's "cmake_modules"-directory).


## Nice to know
The sources in `engine/src/` are combined to the sources found in `src` to create a single binary.  


