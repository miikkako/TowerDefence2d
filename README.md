# DEFEND!
A tower defence game using a game engine suitable for simple 2D games.  
The sources in `engine/src/` are combined to the sources found in `src` to create a single binary  
NOTE: This project is as private project on my school's Gitlab server, hence the weird push intervals.  

## Build
Into the project folder:  
1. `cmake .`  
2. `make && ./td`  

Into a separate folder:  
1. `mkdir build && cd build`  
2. `cmake ..`  
3. `make && ./td`  

## Game instructions
The game is on development phase, so for now keyboard commands can be read
from engine/src/usereventhandler.cpp AND src/tdusereventhandler.cpp.  

### About coding style
* using "this->" in methods that are not defined inside the class itself, but inside the classes that The class inherits


