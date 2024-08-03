#pragma once

#include <chrono>

namespace Blocky {

	class Clock
	{
	private:
		std::chrono::system_clock::time_point startTime;
		std::chrono::high_resolution_clock::time_point frameStart;
		float deltaTime = 0;
		int FPS = 0;
		float frameTime = 0;
		long frameCount = 0;


	public:
		void Start();
		void NewFrame();

		inline float DT() { return deltaTime; };
		inline int GetFPS() { return FPS; };
		inline float GetFameTime() { return frameTime; };
	};
}