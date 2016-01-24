#pragma once

#include <iostream>

#include <set>
#include <vector>

#include <sstream>

#include "Version.h"

#include "IniFileIO.h"

#include "Common.h"

#include "FontManager.h"

#include "Background.h"
#include "Player.h"
#include "Enemy.h"

#include "CollisionRect.h"
#include "CollisionCircle.h"

#include "GUIBase.h"
#include "Label.h"
#include "Btn.h"
#include "ToggleBtn.h"
#include "Panel.h"
#include "Scrollbar.h"
#include "RadioBtn.h"
#include "Progressbar.h"
#include "Clock.h"

#include "GuiScrollableContainer.h"
#include "GroupBoxRBtn.h"
#include "GroupBoxBtn.h"

#include "SimpleScrollbarVer.h"

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

		float m_TimeFrame = 0.0f;
		float m_FPS = 0;

		Uint32 m_FrameTimeFixed = 1000 / 60;	// 60 frames per second is default = 16ms per Frame

		bool m_StatInfo = false;

		bool m_Run = true;
		bool m_Paused = true;
		bool m_FirstInitDone = false;

		CKT::IO::CIniFileIO m_IniFile;

		std::string m_ResPath = "";

	private:
		// Gamelogic
		CKT::GAME::CBackground m_Back;
		CKT::GAME::CPlayer m_Player;
		CKT::GAME::CShoot m_Shoot;
		CKT::GFX::GfxObject m_Explosion;
		std::set<CKT::GAME::CEnemy*> m_Enemys;
		int m_EnemysShot = 0;

		Uint32 m_LastShieldTime = 0;
		Uint32 m_ShieldDamgeTime = 200;

		float m_GameTime = 0.0f;

	private:
		// GUI
		CKT::GUI::CLabel m_Label[20];
		CKT::GUI::CBtn m_btnExit;
		CKT::GUI::CBtn m_btnRestart;
		CKT::GUI::CBtn m_btnPlay;
		CKT::GUI::CToggleBtn m_But2;
		CKT::GUI::CPanel m_MenuPanel;
		CKT::GUI::CRadioBtn m_Radio1;
		CKT::GUI::CRadioBtn m_Radio2;
		CKT::GUI::CRadioBtn m_Radio3;
		CKT::GUI::CRadioBtn m_Radio4;
		CKT::GUI::CProgressbar* m_Bar;
		CKT::GUI::CClock m_Clock;
		CKT::GUI::CGuiScrollableContainer m_Cont;
		CKT::GUI::CGroupBoxRBtn m_Group1;
		CKT::GUI::CGroupBoxRBtn m_Group2;
		CKT::GUI::CGroupBoxBtn m_BtnGroup;

	private:
		// Callbacks for Events
		static void onClickedCallback(void* pThis, CKT::GUI::CBtn& sender, GUI::CBtnEventArgs& args);
		void onClicked(GUI::CBtn& sender, GUI::CBtnEventArgs& args);
		static void onGotFocusCallback(void* pThis, CKT::GUI::CFocusableObj& sender, GUI::CGuiEventArgs& args);
		void onGotFocus(CKT::GUI::CFocusableObj& sender, GUI::CGuiEventArgs& args);
		static void onLostFocusCallback(void* pThis, CKT::GUI::CFocusableObj& sender, GUI::CGuiEventArgs& args);
		void onLostFocus(CKT::GUI::CFocusableObj& sender, GUI::CGuiEventArgs& args);
		static void onValueCallback(void * pThis, CKT::GUI::CScrollbar & sender, GUI::CGuiEventArgs& args);
		void onValue(GUI::CScrollbar & sender, GUI::CGuiEventArgs& args);

	private:
		// Game init
		int SDLInit();

		int GameInit();

		int InitEnemeis();

		int GuiInit();

	private:
		// Game update and rendering
		int Move();

		int Render(CKT::PRENDERER pRen);

	public:
		CGame() : GAME_VERSION("0.6.3") {  }

		int AppInit();

		int AppExit(int code);

		int AppLoop();

	};

}