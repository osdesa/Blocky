#pragma once

#include "graphics/primitives/rect.h"
#include <functional>
#include <iostream>
#include "graphics/primitives/rect.h"

namespace Blocky {


	class Button : Rect
	{
	public:
		void Create(Camera& camera, Vec2 left, Vec2 right, Vec3 colour, Vec3 actionColour, Vec3 hoverColour, std::function<void()> btnCallback);
		bool CheckClick(Vec2 MousePos);
		void Draw();
		void CheckHover(Vec2 MousePos);
		void SetHover();
		void ChangeColour();
		void Reset();
		void CallCallback();
		inline uint32_t GetId() { return RGetVaoId(); }
		bool IsClicked() { return clicked; }

		Button() {};

	private:
		Vec3 defultColour;
		Vec3 ActionColour;
		Vec3 HoverColour;
		std::function<void()> callback;
		bool clicked;
	};
}