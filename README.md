# BallsSimulation
A simple simulation of balls insteraction. Can be used for an ideal gas, or billard balls simulations. 

## Installation instructions:
```
git clone https://github.com/akalinow/BallsSimulation.git
cd BallsSimulation
mkdir build; cd build
cmake ../
make install -j 4
```

Alternative version with command line compilation:
```
cd BallsSimulation
mkdir build; cd build
g++ -Wall -O3 -std=c++14 -DWITHOUT_NUMPY -I/usr/include/python2.7/ -lpython2.7 -I../include/ ../src/*.cpp ../bin/main.cpp -o mySimulation
```

## Running intructions:
Application recognises a number of command line options:
- -nStep - integer number of time steps to simulate
- -nBalls - integer number of balls to simulate
- -input - source of balls. "random" - means random initial position and speed.
- -dt - time step, in range ]0,1[

Run command:

```
./mySimulation -nSteps 250 -nBalls 2 -input random -dt -0.01
```

Program creates a set of frames merged at the end into a gif animation "animation.gif".
The animation can be displayed in browser, just type URL (replace "directory" with correct path)
to the file.

```
file://directory/animation.gif
```

