#pragma once

#include "app.h"

#include <stdint.h>
#include "logger.h"
#include <iostream>
#include "math/BMath.h"
#include "clock.h"
#include "graphics/VertexBuffer.h"
#include "graphics/IndexBuffer.h"
#include "graphics/VertexArray.h"
#include "graphics/shader.h"
#include <graphics/renderer.h>
#include "camera.h"
#include "graphics/Texture.h"
#include "world/block.h"
#include "world/chunk.h"
#include "world/block_types.hpp"
#include "UI/UIManager.h"
#include <iostream>
#include <vector>
#include <array>
#include <cstdint>
#include <world/world.h>
#include <world/sky/sun.h>

namespace Blocky {
	class App : Renderer
	{
	private:
		Window* window{};
		const int width = 1920;
		const int height = 1080;
		const char* title = "Blocky";
		const Vec3 defultSkyColour = { 135 / 255.0f, 206 / 255.0f, 235 / 255.0f };
		const Vec3 nightSky = { 0.01, 0.01, 0.1 };

		Vec3 skyColour = defultSkyColour;
		Clock clock{};

		void SetUp();
		void CheckGamestate(Camera& camera);
		void ChangeColour(float roation);

		void InitMenuUI(Camera& cam);
		void InitPreGame(Camera& cam);
		void InitSettings(Camera& cam);
		void InitInGameUI(Camera& cam);

		void DrawWorld(Camera& cam);

		World world;
		UIManager uiManager{ (float)width, (float)height,"app/res/fonts/", "font.ttf" };


	public:
		void Start();
		App() {};
	};
}