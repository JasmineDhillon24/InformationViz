# InformationViz
Various information visualization tools
## Scatterplot Matrix
![Image of Scatterplot Matrix](ScatterplotMatrix/SPLOM.png)
## Parallel Coordinates
![Image of Parallel Coordinates](ParallelCoords/ParallelCoords.png)
## Hybrid Parallel Coordinates
![Image of Hybrid Parallel Coordinates](ParallelCoordsHybrid/ParallelCoordsHybrid.png)
## Slice View
![Image of Slice 1](SliceView/Slice_1.png)
![Image of Slice 2](SliceView/Slice_2.png)
## Isosurface
![Image of Isosurface](Isosurface/Isosurface1.png)
![Image of Isosurface](Isosurface/Isosurface2.png)
## Transfer Function
![Image of Transfer Function](TransferFunction/TransferFunction.png)
## Vectors
![Image of Vector Field](Vector/Vector.png)
## Dependency
1. Openframeworks https://github.com/openframeworks/openFrameworks
2. VTK http://www.vtk.org/download/
## Build
```
cd <viz>
mkdir build
cd build
cmake ../CMakeLists.txt
cd ..
make
```
Example:
```
cd ScatterPlot
mkdir build
cd build
cmake ../CMakeLists.txt
cd ..
make
```
## Run
```
cd <viz>
./bin/<viz>
```
Example:
```
cd ScatterPlot
./bin/ScatterPlot
```
