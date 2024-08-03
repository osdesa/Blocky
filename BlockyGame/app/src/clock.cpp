#include "clock.h"
#include "logger.h"

namespace Blocky {
    void Clock::Start()
    {
        // logs that the clock has started
        Logger::output(KEYINFO, "Clock started");
        // sets the start time 
        startTime = std::chrono::system_clock::now();
        frameStart = std::chrono::high_resolution_clock::now();
    }

    void Clock::NewFrame()
    {
        // increase the frame counter
        frameCount++;
        // gets the current time
        auto currentTime = std::chrono::high_resolution_clock::now();
        // Gets the differance in time between the current time and frame start time
        deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - frameStart).count();
        // Gets the current time
        frameStart = std::chrono::high_resolution_clock::now();

        // if 60 frames have passed update the FPS variable
        if (frameCount % 60 == 0)
            FPS = (int)(1.0f / deltaTime);
#if SHOWFPS
        Logger::output(INFO, "FPS: %d", FPS);
#endif
    }
}