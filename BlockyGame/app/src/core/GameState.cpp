#include "core/GameState.h"
#include <logger.h>
#include <Windows.h>

namespace GameState
{
	extern bool menu = true;
	extern bool game = false;
	extern bool preGame = false;
	extern bool settings = false;
	extern bool inGameSettings = false;

	extern bool ChangedSens = false;
	extern std::string currentText = "";
	extern float mouseSens = 2.0f;
	extern bool quit = false;
	extern bool update = false;
	extern bool loadWorld = false;
	extern bool firstLoad = false;
	extern bool fullScreen = false;
	extern bool infinte = true;

	extern int chunkSize = 6;
	extern int worldSize = chunkSize * chunkSize;
	extern std::string seed = "";

	void Reset()
	{
		menu = false;
		game = false;
		preGame = false;
		settings = false;
		inGameSettings = false;
	}

	void Menu()
	{
		Reset();
		menu = true;
		update = true;
	}

	void SettingsMenu()
	{
		Reset();
		update = true;
		settings = true;
	}

	void Quit()
	{
		Reset();
		quit = true;
		update = true;
	}

	void ChangeMouseSensitivy()
	{
		ChangedSens = true;
		mouseSens = (float)std::stof(currentText);
	}

	void UpdateWorldSize()
	{
		if (currentText.size() == 0) return;
		for (char c : currentText) {
			if ((c < 48) || (c  > 57)) {
				Logger::output(INFO, "Char %c", c);
				MessageBox(nullptr, TEXT("World size must be interger"), TEXT("ERROR"), MB_OK);
				return;
			}
		}
	
		int size = stoi(currentText);
		if (size % 2 == 1) size++;
		chunkSize = size;
		worldSize = size * size;
	}

	void SetSeed()
	{
		seed = currentText;
	}

	void SetInfinte()
	{
		infinte = !infinte;
	}

	void PreGame()
	{
		Reset();
		preGame = true;
		update = true;
	}

	void Game()
	{
		Reset();
		if (loadWorld == false) {
			loadWorld = true;
			firstLoad = true;
		}
		else {
			firstLoad = false;
		}
		game = true;
		update = true;
	}
}