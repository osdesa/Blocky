#include "UI/UIManager.h"

namespace Blocky {
	UIManager::UIManager(float winWidth, float winHeight, std::string dir, std::string font)
		: width(winWidth), height(winHeight), midWidth(winWidth / 2), midHeight(winHeight / 2), directory(dir), fontName(font)
	{
		buttonClickedId = -1;
	}

	void UIManager::Init(Camera& camera)
	{
		// Creates the text handler
		textHandler.Create(directory, fontName);
		// sets the projection
		textHandler.SetProjection(camera);
	}

	void UIManager::ClearUI()
	{
		// resets the amount of UI elements
		btnCount = 0;
		inputBoxCount = 0;
		rectCount = 0;
		for (int i = 0; i < buttons.size(); i++) {
			// creates empty button
			Button btn = Button();
			// moves this button into the array
			buttons[i] = std::move(btn);
		}
		for (int i = 0; i < rects.size(); i++) {
			// creates rect
			Rect rect = Rect();
			// moves this rect into the array

			rects[i] = std::move(rect);
		}
		for (int i = 0; i < inputBoxs.size(); i++) {
			// creates input box
			InputBox ib = InputBox();
			// moves this button into the array
			inputBoxs[i] = std::move(ib);
		}
		// clears all the text
		textHandler.Clear();
	}

	void UIManager::RendererUI()
	{
		DrawRects();
		DrawButtons();
		RenderInput();
		DrawText();
	}

	void UIManager::Update()
	{
		// if there is an active button
		if (buttonClickedId != -1) {
			// calls the buttons callback
			buttons[buttonClickedId].CallCallback();
			// makes the active button null
			buttonClickedId = -1;
		}
		// checks to see if left mouse button is clicked
		if (Input::isMouseButtonDown(GLFW_MOUSE_BUTTON_1)) {
			// if the click happens when it can
			if (ValidClick())
				bool click = CheckClicked({ Input::mouseX, Input::mouseY });
		}
		if (Input::isMouseButtonDown(GLFW_MOUSE_BUTTON_1) == false) {
			// resets the mouse down 
			SetValidClick();
			ResetAll();
		}
		// if the user is typing into and input box
		if ((typeText) && (Input::currentKey != NULL)) {
			bool reset = false;
			for (int i = 0; i < inputBoxs.size(); i++) {
				// if the input box exists
				if (inputBoxs[i].GetVao() != 0) {
					// if the id of the input box is the same as the selected
					if (selectedId == inputBoxs[i].GetId()) {
						// check if the box should be reset
						reset = inputBoxs[i].GetReset();
					}
				}
			}
			// update all the text
			textHandler.Update(selectedId, Input::currentKey, reset);
		}
	}

	void UIManager::AddRect(Camera& camera, Vec2 left, Vec2 right, Vec3 colour)
	{
		Rect rect;
		// Creates a rectangle
		rect.RCreate(camera, left, right, colour);
		// adds it array of rectangles
		rects[rectCount] = std::move(rect);
		rectCount++;
	}

	void UIManager::AddRectTextured(Camera& camera, Vec2 left, Vec2 right, Vec3 colour, std::string name)
	{
		// Creates texture rectangle
		Rect rect;
		rect.RCreateTextured(camera, left, right, colour, name);
		// adds it to the array of rectangles
		rects[rectCount] = std::move(rect);
		rectCount++;
	}

	void UIManager::DrawRects()
	{
		// Draws all the rectangles
		for (int i = 0; i < rects.size(); i++) {
			if (rects[i].RGetVaoId() != 0)
				rects[i].RDraw();
		}
	}

	void UIManager::AddInputBox(Camera& camera, Vec2 left, Vec2 right, Vec3 colour, Vec3 actionColour)
	{
		// increment the number of input boxs
		maxId++;
		// gets where to center the box on the y axis
		float y = (left.y + right.y - 48) / 2;
		// Gets where to center the box on the x axis
		float x = ((left.x + right.x) / 2) - ((right.x - left.x) / 2) + 5;
		// Adds the text at the center of the input box
		textHandler.AddText("Enter text", x, y, 1.0f, { 0.1 }, false, maxId);

		// Creates the inputbox
		InputBox box;
		box.Create(camera, left, right, colour, actionColour, maxId);
		// Move the input box into the array of input boxs
		inputBoxs[inputBoxCount] = std::move(box);
		inputBoxCount++;
	}

	void UIManager::RenderInput()
	{
		// Renderers all input boxs
		for (int i = 0; i < inputBoxs.size(); i++) {
			if (inputBoxs[i].GetVao() != 0)
				inputBoxs[i].Draw();
		}
	}

	void UIManager::CheckClick(Vec2 mousePos)
	{
		bool found = false;
		// loop through every input box
		for (int i = 0; i < inputBoxs.size(); i++) {
			// if the input box exits
			if (inputBoxs[i].GetVao() != 0) {
				// reset them
				inputBoxs[i].Reset();
				bool click = inputBoxs[i].CheckClick({ mousePos.x, height - mousePos.y });
				if (click) {
					// set the currently selected input box as the found input box
					found = true;
					typeText = true;
					selectedId = inputBoxs[i].GetId();
				}
			}
		}
		if (!found) {
			typeText = false;
		}
	}

	void UIManager::AddText(char c)
	{
	}

	void UIManager::AddText(std::string text, float x, float y, float scale, Vec3 color, bool clear)
	{
		// adds text and increments the id
		maxId++;
		textHandler.AddText(text, x, y, scale, color, clear, maxId);
	}

	void UIManager::AddText(std::string text, float y, float scale, Vec3 color, bool clear)
	{
		// Addes text but also centers on the x axis
		maxId++;
		float x = midWidth - ((textHandler.GetTextSize(text, scale) / 2));
		textHandler.AddText(text, x, y, scale, color, clear, maxId);
	}

	void UIManager::DrawText()
	{
		// Draws all the text on the screen
		textHandler.RenderText();
	}

	void UIManager::AddButton(Camera& camera, std::string text, float x, float scale, Vec3 textColour, bool clear,
		Vec2 left, Vec2 right, std::function<void()> btnCallback, Vec3 BackgroundColour, Vec3 actionColour, Vec3 hoverColour, bool centerd)
	{
		// increments the number of text elements
		maxId++;
		// Center the text in the middle of the button y axis
		float y = ((left.y + right.y) / 2) - 24;

		// if the button should be centerd on the x axis
		if (centerd) {
			left.x = midWidth + left.x;
			right.x = midWidth + right.x;
		}
		// Set x axis placement accounting for the size of the text
		x = ((left.x + right.x) / 2) - ((textHandler.GetTextSize(text, scale) / 2));

		// Creates the button
		Button btn;
		btn.Create(camera, left, right, BackgroundColour, actionColour, hoverColour, btnCallback);
		// move button to the array
		buttons[btnCount] = std::move(btn);
		btnCount++;

		// adds the text to the text handler
		textHandler.AddText(text, x, y, scale, textColour, clear, maxId);
	}

	bool UIManager::CheckClicked(Vec2 mousePos)
	{
		CheckClick(mousePos);
		buttonClickedId = -1;
		for (int i = 0; i < buttons.size(); i++) {
			// checks to see if the button being index has been clicked
			bool clicked = buttons[i].CheckClick({ mousePos.x, height - mousePos.y });
			if (clicked) {
				buttonClickedId = i;
				validClick = false;
				return true;
			}
		}
		return false;
	}

	void UIManager::CheckHover(Vec2 mousePos)
	{
		// checks if the mouse is over a button
		for (int i = 0; i < buttons.size(); i++) {
			buttons[i].CheckHover({ mousePos.x, height - mousePos.y });
		}
	}

	void UIManager::DrawButtons()
	{
		// loops through all the buttons
		for (int i = 0; i < buttons.size(); i++) {
			if (buttons[i].GetId() != 0)
				buttons[i].Draw();
		}
	}

	void UIManager::ResetAll()
	{
		for (int i = 0; i < buttons.size(); i++) {
			if (buttons[i].GetId() != 0)
				buttons[i].Reset();
		}
	}
}