#pragma once

#include <iostream>

#include <set>
#include <vector>

#include <sstream>

#include <Util.h>
#include <Version.h>
#include <Common.h>
#include <Graphics.h>
#include <GfxObject.h>
#include <TimerOn.h>
#include <CollisionRect.h>
#include <Color.h>

#include <CKT_GUI.h>

#include "Board.h"

namespace CKT
{
	class CGame
	{
	public:
		typedef SDL_Window* PWINDOW;
		typedef SDL_Surface* PSURFACE;

		const CVersion GAME_VERSION;

	private:
		PWINDOW m_pWin = nullptr;
		CKT::PRENDERER m_pRenderer = nullptr;

		SScreen SCREEN;

		float m_TimeFrame = 0.0f;
		float m_FPS = 0;

		Uint32 m_FrameTimeFixed = 1000 / 60;	// 60 frames per second is default = 16ms per Frame

		bool m_Run = true;
		bool m_Paused = true;
		bool m_FirstInitDone = false;

		const SDL_Color m_ClearColor = { 66,33,0,255 };

		std::string m_ResPath = "";

	private:
		// Gamelogic
		GAME::CBoard m_Board;
		float m_GameTime = 0.0f;

		/**
		* 1: to switch to the Game
		*-1: to switch to the pause menu
		*/
		int m_SwitchMenu = 0;
		CTimerOn m_Timer;

		static const int BOARD_W = 8, BOARD_H = 8;

	private:
		// GUI
		GUI::CPanel m_Menu;
		GUI::CMenubar* m_MenuBar = nullptr;

	private:
		// Callbacks for Events
		static void onMenuClickedCallback(void* pThis, CKT::GUI::CMenuItem& sender, GUI::CBtnEventArgs& args);
		void onMenuClicked(GUI::CMenuItem& sender, GUI::CBtnEventArgs& args);

	private:
		// Game init
		int SDLInit();

		int GameInit();
		int InitFigures(GAME::eWhere up);

		int GuiInit();

	private:
		// Game update and rendering
		int Move();

		int Render(CKT::PRENDERER pRen);

	public:
		CGame() : GAME_VERSION("0.6.3")
		{  }

		int AppInit();

		int AppExit(int code);

		int AppLoop();

	};

}