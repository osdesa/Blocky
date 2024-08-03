#include "UI/inputBox.h"

namespace Blocky {
	void InputBox::Create(Camera& camera, Vec2 left, Vec2 right, Vec3 colour, Vec3 actionColour, uint32_t i_id)
	{
		defultColour = colour;
		ActionColour = actionColour;
		id = i_id;
		// Creates the basic rectangle
		RCreate(camera, left, right, colour);
	}

	bool InputBox::CheckClick(Vec2 mousePos)
	{
		// Checks if inside the rectangle
		if (RIntersect(mousePos)) {
			SetAction();
			return true;
		}
	}

	void InputBox::Draw()
	{
		RDraw();
	}

	void InputBox::SetAction()
	{
		RChangeColour(ActionColour);
	}

	bool InputBox::GetReset()
	{
		// if the input box has nt been writen into
		if (reset) {
			reset = false;
			return true;
		}
		return false;
	}
}