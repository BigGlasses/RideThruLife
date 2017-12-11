#ifndef __CAMERA_H__	//guard against cyclic dependancy
#define __CAMERA_H__ //written with help of LectureCode1 from avenue

#include "glm/glm.hpp"

//http://in2gpu.com/2016/03/14/opengl-fps-camera-quaternion/

class Camera {
    public:    
        void Camera::updateView();
        glm::mat4 Camera::getViewMatrix();
        void Camera::keyPressed(const unsigned char);
        void Camera::mouseMove(int, int, int, int);
        void Camera::mousePressed(int, int, int, int);

    private:
        glm::vec3 eyeVector;
        glm::mat4 viewMatrix;
        glm::quat cameraQuat;
        glm::vec2 mousePosition;
        float key_pitch;
        float key_yaw;
        float key_roll;
        bool isMousePressed;
};
#endif