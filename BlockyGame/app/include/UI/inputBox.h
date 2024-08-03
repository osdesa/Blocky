#pragma once
#include <math/vector.h>
#include <graphics/primitives/rect.h>

namespace Blocky {
	class InputBox : Rect
	{
	public:
		InputBox() {};

		void Create(Camera& camera, Vec2 left, Vec2 right, Vec3 colour, Vec3 actionColour, uint32_t i_id);
		bool CheckClick(Vec2 mousePos);
		void Draw();
		void SetAction();

		inline uint32_t GetVao() { return RGetVaoId(); }
		inline uint32_t GetId() { return id; }
		inline void Reset() { RChangeColour(defultColour); }
		bool GetReset();

	private:
		Vec3 defultColour;
		Vec3 ActionColour;
		std::string text;
		uint32_t id;
		bool reset = true;
	};
}