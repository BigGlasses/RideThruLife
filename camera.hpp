#ifndef __CAMERA_H__	//guard against cyclic dependancy
#define __CAMERA_H__ //written with help of LectureCode1 from avenue

//http://in2gpu.com/2016/03/14/opengl-fps-camera-quaternion/

class Camera {
    public:    
        void updateView();
        // float** getViewMatrix();
        void keyPressed(const unsigned char);
        void mouseMove(int, int, int, int);
        void mousePressed(int, int, int, int);
        void normalize();

        float viewMatrix[4][4];

    private:
        float eyeVector[3];
        float cameraQuat[4];
        float mousePosition[2];
        float key_pitch;
        float key_yaw;
        float key_roll;
        bool isMousePressed;
};
#endif