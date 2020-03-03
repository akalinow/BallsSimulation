# BallsSimulation
A simple simulation of balls insteraction. Can be used for an ideal gas, or billard balls simulations. 

## Installation instructions:
```
git clone https://github.com/akalinow/BallsSimulation.git
cd BallsSimulation
mkdir build; cd build
cmake ../
make install -j 4
./mySimulation
```

Alternative version with command line compilation:
```
cd BallsSimulation
mkdir build; cd build

```


Program creates a set of frames merged at the end into a gif animation "animation.gif".
The animation can be displayed in browser, just type URL (replace "directory" with correct path
to the file.

```
file://directory/animation.gif
```
