#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include "camera.hpp"
#include <math.h>

/*
* Written with heavy help from http://in2gpu.com/2016/03/14/opengl-fps-camera-quaternion/
*/

void Camera::normalize() {
    float w, x, y, z;
    w = cameraQuat[0];
    x = cameraQuat[1];
    y = cameraQuat[2];
    z = cameraQuat[3];

    float length = sqrt(w*w + x*x + y*y + z*z);
    cameraQuat[0] = w/length;
    cameraQuat[1] = x/length;
    cameraQuat[2] = y/length;
    cameraQuat[3] = z/length;
}

void Camera::updateView() {
    // temp quaternions per frame
    float keyQuat[4] = {1, key_pitch, key_yaw, key_roll};
    key_pitch = key_yaw = key_roll = 0; // reset their values

    // cameraQuat = keyQuat * cameraQuat;
    // multiply two quaternions together
    float a = keyQuat[0]*cameraQuat[0] - keyQuat[1]*cameraQuat[1] - keyQuat[2]*cameraQuat[2] - keyQuat[3]*cameraQuat[3];
    float b = keyQuat[1]*cameraQuat[0] + keyQuat[0]*cameraQuat[1] - keyQuat[3]*cameraQuat[2] + keyQuat[2]*cameraQuat[3];
    float c = keyQuat[2]*cameraQuat[0] + keyQuat[3]*cameraQuat[1] + keyQuat[0]*cameraQuat[2] - keyQuat[1]*cameraQuat[3];
    float d = keyQuat[3]*cameraQuat[0] - keyQuat[2]*cameraQuat[1] + keyQuat[1]*cameraQuat[2] + keyQuat[0]*cameraQuat[3];

    cameraQuat[0] = a;
    cameraQuat[1] = b;
    cameraQuat[2] = c;
    cameraQuat[3] = d;

    //normalize the camera quaternion
    normalize();

    // glm::mat4 rotate = glm::mat4_cast(cameraQuat);
    float rotate[4][4] = {
        {cameraQuat[0], -cameraQuat[1], -cameraQuat[2], -cameraQuat[3]},
        {cameraQuat[1], cameraQuat[0], -cameraQuat[3], cameraQuat[2]},
        {cameraQuat[2], cameraQuat[3], cameraQuat[0], -cameraQuat[1]},
        {cameraQuat[3], -cameraQuat[2], cameraQuat[1], cameraQuat[0]}
    };

    // glm::mat4 translate = glm::mat4(1.0f);
    // translate = glm::translate(translate, -eyeVector);
    float translate[4][4] = {
        {1.0f, 0, 0, -eyeVector[0]},
        {0, 1.0f, 0, -eyeVector[1]},
        {0, 0, 1.0f, -eyeVector[2]},
        {0, 0, 0, 1.0f}
    };

    // viewMatrix = rotate * translate;
    // viewMatrix[0][0] = rotate[0][0]*translate[0][0] + rotate[0][1]*translate[1][0] + rotate[0][2]*translate[2][0] + rotate[0][3]*translate[3][0];
    // viewMatrix[0][1] = rotate[0][0]*translate[0][1] + rotate[0][1]*translate[1][1] + rotate[0][2]*translate[2][1] + rotate[0][3]*translate[3][1];

    for(int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            viewMatrix[i][j] = rotate[i][j]*translate[i][j] + rotate[i][j]*translate[j][i] + rotate[i][j]*translate[j][i] + rotate[i][j]*translate[j][i];
        }
    }
}

// float** Camera::getViewMatrix() {
//     return viewMatrix;
// }

void Camera::keyPressed(const unsigned char key) {
    float dx = 0;
    float dz = 0;
    switch (key) {
        case 'w': {
            dz = 2;
            break;
        }
        case 's': {
            dz = -2;
            break;
        }
        case 'a': {
            dx = -2;
            break;
        }
        case 'd': {
            dx = 2;
            break;
        }
        default:
            break;
    }

    // float mat[4][4] = viewMatrix;
    float forward[3] = {viewMatrix[0][2], viewMatrix[1][2], viewMatrix[2][2]}; //forwards and back
    float strafe[3] = {viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]}; //side to side

    const float speed = 0.12f;

    // eyeVector += (-dz * forward + dx * strafe) * speed;
    eyeVector[0] += (-dz*forward[0] + dx*strafe[0])*speed;
    eyeVector[1] += (-dz*forward[1] + dx*strafe[1])*speed;
    eyeVector[2] += (-dz*forward[2] + dx*strafe[2])*speed;

    updateView();
}

void Camera::mouseMove(int x, int y, int width, int height) {
    if (isMousePressed == false) return;

    float mouseDelta[2];
    mouseDelta[0] =  x - mousePosition[0];
    mouseDelta[1] = y - mousePosition[1];

    const float mouseXSensitivity = 0.0020f;
    const float mouseYSensitivity = 0.0020f;

    key_yaw = mouseXSensitivity * mouseDelta[0];
    key_pitch = mouseYSensitivity * mouseDelta[1];

    mousePosition[0] = x;
    mousePosition[1] = y;
    updateView();
}

void Camera::mousePressed(int button, int state, int x, int y) {
    if (state == GLUT_UP) {
        isMousePressed = false;
    }
    if (state == GLUT_DOWN) {
        isMousePressed = true;
        mousePosition[0] = x;
        mousePosition[1] = y;
    }

}