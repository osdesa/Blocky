#include "app.h"
#include <thread>
#include <UI/Font.h>
#include <UI/Button.h>
#include <functional>
#include <iostream>
#include "core/GameState.h"

namespace Blocky {
	// sets up the callback for openGL errors
	void GLAPIENTRY errorMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
		const GLchar* message, const void* userParam)
	{
		// if the message is an error display error to the console
		if (type == GL_DEBUG_TYPE_ERROR)
			Logger::output(VALIDATION, "OpenGL error");
	}

	void App::Start()
	{
		// sets up the window and the graphics handle
		SetUp();

		// Creates the camera with the size of the screen
	 	Camera camera(window, &clock, width, height);

		// sets up the ui handler
		uiManager.Init(camera);
	
		// sets up the menu ui
		InitMenuUI(camera);
		Logger::output(KEYINFO, "-----------Main start loop------------");

		// main game loop
		while (!glfwWindowShouldClose(window->window))
		{
			// sets up logic for new frames
			clock.NewFrame();
			Clear(skyColour);

			// updates all the UI elements
			uiManager.Update();
			// checks to see what has changed in the global state
			CheckGamestate(camera);

			// Draws all the UI
			uiManager.RendererUI();

			// Checks if the esc key is down or the game is set to quit
			if (Input::isKeyDown(GLFW_KEY_ESCAPE) || GameState::quit == true) {
				window->Close();
			}

			// Checks if the C key is down
			if (Input::isKeyDown(GLFW_KEY_C)) {
				// removes all the text from the terminal
				system("cls");
			}
			// Sets no key to be active
			Input::currentKey = NULL;
			
			// clears display
			NewFrame(window);
		}
		Logger::output(KEYINFO, "-------------Main loop end------------");

		Logger::output(INFO, "Closing program gracefully");
		// clears window and then deletes
		Window::FreeWindow(window);
		// stops the program
		glfwTerminate();
	}

	/// <summary>
	/// Draws every chunk in the world
	///
	/// </summary>
	/// <param name="cam"></param>
	void App::DrawWorld(Camera& cam)
	{
		world.Draw(cam, clock);
	}

	void App::SetUp()
	{
		// sets up the window manager
		glfwInit();
		// Creates a new window handle with given parameters
		window = Window::CreateWindow(width, height, title, GameState::fullScreen);

		// if the window failed to create
		if (window == nullptr) {
			Logger::output(FATAL, "Failed to create window");
		}
		// if the window created well
		else {
			Logger::output(KEYINFO, "Create window");
		}
		// sets up input callbacks to handle when a key is pressed
		window->InstallMainCallback();

		// sets up openGL bindings
		// if it fails write that it failed
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			Logger::output(FATAL, "failed to init GLAD");
		}

		else {
			Logger::output(KEYINFO, "Glad initilzed");
		}

		// enables callbacks which handles what to do when an error is found in the graphics side
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(errorMessageCallback, 0);
		// sets up the viewport to the size of the screen
		glViewport(0, 0, width, height);

		// Enables blending which is the art of allowing Transparency
		glEnable(GL_BLEND);
		// sets the Transparency function to the defult
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// sets up the depth test which makes the gpu check how far every pixel is from the camera's eye
		glEnable(GL_DEPTH_TEST);

		// starts the clock
		clock.Start();
	}


	/// <summary>
	/// Method which handles the checking of the global gamestate
	/// redraws the FPS every time it is ran
	/// checks if buttons have been click or are hoverd over
	/// handles UI changes such as changing scence
	/// </summary>
	/// <param name="camera"></param>
	void App::CheckGamestate(Camera& camera)
	{
		// resets the sky colour
		skyColour = defultSkyColour;

		// Sets up the fps text
		std::string text = std::string("FPS : ") + std::to_string(clock.GetFPS());
		uiManager.AddText(text, 10.0f, height - 70.0f, 0.75f, Vec3(0), true);

		// checks if the mouse is currently over any buttons
		uiManager.CheckHover({ Input::mouseX, Input::mouseY });

		// checks to see if the user has changed the sensitivty in game
		if (GameState::ChangedSens) {
			camera.ChangeSens(GameState::mouseSens);
			GameState::ChangedSens = false;
		}
		// Checks to see if the user is trying to go to the menu
		if (GameState::menu && GameState::update) {
			uiManager.ClearUI();
			InitMenuUI(camera);
		}
		// checks to see if the user is trying to go to the settings menu
		if (GameState::settings && GameState::update) {
			uiManager.ClearUI();
			InitSettings(camera);
		}
		// Checks to see if the user is going to the pregame screen
		if (GameState::preGame && GameState::update) {
			uiManager.ClearUI();
			InitPreGame(camera);
		}
		// Checks to see if the player is trying to start the game and if the world has been loaded before
		if (GameState::game && GameState::loadWorld && GameState::firstLoad) {
			// Generates the world as set by the players requirments
			world.CreateWorld(camera);
			// Draws the world
			DrawWorld(camera);
			// sets the world to be loaded
			GameState::firstLoad = false;
			// clears the UI
			uiManager.ClearUI();
			// sets up in game UI
			InitInGameUI(camera);
		}
		// if the user is in the game and is not the first load
		if (GameState::game) {
			Vec3 pos = camera.GetPosition();
			text = std::string("POS: ") + std::to_string(pos.x) + ", " + std::to_string(pos.y) +  ", " + std::to_string(pos.z);
			uiManager.AddText(text, 10.0f, height - 140.0f, 0.5f, Vec3(0), true);

			// if the user holds down tab their mouse should be freed
			if (Input::isKeyDown(GLFW_KEY_TAB)) {
				glfwSetInputMode(window->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
			else {
				glfwSetInputMode(window->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				world.update(camera, clock);
			}
			// gets the rotation of the sun
			float roatation = world.GetRotation();
			// updates the colour of the sky
			ChangeColour(roatation);
			// Draws the world
			DrawWorld(camera);
		}
		// sets the update flag to false
		GameState::update = false;
	}

	void App::ChangeColour(float roation)
	{
		// Gets the sun lighting posistion using a translated cos graph
		roation = (cos(roation) + 2.5) / 4;
		// gets the percetage change of blue which is the highest colour value
		float percentageChange = 1 / skyColour.z;
		// gets the change in green
		float deltaGreen = skyColour.y * percentageChange * roation;
		// Gets the change in red
		float deltaRed = skyColour.x * percentageChange * roation;
		// sets the colour to the new colour correct sky colour
		skyColour = Vec3(deltaRed, deltaGreen, skyColour.z * roation);
	}

	void App::InitMenuUI(Camera& cam)
	{
		// Adds the title text
		uiManager.AddText("Blocky", height - 50.0f, 1.0f, Vec3(0.7, 0.1, 0.1), false);
		// Adds the play button
		uiManager.AddButton(cam, "Play Game", 800, 1.0f, Vec3(0), false, { -300, 550 }, { 300, 700 }, &GameState::PreGame);
		// Adds the settings button
		uiManager.AddButton(cam, "Settings", 800, 1.0f, Vec3(0), false, { -300, 350 }, { 300, 500 }, &GameState::SettingsMenu);
		// Adds the close button
		uiManager.AddButton(cam, "Close Game", 800, 1.0f, Vec3(0), false, { -300, 150 }, { 300, 300 }, &GameState::Quit);
	}

	void App::InitPreGame(Camera& cam)
	{
		// Adds the title text
		uiManager.AddText("Blocky", height - 50.0f, 1.0f, Vec3(0.7, 0.1, 0.1), false);
		// Adds the input box which lets the user enter values
		uiManager.AddInputBox(cam, { (width / 2) - 300.0f,600 }, { (width / 2) + 300.0f,700 }, { 0.6,0.6,0.6 }, { 0.4,0.4,0.4 });
		// Adds the button which reads from the input box and sets the world seed
		uiManager.AddButton(cam, "Set seed", 800, 1.0f, Vec3(0), false, { -200, 450 }, { 200, 550 }, &GameState::SetSeed);
		// Adds the button which reads from the input box and sets the world size
		uiManager.AddButton(cam, "Set world size", 800, 1.0f, Vec3(0), false, { -200, 340 }, { 200, 440 }, &GameState::UpdateWorldSize);
		// Adds the toggle button allowing the user to make the world infite or finite
		uiManager.AddButton(cam, "Infinte", 800, 1.0f, Vec3(0), false, { -150, 250 }, { 150, 330 }, &GameState::SetInfinte);
		// Adds the start button which will create the world
		uiManager.AddButton(cam, "Start", 800, 1.0f, Vec3(0), false, { -300, 750 }, { 300, 900 }, &GameState::Game);
		// Adds the back button which allows the user to go back to the main menu
		uiManager.AddButton(cam, "Back", 800, 1.0f, Vec3(0), false, { -300, 50 }, { 300, 200 }, &GameState::Menu);
	}

	void App::InitSettings(Camera& cam)
	{
		// Adds the title text
		uiManager.AddText("Blocky", height - 50.0f, 1.0f, Vec3(0.7, 0.1, 0.1), false);
		// Adds the button which allows the user to go back to the menu
		uiManager.AddButton(cam, "Menu", 800, 1.0f, Vec3(0), false, { -300, 150 }, { 300, 300 }, &GameState::Menu);
		// Displays info text
		uiManager.AddText("Enter Mouse sensitivity", 500.0f, 520.0f, 0.75f, Vec3(0.1, 0.1, 0.1), false);
		// Adds input box which allows user to enter values
		uiManager.AddInputBox(cam, { 500,400 }, { 1100,500 }, { 0.6,0.6,0.6 }, { 0.4,0.4,0.4 });
		// Takes current input and sets that as the current mouse sensitivty
		uiManager.AddButton(cam, "Save", 800, 1.0f, Vec3(0), false, { 200, 400 }, { 350, 500 }, &GameState::ChangeMouseSensitivy, { 0.6 }, { 0.5 }, { 0.4 }, true);
	}

	void App::InitInGameUI(Camera& cam)
	{
		// Adds the crosshair at the center of the screen
		uiManager.AddRectTextured(cam, { (width / 2) - 16.0f, (height / 2) - 16.0f }, { (width / 2) + 16.0f, (height / 2) + 16.0f }, { 0.5,0.5,0.5 }, "crosshair.png");
	}
}