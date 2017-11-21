#ifndef __QUICKGL_H__	//guard against cyclic dependancy
#define __QUICKGL_H__

#define GLEW_STATIC
#ifdef __APPLE__
#  include "include/GL/glew.h"
#  include <GLUT/glut.h>
#else
#  include "include/GL/glew.h"
#  include <GL/freeglut.h>
#endif

#endif