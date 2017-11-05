# Extended Kalman Filter Project Starter Code

Udacity Self-Driving Car Engineer Nanodegree Program

## Overview

I utilized an extended Kalman filter with C++ to estiamte the position and velocity of moving an object of interest with lidar and radar measurements.
The repository have files to install [uWebSocketIO](https://github.com/uWebSockets/uWebSockets) for the communication between the simulator and EFK in either Linux or Mac systems.

## Dependancies

* cmake >= 3.5
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
* gcc/g++ >= 5.4

Tips for detail prerequisite can be found [here](./README_Original.md)

## Build Instructions

1. mkdir build
2. cd build
3. cmake ..
4. make
5. ./ExtendedKF

## Outputs
[//]: # (Image References)

[image1]: ./Output/Output_DataSet_1.png "Dataset 1"
[image2]: ./Output/Output_DataSet_2.png "Dataset 2"

![alt text][image1]
![alt text][image2]

## Rubrics

### Compiling

#### You should compile.
Yes. It works with ```cmake``` and ```make``` as mentioned in the "Build Instruction".

### Accuracy

#### px, py, vx, vy output coordinates must have an RMSE <= [.11, .11, 0.52, 0.52] when using the file: "obj_pose-laser-radar-synthetic-input.txt which is the same data file the simulator uses for Dataset 1"
The results of RMSE are
* Dataset 1: [0.0973, 0.0855, 0.4499, 0.4411]
* Dataset 2: [0.0727, 0.0964, 0.4313, 0.5266]


### Following the Correct Algorithm

#### Your Sensor Fusion algorithm follows the general processing flow as taught in the preceding lessons.
The code mainly follows the sensor fusions and Kalman filter algorithms with the codes in ```../src```

#### Your Kalman Filter algorithm handles the first measurements appropriately.
The initialization step for the state vectors and covariance matrices are applied in[FusionEKF.cpp](../src/FusionEKF.cpp) from line 58 to 112.

#### Your Kalman Filter algorithm first predicts then updates.
The prections step are at [FusionEKF.cpp](../src/FusionEKF.cpp) from line 114 to 155 and the updates are placed at the same file from line 157 to 192.

#### Your Kalman Filter can handle radar and lidar measurements.
Different scheme are utilized in the first measurements (from line 73 to 111) and updates steps (from line 157 to 192) in [FusionEKF.cpp](../src/FusionEKF.cpp).  

