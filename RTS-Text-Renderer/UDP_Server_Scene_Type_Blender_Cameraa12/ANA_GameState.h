#ifndef BASE_ANA_GAMESTATE_CLASS_H
#define BASE_ANA_GAMESTATE_CLASS_H


#include "MainMenu_UI.h"
#include "UI_OptionsSettings_Dialog.h"
#include "GameHUD_UI.h"


#ifdef WIN32
#pragma once
#endif


class AnaGameState
{
public:
	AnaGameState();
	~AnaGameState();

	int m_iMainGameState;

	int m_iPlayGameInGameState;

	int m_iPlayingPendingJoinGame;
	// vector <GameMatchMake> gamesMatchMaking;

	int GetMainGameState();          // Loading 0, MainMenu 1, PlayGame 2
	int GetPlayGameInGameState();    // Init 0 Loading 1,GameStarting 2, Connecting 3, PlayingGame 4
	int GetPlayingPendingJoinGame();          // No Matching Making, Finding Game, Found Game, Joining Other Game, Trying to join multiple games

	void SetMainGameState(int iMainGameState);
	void SetPlayGameInGameState(int iPlayGameInGameState); // when inside a game
	void SetPlayingPendingJoinGame(int iPlayingPendingJoinGame);

	int m_iSettingOptionsDialogState;
	int GetSettingOptionsDialogState();
	void SetSettingOptionsDialogState(int iSettingOptionsDialogState);

	//int iSettingOptionsDialog_MainVertices_index;
};

extern AnaGameState* g_pAnaGameState;

#endif
