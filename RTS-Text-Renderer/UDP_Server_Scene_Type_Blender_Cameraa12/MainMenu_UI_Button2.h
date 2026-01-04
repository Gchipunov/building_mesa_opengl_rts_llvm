
#ifndef UDPCCLIENT_MAINMENU_UI_BUTTON2_H
#define UDPCCLIENT_MAINMENU_UI_BUTTON2_H


#include <vector>
#include <glm/glm.hpp>

#include <GL/glew.h>

#include <GLFW/glfw3.h>


class MainMenuUIButton2
{
public:

	MainMenuUIButton2();
	~MainMenuUIButton2();

	int CreateMainMenuQuads();

	void UpdateMainMenu();


	void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);


	int iMainMenuUI_MainVertices_index;

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



extern MainMenuUIButton2* g_ANA_MainMenuUIButton2;

#endif
