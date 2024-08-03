#pragma once

#include "logger.h"
#include "math/BMath.h"
#include "core/window.h"
#include "core/input.h"
#include "clock.h"
#include <core/aabb.h>

namespace Blocky {

    class Camera
    {
    public:
        Camera() = default;

        Camera(Window* win, Clock* _clock, int w_Width, int w_Height);
        Matrix4x4 Look();
        void Move(float deltaTime);
        void SetPos(Vec3 pos) { CameraPos = pos; }

        inline void ChangeSens(float sens) { sensitivity = sens; }
        inline float GetFOV() { return fov; }
        inline void ResetMove() { CameraPos = tempPos; View = Look(); }
        inline AABB GetAABB() { return aabb; }
        void Update(float dt);

        Vec3 GetPosition() { return CameraPos; }
        Vec3 GetLastPosition() { return lastPos; }

        Matrix4x4 GetModel() { return Model; }
        Matrix4x4 GetProjection() { return Projection; }
        Matrix4x4 GetView() { return View; }
        Matrix4x4 GetTextProjection() { return textProjection; }

    private:
        Window* window;
        Clock* clock;

        void UpdateAABB();

        int width;
        int height;

        Matrix4x4 Model;
        Matrix4x4 View;
        Matrix4x4 Projection;
        Matrix4x4 textProjection;

        Vec3 CameraPos;
        Vec3 lastPos;
        Vec3 cameraTarget;
        Vec3 CameraDirection;
        Vec3 CameraFront;
        Vec3 Up;
        Vec3 CameraRight;
        Vec3 CameraUp;
        Vec3 Direction;
        Vec3 tempPos;

        Vec3 Min;
        Vec3 Max;
        AABB aabb;

        float lastX = 1920 / 2;
        float lastY = 1080 / 2;
        const float cameraSpeed = 5.0f;
        float sensitivity = 0.20f;
        const float defultFov = 90.0f;
        float fov = 90.0f;
        float yaw = -90.0f;
        float pitch = 0.0f;

        float near = 0.001f;
        float far = 100.0f;
        float right = 1920.0f;
        float left = 0.0f;
        float top = 1920.0f;
        float bottom = 0.0f;

        uint32_t startX = 16 * 16;
        uint32_t startZ = 16 * 16;
    };
}