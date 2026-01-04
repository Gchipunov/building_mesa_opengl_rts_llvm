
#ifndef UDPCCLIENT_MAINMENU_UI_BUTTON4_H
#define UDPCCLIENT_MAINMENU_UI_BUTTON4_H


#include <vector>
#include <glm/glm.hpp>

#include <GL/glew.h>

#include <GLFW/glfw3.h>


class GameHUD_UI_Build_Button4
{
public:

	GameHUD_UI_Build_Button4();
	~GameHUD_UI_Build_Button4();

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
	int SpriteID_Icon = 2;
	int BuildPercentage = 50;



};



extern GameHUD_UI_Build_Button4* g_ANA_GameHUD_UI_Build_Button4;

#endif
