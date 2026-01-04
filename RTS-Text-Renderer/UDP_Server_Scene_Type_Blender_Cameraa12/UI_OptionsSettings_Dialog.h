#ifndef BASE_UI_OPTIONS_SETTINGS_DIALOG_CLASS_H
#define BASE_UI_OPTIONS_SETTINGS_DIALOG_CLASS_H


#ifdef WIN32
#pragma once
#endif


#include <vector>
#include <glm/glm.hpp>

#include <GL/glew.h>

#include <GLFW/glfw3.h>


#include "ANA_GameState.h"
#include "Cursor_UI_Draw.h"

class UI_OptionsSettings_Dialog
{
public:

	UI_OptionsSettings_Dialog();
	~UI_OptionsSettings_Dialog();

	int CreateMainMenuQuads();

	void UpdateMainMenu();


	void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);


	int iUI_OptionsSettings_Dialog_MainVertices_index;
	int m_iNumberOfDrawQuads;
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


	float	StartXButton1;// = 0.0f;
	float	EndXButton1;// = 0.0f;
	float	StartYButton1;// = 0.0f;
	float	EndYButton1;// = 0.0f;

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void TurnOffVSync();

	void TurnOnVSync();
	void TurnOnVSync_Ext();

};



extern UI_OptionsSettings_Dialog* g_ANA_UI_OptionsSettings_Dialog;


#endif
