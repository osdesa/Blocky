#pragma once
#include <graphics/shader.h>
#include <graphics/VBLayout.h>
#include <graphics/VertexBuffer.h>
#include <graphics/VertexArray.h>
#include <graphics/IndexBuffer.h>
#include <camera.h>
#include <graphics/renderer.h>
#include <graphics/Texture.h>

namespace Blocky {
	class Rect : Renderer {
	public:
		void RCreate(Camera& camera, Vec2 left, Vec2 right, Vec3 colour);
		void RCreateTextured(Camera& camera, Vec2 left, Vec2 right, Vec3 colour, std::string fileName);
		void RDraw();
		void RChangeColour(Vec3 colour);
		bool RIntersect(Vec2 pos);

		inline Vec2 RGetTop() { return rightTop; }
		inline Vec2 RGetBottom() { return leftBottom; }
		inline uint32_t RGetVaoId() { return va.GetId(); }


		Rect() {};


	protected:
		VertexArray va;
		VertexBuffer vb;
		IndexBuffer ib;
		VBLayout layout{};
		Shader shader;
		Texture texture;

		Vec2 leftBottom;
		Vec2 rightTop;

		uint32_t indices[6] = { 0,1,2,2,3,0 };
	};
}