
#ifndef UDPCCLIENT_MAINMENU_UI_H
#define UDPCCLIENT_MAINMENU_UI_H


#include <vector>
#include <glm/glm.hpp>

#include <GL/glew.h>

#include <GLFW/glfw3.h>


class MainMenuUI
{
public:

	MainMenuUI();
	~MainMenuUI();

	int CreateMainMenuQuads();

	void UpdateMainMenu();


	void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);


	int iMainMenuUI_MainVertices_index;

	float StartXButton1; // =
	float StartYButton1; // =
	// board face collision detection , for physics
	// https://developer.nvidia.com/gpugems/gpugems3/part-v-physics-simulation/chapter-32-broad-phase-collision-detection-cuda
	float EndXButton1; // =
	float EndYButton1; // =

	float StartXButton2; // =
	float StartYButton2; // =
	float EndXButton2; // =
	float EndYButton2; // =

	float StartXButton3; // =
	float StartYButton3; // =
	float EndXButton3; // =
	float EndYButton3; // =

	float StartXButton4; // =
	float StartYButton4; // =
	float EndXButton4; // =
	float EndYButton4; // =


	// New Game      - Campaign
	// Multiplayer   - Coop, 1v1, ..
	// Options
	// Exit/Quit

	// UserProfile
	// WorkshopGame
	// WorkshopUGC
	// Chatroom
	// ProfileView - Other User profile
	// Leaderboard - Hall of Fame

	// Skills 
	// Constract
	// Achievement
	// Daily Crates
	// Daily Rewards




};



extern MainMenuUI* g_ANA_MainMenuUI;

#endif