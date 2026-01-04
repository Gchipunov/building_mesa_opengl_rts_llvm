
#ifndef UDPCCLIENT_MAINMENU_UI_BUTTON1_H
#define UDPCCLIENT_MAINMENU_UI_BUTTON1_H


#include <vector>
#include <glm/glm.hpp>

#include <GL/glew.h>

#include <GLFW/glfw3.h>


//#include "Texture_Sprite_Altas_Loader.h"



class GameHUD_UI_Build_Button1
{
public:

	GameHUD_UI_Build_Button1();
	~GameHUD_UI_Build_Button1();

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



extern GameHUD_UI_Build_Button1* g_ANA_GameHUD_UI_Build_Button1;

#endif
