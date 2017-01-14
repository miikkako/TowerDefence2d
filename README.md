# DEFEND!
A tower defence game using a game engine suitable for simple 2D games.  
The sources in `engine/src/` are combined to the sources found in `src` to create a single binary  

## Build
Into the project folder:  
1. `cmake .`
2. `make && ./td`

Into a separate folder:  
1. `mkdir build && cd build`  
2. `cmake ..`
3. `make && ./td`


### About coding style
* using "this->" in methods that are not defined inside the class itself, but inside the classes that The class inherits