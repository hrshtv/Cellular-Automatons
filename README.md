<h1 align="center"> Cellular Automatons </h1>

<p align="middle">
  <img src="demo/brians_brain.gif" width="32%"></img>
  <img src="demo/conway.gif" width="32%"></img>
  <img src="demo/wireworld.gif" width="32%"></img>
</p>

[Brian's World](https://en.wikipedia.org/wiki/Brian%27s_Brain), [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life), and [Wireworld](https://en.wikipedia.org/wiki/Wireworld) have been implemented.  

## Usage:

```
cd src
bash run.sh <filename>
```

## Documentation:

src/  
- Helpers.h : Contains a few trivial helper functions 
- cells/  
  - BrianCell.h : Implementation of the Brian's Brain cell
  - Cell.h : Abstract class that describes the nature of a cell in a cellular automaton
  - ConwayCell.h : Implementation of the Conway's Game of Life's cell
  - WireworldCell.h : Implementation of Wireworld's cell
- configs/  
  - Circuit.h : Stores the state information for the circuit shown in the [GIF](demos/wireworld.gif)
  - Config.h : Abstract class that stores a particular configuration of the world
  - Gosper.h : Stores the state information for Gosper's Glider Gun
- main_bb.cpp : Main script for Brian's Brain
- main_cgol.cpp : Main script for Conway's Game of Life
- main_ww.cpp : Main script for Wireworld
- run.sh : Compiles and runs a FLTK program 
- worlds/  
  - BrianWorld.h : Implementation of Brian's Brain
  - ConwayWorld.h : Implementation of the Conway's Game of Life
  - WireworldWorld.h : Implementation of Wireworld
