#pragma once

#include "math/BMath.h"
#include <camera.h>
#include <graphics/renderer.h>
#include <graphics/Texture.h>

namespace Blocky {
	class CelestialModel : Renderer
	{
	public:
		virtual void Create(Camera& camera);
		void Draw(Camera& cam, float DT);
		float GetRotation() { return angle; }

	protected:
		VertexArray va;
		VertexBuffer vb;
		IndexBuffer ib;
		Texture texture;
		Shader shader;
		Vec3 posistion;

		float size = 1;
		double angle = 0.0f;
		float scaleFactor = 75.0f;
		int distance = 4000;
		float offset = 0.0001f;

		float rect[40] = {
			size,size,size,1,1,
			size,size,-size,0,1,
			-size,size,-size,0,0,
			-size,size,size,0,1,
			size + offset,-size + offset,size + offset,    1,1,
			-size + offset,-size + offset,size + offset, 0,1,
			-size + offset,-size + offset,-size + offset,0,0,
			size + offset,-size + offset,-size + offset, 0,1,
		};

		uint32_t indices[12] = {
			0,1,2,2,3,0,
			4,5,6,6,7,4
		};
	};
}