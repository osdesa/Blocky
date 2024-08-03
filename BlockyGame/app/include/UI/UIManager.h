#pragma once

#include "Button.h"
#include "Font.h"
#include "inputBox.h"

namespace Blocky {
	class UIManager
	{
	private:
		std::array<Button, 10> buttons;
		std::array<Rect, 10> rects;
		std::array<InputBox, 10> inputBoxs;
		uint8_t btnCount = 0;
		uint8_t rectCount = 0;
		uint8_t inputBoxCount = 0;

		std::string directory;
		std::string fontName;

		uint32_t maxId;

		int buttonClickedId;
		float width;
		float height;
		float midWidth;
		float midHeight;
		bool validClick;
		bool clicked;
		uint32_t selectedId;
		bool typeText;

	public:
		UIManager() {};
		UIManager(float winWidth, float winHeight, std::string dir, std::string font);
		UIManager(const UIManager&) = delete;
		UIManager& operator=(const UIManager&) = delete;

		Font textHandler{};

		void Init(Camera& camera);
		void ClearUI();
		void RendererUI();
		void Update();

		inline bool ValidClick() { return validClick; }
		inline void SetValidClick() { validClick = true; }

		// Rects
		void AddRect(Camera& camera, Vec2 left, Vec2 right, Vec3 colour);
		void AddRectTextured(Camera& camera, Vec2 left, Vec2 right, Vec3 colour, std::string name);
		void DrawRects();

		// Input Box
		void AddInputBox(Camera& camera, Vec2 left, Vec2 right, Vec3 colour, Vec3 actionColour);
		void RenderInput();
		void CheckClick(Vec2 mousePos);
		void AddText(char c);

		//text
		void AddText(std::string text, float x, float y, float scale, Vec3 color, bool clear);
		void AddText(std::string text, float y, float scale, Vec3 color, bool clear);
		void DrawText();

		// Button
		void AddButton(Camera& camera, std::string text, float x, float scale, Vec3 textColour, bool clear,
			Vec2 left, Vec2 right, std::function<void()> btnCallback, Vec3 BackgroundColour = { 0.5,0.5,0.5 }, Vec3 actionColour = { 0.8,0.2,0.2 }, Vec3 hoverColour = { 0.4,0.4,0.4 }, bool centerd = true);
		bool CheckClicked(Vec2 mousePos);
		void CheckHover(Vec2 mousePos);
		void DrawButtons();
		void ResetAll();
	};
}