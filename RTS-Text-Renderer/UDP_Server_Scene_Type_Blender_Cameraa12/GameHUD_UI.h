
#ifndef UDPCCLIENT_GAMEHUD_UI_H
#define UDPCCLIENT_GAMEHUD_UI_H


#include <vector>
#include <glm/glm.hpp>

#include <GL/glew.h>

#include <GLFW/glfw3.h>


#include "ANA_GameState.h"

#include "GameHUD_UI_Build_Button1.h"
#include "GameHUD_UI_Build_Button2.h"
#include "GameHUD_UI_Build_Button3.h"
#include "GameHUD_UI_Build_Button4.h"

class GameHUDUI
{
public:

	GameHUDUI();
	~GameHUDUI();

	int CreateMainMenuQuads();

	void UpdateMainMenu();


	void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);


	int iGameHUDUI_MainVertices_index;

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



extern GameHUDUI* g_ANA_GameHUDUI;

#endif