#pragma once
#include <string>

namespace GameState
{
	extern bool menu;
	extern bool game;
	extern bool preGame;
	extern bool settings;
	extern bool inGameSettings;
	
	extern bool update;
	extern bool quit;
	extern bool loadWorld;
	extern bool firstLoad;
	extern std::string currentText;
	extern float mouseSens;
	extern bool ChangedSens;
	extern bool fullScreen;
	extern bool infinte;

	extern int chunkSize;
	extern int worldSize;
	extern std::string seed;

	void Reset();
	void Menu();
	void Game();
	void PreGame();
	void SettingsMenu();
	void Quit();
	void ChangeMouseSensitivy();
	void UpdateWorldSize();
	void SetSeed();
	void SetInfinte();
}