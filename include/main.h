#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h> // OpenGL Graphics Utility Library
#include <iostream>
#include <stdbool.h>
#include <thread>

#include "player.h"
#include "server.h"
#include "client.h"

// These variables set the dimensions of the rectanglar region we wish to view.
const double Xmin = 0, Xmax = 1024;
const double Ymin = 0, Ymax = 256;

#define DeltaY 32