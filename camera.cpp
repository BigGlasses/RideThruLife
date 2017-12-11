#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <camera.hpp>
#include <glm.hpp>

/*
* Written with heavy help from http://in2gpu.com/2016/03/14/opengl-fps-camera-quaternion/
*/

void Camera::updateView() {
    // temp quaternions per frame
    glm::quat keyQuat = glm::quat(glm::vec3(key_pitch, key_yaw, key_roll));
    key_pitch = key_yaw = key_roll = 0; // reset their values

    cameraQuat = keyQuat * cameraQuat;
    cameraQuat = glm::normalize(cameraQuat);
    glm::mat4 rotate = glm::mat4_cast(cameraQuat);

    glm::mat4 translate = glm::mat4(1.0f);
    translate = glm::translate(translate, -eyeVector);

    viewMatrix = rotate * translate;
}

void Camera::getViewMatrix() {
    return viewMatrix;
}

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

    glm::mat4 mat = getViewMatrix();
    glm::vec3 forward(mat[0][2], mat[1][2], mat[2][2]); //forwards and back
    glm::vec3 strafe(mat[0][0], mat[1][0], mat[2][0]); //side to side

    const float speed = 0.12f;

    eyeVector += (-dz * forward + dx * strage) * speed;

    updateView();
}

void Camera::mouseMove(int x, int y, int width, int height) {
    if (isMousePressed == false) return;

    glm::vec2 mouseDelta = glm::vec2(x, y) - mousePosition;

    const float mouseXSensitivity = 0.0020f;
    const float mouseYSensitivity = 0.0020f;

    key_yaw = mouseXSensitivity * mouseDelta.x;
    key_pitch = mouseYSensitivity * mouseDelta.y;

    mousePosition = glm::vec2(x,y);
    updateView();
}

void Camera::mousePressed(int button, int state, int x, int y) {
    if (state == GLUT_UP) {
        isMousePressed = false;
    }
    if (state == GLUT_DOWN) {
        isMousePressed = true;
        mousePosition.x = x;
        mousePosition.y = y;
    }
}
