#include "camera.h"
#include "logger.h"
#include "defines.h"
#include <iostream>

namespace Blocky {
    Camera::Camera(Window* win, Clock* _clock, int w_Width, int w_Height)
        : window(win), clock(_clock), width(w_Width), height(w_Height)
    {
        // writes to the logger that the camera has started
        Logger::output(KEYINFO, "Camera Init");
        // Sets the position of the camera
        CameraPos = Vec3(startX, WATERLEVEL + 30.0f, startZ);
        lastPos = CameraPos;
        // sets the camera target to the center of the screen
        cameraTarget = Vec3(0.0f, 0.0f, 0.0f);
        // sets up collisions
        UpdateAABB();
        // sets where the camera front is
        CameraFront = Vec3(0.0f, 0.0f, -1.0f);
        // Sets the cameras up direction
        Up = Vec3(0.0f, 1.0f, 0.0f);
        // Sets the cameras up direction for later use
        CameraUp = Vec3(0.0f, 1.0f, 0.0f);

        // Creates the projection matrix which will be used for all 3d things
        Projection = Matrix::Perspective(DEG_TO_RAD(fov), (float)width / (float)height, 0.001f, 1000.0f);
        // Creates the orhograpthic matrix which will be used for all 2d things
        textProjection = Matrix::Orthographic(0.0f, (float)width, 0.0f, (float)height);
        // Sets up the model matrix
        Model = Matrix4x4();
        // Sets up the view matrix
        View = Matrix::LookAt(CameraPos, CameraPos + CameraFront, CameraUp);
    }

    Matrix4x4 Camera::Look()
    {
        // Calulates which direction the player is looking
        Vec3 forward = CameraPos + CameraFront;
        // Returns where the player is looking
        return Matrix::LookAt(CameraPos, forward, CameraUp);
    }

    void Camera::Update(float dt)
    {
        lastPos = CameraPos;
        // moves the player
        Move(dt);
        // Updates the view matrix
        View = Look();
    }

    void Camera::UpdateAABB()
    {
        // sets the min to be a vec3 where all values are 0.3 less than the posistion
        Min = CameraPos - 0.3;
        // sets the min to be a vec3 where all values are 0.3 more than the posistion
        Max = CameraPos + 0.3;
        // updates the colision box
        aabb.Update(Min, Max);
    }

    void Camera::Move(float deltaTime)
    {
        // makes sets the camera speed which has the frame rate acounted for
        float cameraSpeed = 20.0f * deltaTime;
        tempPos = CameraPos;

        if (Input::isKeyDown('W')) {
            // sets the movement forward
            Vec3 temp = CameraFront * cameraSpeed;
            // updates the position
            CameraPos = CameraPos + temp;
        }
        if (Input::isKeyDown('S')) {
            // sets the movement forward
            Vec3 temp = CameraFront * cameraSpeed;
            // updates the position

            CameraPos = CameraPos - temp;
        }
        if (Input::isKeyDown('A')) {
            // Gets the vector which is perpendicular to the front and and the vertical
            Vec3 temp = Vector::CrossProduct(CameraFront, CameraUp);
            // normilise the direction vector
            temp = Vector::Normilise(temp);
            // updates the position
            CameraPos = CameraPos - (temp * cameraSpeed);
        }
        if (Input::isKeyDown('D')) {
            // Gets the vector which is perpendicular to the front and and the vertical
            Vec3 temp = Vector::CrossProduct(CameraFront, CameraUp);
            // normilise the direction vector
            temp = Vector::Normilise(temp);
            // updates the position
            CameraPos = CameraPos + (temp * cameraSpeed);
        }
        // check if movement was valid
        UpdateAABB();

        // Gets the direction in which the mouse has moved on the x axis
        float xoffset = Input::mouseX - lastX;
        // Gets the direction in which the mouse has moved on the y axis
        float yoffset = lastY - Input::mouseY;

        // Sets the last directions
        lastX = Input::mouseX;
        lastY = Input::mouseY;

        xoffset *= sensitivity;
        yoffset *= sensitivity;

        // adds to horizontal based on the direction of the mouse
        yaw += xoffset * sensitivity;
        // adds to vertical based on the direction of the mouse
        pitch += yoffset * sensitivity;

        // limits the pitch to be in the rand -89 to 89
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        // Calulates the front where the mouse is based on math
        Vec3 Front = Vec3(
            cos(DEG_TO_RAD(yaw)) * cos(DEG_TO_RAD(pitch)),
            sin(DEG_TO_RAD(pitch)),
            sin(DEG_TO_RAD(yaw)) * cos(DEG_TO_RAD(pitch))
        );
        // sets the front as a normlised vector giving the correct direcition
        CameraFront = Vector::Normilise(Front);

        // code bellow increases accuracy as distance from 0,0,0 increases
        Vec3 temp = Vector::CrossProduct(Front, Up);
        CameraRight = Vector::Normilise(temp);
        temp = Vector::CrossProduct(CameraRight, Front);
        Up = Vector::Normilise(temp);
    }
}