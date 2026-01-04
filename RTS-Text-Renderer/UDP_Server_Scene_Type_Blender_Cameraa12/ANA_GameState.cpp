
#include "ANA_GameState.h"



AnaGameState::AnaGameState()
{
	m_iMainGameState = 0;

	m_iPlayGameInGameState = 0;

	m_iPlayingPendingJoinGame = 0;

	m_iSettingOptionsDialogState = 0; // 0 show to dialog, 1 show dialog



}

AnaGameState::~AnaGameState()
{


}

int AnaGameState::GetMainGameState() {
	// Loading 0, MainMenu 1, PlayGame 2
	return m_iMainGameState;
}
int AnaGameState::GetPlayGameInGameState()
{
	// Loading 0,GameStarting 1, Connecting 2, PlayingGame 3
	return m_iPlayGameInGameState;

}
int AnaGameState::GetPlayingPendingJoinGame()
{

	return m_iPlayingPendingJoinGame;
}

int AnaGameState::GetSettingOptionsDialogState()
{

	return m_iSettingOptionsDialogState;
}


void AnaGameState::SetMainGameState(int iMainGameState) {
	m_iMainGameState = iMainGameState;
	// Loading 0, MainMenu 1, PlayGame 2
	if (g_ANA_MainMenuUI)
	{
		g_ANA_MainMenuUI->UpdateMainMenu();
	}
	if (g_ANA_GameHUDUI)
	{
		g_ANA_GameHUDUI->UpdateMainMenu();

	}


}
void AnaGameState::SetPlayGameInGameState(int iPlayGameInGameState) // when inside a game
{
	// Loading 0,GameStarting 1, Connecting 2, PlayingGame 3
	m_iPlayGameInGameState = iPlayGameInGameState;

}
void AnaGameState::SetPlayingPendingJoinGame(int iPlayingPendingJoinGame)
{

	m_iPlayingPendingJoinGame = iPlayingPendingJoinGame;
}


void AnaGameState::SetSettingOptionsDialogState(int iSettingOptionsDialogState)
{
	m_iSettingOptionsDialogState = iSettingOptionsDialogState;

	if (g_ANA_UI_OptionsSettings_Dialog)
	{
		g_ANA_UI_OptionsSettings_Dialog->UpdateMainMenu();
	}


}



#ifndef NULL
#define NULL2 nullptr; // may not exist in C98
#endif

AnaGameState* g_pAnaGameState = 0;
