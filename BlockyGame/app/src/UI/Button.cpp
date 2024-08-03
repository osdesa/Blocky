#include "UI/Button.h"

namespace Blocky {
	void Button::Create(Camera& camera, Vec2 left, Vec2 right, Vec3 colour, Vec3 actionColour, Vec3 hoverColour, std::function<void()> btnCallback)
	{
		// sets up the basic variables
		defultColour = colour;
		ActionColour = actionColour;
		HoverColour = hoverColour;
		callback = btnCallback;
		// creates the rectangle which is the base of a button
		RCreate(camera, left, right, colour);
	}

	bool Button::CheckClick(Vec2 MousePos)
	{
		// if the mouse is inside the button
		if(RIntersect(MousePos)){
			clicked = true;
			ChangeColour();
			return true;
		}
		else {
			clicked = false;
			return false;
		}
	}

	void Button::Draw()
	{
		// Draws the buttons rectangle
		RDraw();
	}

	void Button::CheckHover(Vec2 MousePos)
	{
		if (RIntersect(MousePos)) {
			SetHover();
		}
	}

	void Button::SetHover()
	{
		RChangeColour(HoverColour);
	}

	void Button::ChangeColour()
	{
		RChangeColour(ActionColour);
	}

	void Button::Reset()
	{
		RChangeColour(defultColour);
	}

	void Button::CallCallback()
	{
		// calls the callback method
		// this is a memory location which can be called at runtime and set at runtime
		callback();
	}
}