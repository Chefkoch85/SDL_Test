
#include <SDL.h>
#include <cstdio>
#include <conio.h>
#include <iomanip>

#include "Game.h"

#include "Cleanup.h"

#include "ScrollbarHor.h"
#include "ScrollbarVer.h"

#include "ProgressbarV.h"
#include "ProgressbarH.h"

#include "TimerOn.h"

#include <SDL_syswm.h>

using namespace CKT;

void CKT::CGame::onClickedCallback(void * pThis, CKT::GUI::CBtn & sender, GUI::CBtnEventArgs& args)
{
	CGame* self = static_cast<CGame*>(pThis);
	self->onClicked(sender, args);
}
void CKT::CGame::onClicked(GUI::CBtn & sender, GUI::CBtnEventArgs& args)
{
	std::cout << std::setw(30) << std::left << "callback \"onClick()\"" << " : ";
	std::cout << std::setw(15) << std::left << sender.Name() << " |ID: " << std::setw(3) << args.ID() << " |State: " << args.ClickState() <<  std::endl;

	if (args.ClickState() == GUI::CBtnEventArgs::Up && m_btnExit.ID() == args.ID())
	{
		m_Run = false;
	}
	else if(args.ClickState() == GUI::CBtnEventArgs::Up && m_btnRestart.ID() == args.ID())
	{
		if (m_Paused)
			GameInit();
	}
	else if (args.ClickState() == GUI::CBtnEventArgs::Up && m_btnPlay.ID() == args.ID())
	{
		if (m_Enemys.size() != 0)
			m_Paused = !m_Paused;
	}
}

void CKT::CGame::onGotFocusCallback(void * pThis, CKT::GUI::CFocusableObj & sender, GUI::CGuiEventArgs & args)
{
	CGame* self = static_cast<CGame*>(pThis);
	self->onGotFocus(sender, args);
}
void CGame::onGotFocus(CKT::GUI::CFocusableObj& sender, GUI::CGuiEventArgs& args)
{
	std::cout << std::setw(30) << std::left << "callback \"onGotFocus()\"" << " : " << std::setw(15) << sender.Name() << " |ID: " << std::setw(3) << args.ID() << std::endl;

	if (sender.ID() == m_btnExit.ID() ||
		sender.ID() == m_btnRestart.ID() ||
		sender.ID() == m_btnPlay.ID())
	{
		((GUI::CBtn&)sender).Content().TextColor({ 230,100,50,255 });
	}
}

void CKT::CGame::onLostFocusCallback(void * pThis, CKT::GUI::CFocusableObj & sender, GUI::CGuiEventArgs & args)
{
	CGame* self = static_cast<CGame*>(pThis);
	self->onLostFocus(sender, args);
}
void CGame::onLostFocus(CKT::GUI::CFocusableObj& sender, GUI::CGuiEventArgs& args)
{
	std::cout << std::setw(30) << std::left << "callback \"onLostFocus()\"" << " : " << std::setw(15) << sender.Name() << " |ID: " << std::setw(3) << args.ID() << std::endl;

	if (sender.ID() == m_btnExit.ID() ||
		sender.ID() == m_btnRestart.ID() ||
		sender.ID() == m_btnPlay.ID())
	{
		((GUI::CBtn&)sender).Content().TextColor({ 255,255,255,255 });
	}
}

void CKT::CGame::onValueCallback(void * pThis, CKT::GUI::CScrollbar & sender, GUI::CGuiEventArgs& args)
{
	CGame* self = static_cast<CGame*>(pThis);
	self->onValue(sender, args);
}
void CKT::CGame::onValue(GUI::CScrollbar & sender, GUI::CGuiEventArgs& args)
{
	std::cout << std::setw(30) << std::left << "callback \"onValue()\"" << " : ";
	std::cout << std::setw(15) << std::left << sender.Name() << " |ID: " << std::setw(3) << args.ID() << " |State: " << sender.GetValue() << std::endl;

	//if (args.ID() == m_Scrollbar[0]->ID())
	//	//m_Clock.Angle() = sender.GetValue();
	//if (args.ID() == m_Scrollbar[0]->ID())
	//	m_Bar->Value() = sender.GetValue();
}


int CGame::Move()
{
	SDL_Event e = { 0 };
	std::string subsys = "";
	CKT::IO::CIniFileIO PlayerIni;
	while (SDL_PollEvent(&e))
	{
		//if (m_btnExit.IsUp())
			//m_Run = false;

		//if (m_Paused && m_btnRestart.IsUp())
			//GameInit();

		//if(m_Enemys.size() != 0 && m_btnPlay.IsUp())
			//m_Paused = !m_Paused;

		switch (e.type)
		{
		case SDL_QUIT:
			m_Run = false;
			break;

		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				if (m_Enemys.size() != 0)
					m_Paused = !m_Paused;

				break;

			case SDLK_a:
				m_Player.KeyLeft(true);
				break;

			case SDLK_d:
				m_Player.KeyRight(true);
				break;

			case SDLK_SPACE:
				m_Player.KeyShoot(true);
				break;

			case SDLK_r:
				if (m_Paused)
					GameInit();
				break;

			case SDLK_p:
				if (m_Enemys.size() != 0)
					m_Paused = !m_Paused;
				break;

			case SDLK_s:
				m_Player.HasShield() = !m_Player.HasShield();
				break;

			case SDLK_BACKQUOTE:
				m_StatInfo = !m_StatInfo && INI_DATA.Console;
				DEBUG_ON = !DEBUG_ON && INI_DATA.Console;
				break;
					
			case SDLK_m:
				if (INI_DATA.MAX_FPS_Lock || INI_DATA.VSync)
					PlayerIni.Open(m_ResPath + "CONFIG\\Player_FPSLOCK.ini");
				else
					PlayerIni.Open(m_ResPath + "CONFIG\\Player.ini");

				PlayerIni.Read();

				CKT::GAME::CPlayer::PlayerVars var;
				var.BOUNCE_STRENGTH = PlayerIni.GetEntryAsFloat("GENERAL", "BOUNCE_EFC");
				var.TIME_TO_SHOOT = PlayerIni.GetEntryAsInt("GENERAL", "SHOT_TIME");
				var.ACC_SPEED = PlayerIni.GetEntryAsFloat("MOVEMENT", "ACC");
				var.BRAKE_SPEED = PlayerIni.GetEntryAsFloat("MOVEMENT", "BRAKE");
				var.MAX_SPEED = PlayerIni.GetEntryAsFloat("MOVEMENT", "MAX_VEL");
				var.ANIM_STEP_0 = PlayerIni.GetEntryAsFloat("ANIM", "ANIM_STEP_0");
				var.ANIM_STEP_1 = PlayerIni.GetEntryAsFloat("ANIM", "ANIM_STEP_1");
				var.ANIM_STEP_2 = PlayerIni.GetEntryAsFloat("ANIM", "ANIM_STEP_2");

				PlayerIni.Close();

				m_Player.PlayerData(var);

				break;

			case SDLK_1:
				m_Radio1.IsPressed() = false;
				m_Radio2.IsPressed() = false;
				break;

			case SDLK_2:
				for (int i = 0; i < (int)GFX::CTextureManager::Instance()->GetTextureNames().size(); i++)
				{
					std::cout << std::setw(3) << std::right << i << " : " << GFX::CTextureManager::Instance()->GetTextureNames()[i] << std::endl;
				}
				break;

			case SDLK_3:
				std::cout << "Has clipboard data: " << (SDL_HasClipboardText() ? "TRUE" : "FALSE") << std::endl;
				SDL_SysWMinfo info;
				SDL_VERSION(&info.version);

				if (SDL_GetWindowWMInfo(m_pWin, &info))	// the call returns true on success
				{
					switch (info.subsystem)
					{
					case SDL_SYSWM_UNKNOWN:
						subsys = "an unkown system!";
						break;

					case SDL_SYSWM_WINDOWS:
						subsys = "Microsoft Windows(TM)";
						break;
					case SDL_SYSWM_X11:
						subsys = "X Window System";
						break;
#if SDL_VERSION_ATLEAST(2, 0, 3)
					case SDL_SYSWM_WINRT:
						subsys = "WinRT";
						break;
#endif
					case SDL_SYSWM_DIRECTFB:
						subsys = "DirectFB";
						break;
					case SDL_SYSWM_COCOA:
						subsys = "Apple OS X";
						break;
					case SDL_SYSWM_UIKIT:
						subsys = "UIKit";
						break;
#if SDL_VERSION_ATLEAST(2, 0, 2)
					case SDL_SYSWM_WAYLAND:
						subsys = "Wayland";
						break;
					case SDL_SYSWM_MIR:
						subsys = "Mir";
						break;
#endif
#if SDL_VERSION_ATLEAST(2, 0, 4)
					case SDL_SYSWM_ANDROID:   subsystem = "Android";                break;
#endif
					}
				}

				std::cout << subsys << std::endl;

				break;

			case SDLK_4:
				std::cout << SDL_GetClipboardText() << std::endl;
				break;

			case SDLK_5:

				SDL_Log("SDL_GetNumVideoDrivers(): %i", SDL_GetNumVideoDrivers());
				std::cout << "SDL_GetVideoDriver(): " << SDL_GetVideoDriver(0) << std::endl;
				std::cout << "SDL_GetVideoDriver(): " << SDL_GetVideoDriver(1) << std::endl;

				int i, display_mode_count;
				SDL_DisplayMode mode;
				Uint32 f;

				SDL_Log("SDL_GetNumVideoDisplays(): %i", SDL_GetNumVideoDisplays());

				SDL_Rect r;
				SDL_GetDisplayBounds(0, &r);
				SDL_GetDisplayBounds(1, &r);

				display_mode_count = SDL_GetNumDisplayModes(1);
				if (display_mode_count < 1) 
				{
					SDL_Log("SDL_GetNumDisplayModes failed: %s", SDL_GetError());
					return 1;
				}
				SDL_Log("SDL_GetNumDisplayModes: %i", display_mode_count);

				for (i = 0; i < display_mode_count; ++i) 
				{
					if (SDL_GetDisplayMode(1, i, &mode) != 0) 
					{
						SDL_Log("SDL_GetDisplayMode failed: %s", SDL_GetError());
						return 1;
					}
					f = mode.format;

					SDL_Log("Mode %i\tbpp %i\t%s\t%i x %i", i, SDL_BITSPERPIXEL(f), SDL_GetPixelFormatName(f), mode.w, mode.h);
				}
				break;

			}

			break;

		case SDL_KEYUP:
			
			switch (e.key.keysym.sym)
			{
			case SDLK_a:
				m_Player.KeyLeft(false);
				break;

			case SDLK_d:
				m_Player.KeyRight(false);
				break;

			case SDLK_SPACE:
				m_Player.KeyShoot(false);
				break;
			}
				
			break;
			
		}

	} // while

	if (m_Paused)
	{
		m_MenuPanel.Update(&e);
		m_Clock.Update(m_TimeFrame);
		m_Cont.Update(&e);
	}
	
	if (m_Paused)
		return 0;

	m_GameTime += m_TimeFrame;

	// for testing
	m_Shoot.PlayAnimation(0, 2, 40);
		
	// general update calls
	m_Player.Update(m_TimeFrame);
		
	for each (auto en in m_Enemys)
	{
		en->Update(m_TimeFrame);
	}
		
		
	// test collision between player and the extra shot (only for testing!)
	SDL_SetTextureColorMod(m_Player.Texture(), 255, 255, 255);
	SDL_SetTextureColorMod(m_Player.GetCollisionObj()->Texture(), 255, 255, 255);
	if (m_Player.GetCollisionObj()->IsColliding((CKT::GAME::CCollisionCircle*)m_Shoot.GetCollisionObj()))
	{
		if (m_LastShieldTime == 0)
		{
			m_LastShieldTime = SDL_GetTicks();
		}

		if (!m_Player.HasShield())
		{
			SDL_SetTextureColorMod(m_Player.Texture(), 200, 50, 50);
		}
		else if(m_LastShieldTime + m_ShieldDamgeTime > SDL_GetTicks())
		{
			SDL_SetTextureColorMod(m_Player.GetCollisionObj()->Texture(), 230, 60, 100);
		}
	}
	else
	{
		m_LastShieldTime = 0;
	}

	// delete shoted enemies
	for each (CKT::GAME::CEnemy* en in m_Enemys)
	{
		if (!en->IsActive())
		{
			m_Enemys.erase(en);
			delete en;
			m_EnemysShot++;
			// nesseccary ohterwise the for loop will crash when deleting an enemey
			break;
		}
	}


	// general hit testing of shoots from player and enemys
	bool hit = false;
	for each(CKT::GAME::CShoot* shoot in m_Player.GetShoots())
	{
		for each(CKT::GAME::CEnemy* en in m_Enemys)
		{
			if (en->Visibility() && shoot->GetCollisionObj()->IsColliding((CKT::GAME::CCollisionRect*)en->GetCollisionObj()))
			{
				hit = true;

				en->Life()--;

				if (en->Life() <= 0)
				{
					en->Visibility() = false;
				}		
			}
		}

		if (hit)
		{
			m_Player.GetShoots().erase(shoot);
			delete shoot;
			// nesseccary ohterwise the for loop will crash when deleting a shoot
			break;
		}
	}
		
	// check if enemy can fire
	for each(GAME::CEnemy* en in m_Enemys)
	{
		for each(GAME::CEnemy* other in m_Enemys)
		{
			if (en->IsObstacle(other))
			{
				en->ShotAllowed() = false;
				break;
			}
			else
			{
				en->ShotAllowed() = true;
			}
		}
	}


	if (m_Enemys.size() == 0)
		m_Paused = true;

	return 0;
}

int CGame::Render(CKT::PRENDERER pRen)
{
	m_Back.Render();

	m_Shoot.Render();

	for each (CKT::GFX::GfxObject* item in m_Enemys)
	{
		item->Render();
	}
		
	m_Player.Render();
		
	SDL_Color color = { 255, 20, 20, 255 };
	CKT::GFX::CFontManager::Instance()->renderText("Enemys left", color, pRen, CKT::SCREEN.W - 150, 5);
	// to make a integrated type to a string you can use a stringstream or...
	std::string str = "";
	std::stringstream ss;
	//ss << m_Enemys.size();
	//str = ss.str();
	// ... std::to_string(x)
	str = std::to_string(m_Enemys.size());
	CKT::GFX::CFontManager::Instance()->renderText(str, color, pRen, CKT::SCREEN.W - 30, 5);

	color = { 20,255,20,255 };
	CKT::GFX::CFontManager::Instance()->renderText("Enemys shot", color, pRen, CKT::SCREEN.W - 150, 20);
	//ss.str("");
	//ss << m_EnemysShot;
	//str = ss.str();
	str = std::to_string(m_EnemysShot);
	CKT::GFX::CFontManager::Instance()->renderText(str, color, pRen, CKT::SCREEN.W - 30, 20);

	color = { 150,255,20,255 };
	// if you have to format them i will prefer stringstream
	str = "Time ";
	ss.str("");
	ss.precision(3);
	ss << std::fixed << str << m_GameTime;
	CKT::GFX::CFontManager::Instance()->renderText(ss.str(), color, pRen, 360, 5, 1);

	str = "SDL Test Game - FPS: " + std::to_string(m_FPS);
	SDL_SetWindowTitle(m_pWin, str.c_str());

	if (m_Paused)
	{
		m_MenuPanel.Render();
		m_Clock.Render();
		m_Cont.Render();

		if (m_Enemys.size() == 0)
		{
			color = { 10,200,10,255 };
			//CKT::GFX::CFontManager::Instance()->renderText("You are victorious!", color, pRen, 5, 130,2); 
			m_MenuPanel.GetControlByName("labVictory")->Visibility() = true;
			if (m_EnemysShot <= 1)
				str = " alien";
			else
				str = " aliens";
			ss.str("");
			ss << "You killed " << m_EnemysShot << str << " in " << m_GameTime << " sec";

			int w, h;
			CKT::GFX::CFontManager::Instance()->TextMetrics(1, ss.str(), &w, &h);
			color = { 255,255,0,255 };
			CKT::GFX::CFontManager::Instance()->renderText(ss.str(), color, pRen, (CKT::SCREEN.W - w) - 110, 200, 1);
		}
		else
		{
			m_MenuPanel.GetControlByName("labVictory")->Visibility() = false;
		}
	}


	// debug infos
	if (!m_StatInfo)
		return 0;
	
	GFX::CFontManager::Instance()->AlphaMod() = 128;

	color = { 255, 255, 255, 0 };
	str = "FrameTime - ";
	ss.str("");
	ss << str << m_TimeFrame;
	str = ss.str();
	CKT::GFX::CFontManager::Instance()->renderText(str, color, pRen, 5, 5);

	ss.str("");
	ss << "FPS - " << m_FPS;
	str = ss.str();
	CKT::GFX::CFontManager::Instance()->renderText(str, color, pRen, 5, 20);

	std::string info = "CPU-Cores - ";
	info += std::to_string(SDL_GetCPUCount());
	CKT::GFX::CFontManager::Instance()->renderText(info, color, pRen, 5, 35);

	info = "RAM - ";
	info += std::to_string(SDL_GetSystemRAM());
	info += " MB";
	CKT::GFX::CFontManager::Instance()->renderText(info, color, pRen, 5, 50);

	info = "Loaded Textures - ";
	info += std::to_string(GFX::CTextureManager::Instance()->GetTextureCount());
	CKT::GFX::CFontManager::Instance()->renderText(info, color, pRen, 5, 65);

	SDL_version v = { 0 };
	SDL_VERSION(&v);
	info = "SDL-Version - ";
	info += std::to_string(v.major) + ".";
	info += std::to_string(v.minor) + ".";
	info += std::to_string(v.patch);
	CKT::GFX::CFontManager::Instance()->renderText(info, color, pRen, 5, 80);

	GFX::CFontManager::Instance()->AlphaMod() = 255;

	return 0;
}


int CGame::SDLInit()
{
	// get INI-File data
	m_IniFile.Open(m_ResPath + "SDL_TestGame.ini");
	std::cout << "Ini-Read() error: " << m_IniFile.Read() << std::endl;

	INI_DATA.WinX = SCREEN.X = m_IniFile.GetEntryAsInt("GENERAL", "WIN_X");
	INI_DATA.WinY = SCREEN.Y = m_IniFile.GetEntryAsInt("GENERAL", "WIN_Y");

	INI_DATA.Lang = m_IniFile.GetEntry("GENERAL", "LANG");
	INI_DATA.Console = m_IniFile.GetEntryAsBool("GENERAL", "CONSOLE");

	INI_DATA.NumEnemies_TL = m_IniFile.GetEntryAsInt("GENERAL", "NUM_EN_TL");
	INI_DATA.NumEnemies_ML = m_IniFile.GetEntryAsInt("GENERAL", "NUM_EN_ML");
	INI_DATA.NumEnemies_BL = m_IniFile.GetEntryAsInt("GENERAL", "NUM_EN_BL");

	INI_DATA.WinW = SCREEN.W = m_IniFile.GetEntryAsInt("VIDEO", "WIN_W");
	INI_DATA.WinH = SCREEN.H = m_IniFile.GetEntryAsInt("VIDEO", "WIN_H");
	INI_DATA.VSync = m_IniFile.GetEntryAsBool("VIDEO", "VSYNC");
	INI_DATA.MAX_FPS_Lock = m_IniFile.GetEntryAsBool("VIDEO", "MAX_FPS_LOCK");
	INI_DATA.MaxFPS = m_IniFile.GetEntryAsInt("VIDEO", "MAX_FPS");
	INI_DATA.FullScreen = m_IniFile.GetEntryAsBool("VIDEO", "FULLSCR");

	INI_DATA.AppStringFile = m_IniFile.GetEntry("FILES", "APP_STR");
	INI_DATA.PlayerIni = m_IniFile.GetEntry("FILES", "PLAYER_INI");

	m_IniFile.Clear();
	m_IniFile.Close();
	
	// only Vsync or FPS-Lock (VSync is better) 
	if (INI_DATA.VSync)
		INI_DATA.MAX_FPS_Lock = false;

	// pre calculate the Fixed FPS frame time if it is active (default is 16ms [60 fps])
	if (INI_DATA.MAX_FPS_Lock)
		m_FrameTimeFixed = 1000 / INI_DATA.MaxFPS;

	// init SDL and other libaries
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		CKT::logSDLError(std::cerr, "ERROR->SDL_Init()");
		return 1;
	}

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		CKT::logSDLError(std::cerr, "ERROR->SDL_Init()");
		SDL_Quit();
		return 2;
	}

	if (TTF_Init() != 0) 
	{
		CKT::logSDLError(std::cout, "ERROR->TTF_Init");
		SDL_Quit();
		return 3;
	}

	// create a SDL window
	m_pWin = SDL_CreateWindow("SDL-TEST", CKT::SCREEN.X, CKT::SCREEN.Y, CKT::SCREEN.W, CKT::SCREEN.H, SDL_WINDOWEVENT_SHOWN);

	int flags = 0;
	if (INI_DATA.FullScreen)
		flags |= SDL_WINDOW_FULLSCREEN;

	SDL_SetWindowFullscreen(m_pWin, flags);

	if (m_pWin == nullptr)
	{
		CKT::logSDLError(std::cerr, "ERROR->CreateWindow()");
		return 4;
	}

	// create Renderer
	flags = SDL_RENDERER_ACCELERATED;
	if (INI_DATA.VSync)
		flags |= SDL_RENDERER_PRESENTVSYNC;

	m_pRenderer = SDL_CreateRenderer(m_pWin, -1, flags);
	if (m_pRenderer == nullptr)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		cleanup(m_pWin);
		return 5;
	}

	return 0;
}

int CGame::GameInit()
{
	// restart
	if (m_FirstInitDone)
	{
		// clear enemies
		if (m_Enemys.size() > 0)
		{
			for each (CKT::GAME::CEnemy* item in m_Enemys)
			{
				delete item;
			}

			m_Enemys.clear();
		}

		// reset all things
		m_EnemysShot = 0;
		m_Player.ResetPlayer();
		m_Player.SetPos((CKT::SCREEN.W - m_Player.Width()) / 2.0f, (CKT::SCREEN.H - m_Player.Height()) - 12.0f);
		m_Player.Update(m_TimeFrame);
		m_GameTime = 0.0f;

		InitEnemeis();
	}

	// first Init
	if (m_FirstInitDone)
		return 0;

	// player creation
	CKT::IO::CIniFileIO PlayerIni;

	if (INI_DATA.MAX_FPS_Lock || INI_DATA.VSync)
		PlayerIni.Open(m_ResPath + "CONFIG\\Player_FPSLOCK.ini");
	else
		PlayerIni.Open(m_ResPath + "CONFIG\\Player.ini");

	PlayerIni.Read();

	CKT::GAME::CPlayer::PlayerVars var;
	var.BOUNCE_STRENGTH = PlayerIni.GetEntryAsFloat("GENERAL", "BOUNCE_EFC");
	var.TIME_TO_SHOOT = PlayerIni.GetEntryAsInt("GENERAL", "SHOT_TIME");
	var.ACC_SPEED = PlayerIni.GetEntryAsFloat("MOVEMENT", "ACC");
	var.BRAKE_SPEED = PlayerIni.GetEntryAsFloat("MOVEMENT", "BRAKE");
	var.MAX_SPEED = PlayerIni.GetEntryAsFloat("MOVEMENT", "MAX_VEL");
	var.ANIM_STEP_0 = PlayerIni.GetEntryAsFloat("ANIM", "ANIM_STEP_0");
	var.ANIM_STEP_1 = PlayerIni.GetEntryAsFloat("ANIM", "ANIM_STEP_1");
	var.ANIM_STEP_2 = PlayerIni.GetEntryAsFloat("ANIM", "ANIM_STEP_2");

	PlayerIni.Close();

	m_Player.PlayerData(var);

	m_Player.Init(m_pRenderer, m_ResPath + "IMG\\PLAYER\\X-Wing_S5.png", 0, 0, 5, 1);
	m_Player.SetPos((CKT::SCREEN.W - m_Player.Width()) / 2.0f, (CKT::SCREEN.H - m_Player.Height()) - 12.0f);
	CKT::GAME::CCollisionObj* obj = new CKT::GAME::CCollisionCircle(m_Player, 65);
	obj->Init(m_pRenderer, m_ResPath + "IMG\\PLAYER\\shields.png", 0, 0, 130, 130);
	m_Player.SetCollisionObj(obj);

	m_Player.Update(m_TimeFrame);

	// shoot creation (for testing)
	m_Shoot.Init(m_pRenderer, m_ResPath + "IMG\\BACK\\Star_S3.png", 150, 500, 3, 1, 4.0f);
	CKT::GAME::CCollisionObj* colObj = new CKT::GAME::CCollisionCircle(m_Shoot, 35);
	colObj->Init(m_pRenderer, m_ResPath + "IMG\\DEBUG\\circle_96.png", 0, 0, 70, 70);
	m_Shoot.SetCollisionObj(colObj);

	// enemy creation
	InitEnemeis();

	// Explosion creation
	m_Explosion.Init(m_pRenderer, m_ResPath + "IMG\\EXPLOSION\\exp_S4x4.png", 368, 268, 4, 4);

	// Background creation
	m_Back.Init(m_pRenderer, m_ResPath + "IMG\\BACK\\Back.png", CKT::SCREEN.W, CKT::SCREEN.H);

	// font creation
	CKT::GFX::CFontManager::Instance()->loadFont(m_ResPath + "FONT\\Chromia.otf", 16);
	CKT::GFX::CFontManager::Instance()->loadFont(m_ResPath + "FONT\\Space_age.ttf", 56);

	// Menu creation
	GuiInit();

	//CKT::GFX::GfxObject* obj = m_Enemys.back();
	//m_Enemys.pop_back();
	//delete obj;

	if (!m_FirstInitDone)
		m_FirstInitDone = true;

	return 0;
}

int CKT::CGame::InitEnemeis()
{
	CKT::GAME::CCollisionObj* colObj = nullptr;

	PTEXTURE t = GFX::CTextureManager::Instance()->loadTexture(m_ResPath + "IMG\\ENEMY\\Enemy_S3.png", m_pRenderer);
	int w, h;
	SDL_QueryTexture(t, nullptr, nullptr, &w, &h);

	GFX::CTextureManager::Instance()->releaseTexture(t);

	int spaceOneEnemey = w / 3;
	int maxEnemies = SCREEN.W / spaceOneEnemey;

	int enemies = INI_DATA.NumEnemies_TL > maxEnemies ? maxEnemies : INI_DATA.NumEnemies_TL;
	int spaceEnemies = spaceOneEnemey * enemies;
	int dist = (SCREEN.W / enemies);
	int start = (SCREEN.W - (spaceEnemies + ((dist - spaceOneEnemey) * (enemies - 1)))) / 2;

	for (int i = start; i < SCREEN.W; i += dist)
	{
		CKT::GAME::CEnemy* en = new CKT::GAME::CEnemy();
		en->Init(m_pRenderer, m_ResPath + "IMG\\ENEMY\\Enemy_S3.png", (float)i, 50, 3, 1, { 0,0,48,48 });
		colObj = new CKT::GAME::CCollisionRect(*en);
		colObj->Init(m_pRenderer, m_ResPath + "IMG\\DEBUG\\rect_96.png", 0, 0, en->Width(), en->Height());
		en->SetCollisionObj(colObj);
		m_Enemys.insert(en);
	}

	enemies = INI_DATA.NumEnemies_ML > maxEnemies ? maxEnemies : INI_DATA.NumEnemies_ML;
	spaceEnemies = spaceOneEnemey * enemies;
	dist = (SCREEN.W / enemies);
	start = (SCREEN.W - (spaceEnemies + ((dist - spaceOneEnemey) * (enemies - 1)))) / 2;
	for (int i = start; i < CKT::SCREEN.W; i += dist)
	{
		CKT::GAME::CEnemy* en = new CKT::GAME::CEnemy();
		en->Init(m_pRenderer, m_ResPath + "IMG\\ENEMY\\Enemy_S3.png", (float)i, 150, 3, 1, { 0,0,48,48 });
		colObj = new CKT::GAME::CCollisionRect(*en);
		colObj->Init(m_pRenderer, m_ResPath + "IMG\\DEBUG\\rect_96.png", 0, 0, en->Width(), en->Height());
		en->SetCollisionObj(colObj);
		m_Enemys.insert(en);
	}

	enemies = INI_DATA.NumEnemies_BL > maxEnemies ? maxEnemies : INI_DATA.NumEnemies_BL;
	spaceEnemies = spaceOneEnemey * enemies;
	dist = (SCREEN.W / enemies);
	start = (SCREEN.W - (spaceEnemies + ((dist - spaceOneEnemey) * (enemies - 1)))) / 2;
	for (int i = start; i < CKT::SCREEN.W; i += dist)
	{
		CKT::GAME::CEnemy* en = new CKT::GAME::CEnemy();
		en->Init(m_pRenderer, m_ResPath + "IMG\\ENEMY\\Enemy_S3.png", (float)i, 250, 3, 1, { 0,0,48,48 });
		colObj = new CKT::GAME::CCollisionRect(*en);
		colObj->Init(m_pRenderer, m_ResPath + "IMG\\DEBUG\\rect_96.png", 0, 0, en->Width(), en->Height());
		en->SetCollisionObj(colObj);
		m_Enemys.insert(en);
	}

	return 0;
}

int CKT::CGame::GuiInit()
{
	// Menu background
	CKT::GUI::CGUIBase* back = new CKT::GUI::CGUIBase();
	back->Init(m_pRenderer, m_ResPath + "IMG\\GUI\\Menu_Backgrd_1.png", 0, 0);

	m_Label[0].Init(m_pRenderer, "SDL - Test Game", 0, 60, { 255,100,0,0 }, 2);
	m_Label[0].Name() = "labGameTitle";
	m_Label[0].AncorPoint() = GUI::CenterX;

	m_Label[1].Init(m_pRenderer, "Company - ChefKochTechnology [CKT]", 5, 2, { 255,100,0,0 }, 1);
	m_Label[1].Name() = "labCompany";
	m_Label[1].AncorPoint() = GUI::Bottom | GUI::Left;

	m_Label[2].Init(m_pRenderer, "Creator - Marcel Schöne", 5, m_Label[1].Height(), { 255,100,0,0 }, 1);
	m_Label[2].Name() = "labCreatorName";
	m_Label[2].AncorPoint() = GUI::Bottom | GUI::Left;

	m_Label[3].Init(m_pRenderer, "Last - 11/13/2015", 5, 2, { 255,100,0,0 }, 1);
	m_Label[3].Name() = "labLastChange";
	m_Label[3].AncorPoint() = GUI::Bottom | GUI::Right;

	m_Label[4].Init(m_pRenderer, "Date - 10/19/2015", 5, m_Label[3].Height(), { 255,100,0,0 }, 1);
	m_Label[4].Name() = "labCreatorDate";
	m_Label[4].AncorPoint() = GUI::Bottom | GUI::Right;

	m_Label[5].Init(m_pRenderer, "Version - " + GAME_VERSION.ToString(), 5, m_Label[4].Height() + m_Label[4].Y(), { 255,100,0,0 }, 1);
	m_Label[5].Name() = "labVersion";
	m_Label[5].AncorPoint() = GUI::Bottom | GUI::Right;

	m_Label[6].Init(m_pRenderer, "You are victorious!", 5, 130, { 10,200,10,255 }, 2);
	m_Label[6].Name() = "labVictory";
	m_Label[6].Visibility() = false;

	m_btnExit.Init(m_pRenderer, m_ResPath + "IMG\\GUI\\GUI_Btn_NSF_S2x2.png", 0, 150, 2, 2);
	m_btnExit.SetClickFocusEvents(onClickedCallback, onGotFocusCallback, onLostFocusCallback, this);
	m_btnExit.Name() = "btnExit";
	m_btnExit.Content().Init(m_pRenderer, "EXIT", 0, 0, 1);
	m_btnExit.AncorPoint() = GUI::CenterX | GUI::Bottom;

	m_btnRestart.Init(m_pRenderer, m_ResPath + "IMG\\GUI\\GUI_Btn_NSF_S2x2.png", 0, m_btnExit.Height() + m_btnExit.Y(), 2, 2);
	m_btnRestart.SetClickFocusEvents(onClickedCallback, onGotFocusCallback, onLostFocusCallback, this);
	m_btnRestart.Name() = "btnRestart";
	m_btnRestart.Content().Init(m_pRenderer, "RESTART", 0, 0, 1);
	m_btnRestart.AncorPoint() = GUI::CenterX | GUI::Bottom;

	m_btnPlay.Init(m_pRenderer, m_ResPath + "IMG\\GUI\\GUI_Btn_NSF_S2x2.png", 0, m_btnRestart.Height() + m_btnRestart.Y(), 2, 2);
	m_btnPlay.SetClickFocusEvents(onClickedCallback, onGotFocusCallback, onLostFocusCallback, this);
	m_btnPlay.Name() = "btnPlay";
	m_btnPlay.Content().Init(m_pRenderer, "PLAY", 0, 0, 1);
	m_btnPlay.AncorPoint() = GUI::CenterX | GUI::Bottom;

	m_BtnGroup.AddBtn(&m_btnExit);
	m_BtnGroup.AddBtn(&m_btnRestart);
	m_BtnGroup.AddBtn(&m_btnPlay);
	m_BtnGroup.Scale() = 1.5f;

	//m_But2.Init(m_pRenderer, m_ResPath + "IMG\\GUI\\GUI_TBtn_S2x2.png", 0, 50, 2, 2);
	//m_But2.SetClickFocusEvents(onClickedCallback, onGotFocusCallback, onLostFocusCallback, this);
	//m_But2.Name() = "Toggle_Btn_1";
	//m_But2.AncorPoint() = GUI::Bottom;	
	//m_Bar = new GUI::CProgressbarV();
	//m_Bar->Init(m_pRenderer, 0, 50, 250, 20);
	//m_Bar->Orientation() = GUI::FromCenter;
	//m_Bar->AncorPoint() = GUI::CenterX | GUI::Bottom;

	SDL_Color c = { 20,20,20,240 };
	m_MenuPanel.Init(m_pRenderer, c, 100, 0, SCREEN.W * .75f, (float)SCREEN.H);
	//m_MenuPanel.Init(m_pRenderer, m_ResPath + "IMG\\GUI\\Menu_Backgrd_1.png", 100, 0, (float)(SCREEN.W * .75f), (float)SCREEN.H);
	//m_MenuPanel.BackgroundColor() = { 100,100,100,128 };
	m_MenuPanel.AddControl(m_Label, 7);
	m_MenuPanel.AddControl(&m_btnExit);
	m_MenuPanel.AddControl(&m_btnRestart);
	m_MenuPanel.AddControl(&m_btnPlay);
	m_MenuPanel.AddControl(&m_BtnGroup);
	//m_MenuPanel.AddControl(&m_But2);
	//m_MenuPanel.AddControl(m_Bar);

	m_MenuPanel.CalculatePositions();

	//GUI::CScrollbar* scb = new GUI::CScrollbarVer();
	//scb->Init(m_pRenderer, m_ResPath + "IMG\\GUI\\GUI_SCBV_S4x3.png", 150, 50, 4, 3, 32 * 15, (float)GUI::CScrollbar::STD_SCB_SIZE);
	//scb->Name() = "scbVertikal";
	//scb->SetScrollFactor(4);
	//scb->Max() = 100;
	//scb->SetValueFocusEvents(onValueCallback, onGotFocusCallback, onLostFocusCallback, this);
	//m_Scrollbar.push_back(scb);
	//scb = new GUI::CScrollbarHor();
	//scb->Init(m_pRenderer, m_ResPath + "IMG\\GUI\\GUI_SCBH_S4x3.png", 100, 20, 4, 3, (float)GUI::CScrollbar::STD_SCB_SIZE, 32 * 15);
	//scb->Name() = "scbHorizontal";
	//scb->SetScrollFactor(4);
	//scb->SetValueFocusEvents(onValueCallback, onGotFocusCallback, onLostFocusCallback, this);
	//m_Scrollbar.push_back(scb);

	m_Clock.Init(m_pRenderer, m_ResPath + "IMG\\GUI\\clock_back.png", m_ResPath + "IMG\\GUI\\clock_pointer.png", 0, 150, 1.0f);
	m_Clock.X() = (SCREEN.W - m_Clock.Width()) / 2; 

	// test of the scrollable container
	m_Radio1.Init(m_pRenderer, m_ResPath + "IMG\\GUI\\GUI_RBtn_S2x2.png", 1, 50, 2, 2);
	m_Radio1.SetClickFocusEvents(onClickedCallback, onGotFocusCallback, onLostFocusCallback, this);
	m_Radio1.Name() = "rbtRadioBtn1";
	m_Radio2.Init(m_pRenderer, m_ResPath + "IMG\\GUI\\GUI_RBtn_S2x2.png", 60, 120, 2, 2);
	m_Radio2.SetClickFocusEvents(onClickedCallback, onGotFocusCallback, onLostFocusCallback, this);
	m_Radio2.Name() = "rbtRadioBtn2";
	m_Radio3.Init(m_pRenderer, m_ResPath + "IMG\\GUI\\GUI_RBtn_S2x2.png", 180, 180, 2, 2);
	m_Radio3.SetClickFocusEvents(onClickedCallback, onGotFocusCallback, onLostFocusCallback, this);
	m_Radio3.Name() = "rbtRadioBtn3";
	m_Radio4.Init(m_pRenderer, m_ResPath + "IMG\\GUI\\GUI_RBtn_S2x2.png", 380, 238, 2, 2);
	m_Radio4.SetClickFocusEvents(onClickedCallback, onGotFocusCallback, onLostFocusCallback, this);
	m_Radio4.Name() = "rbtRadioBtn4";

	m_Radio1.IsPressed() = true;
	m_Radio4.IsPressed() = true;

	m_Group1.AddRadioBtn(&m_Radio1);
	m_Group1.AddRadioBtn(&m_Radio2);
	m_Group2.AddRadioBtn(&m_Radio3);
	m_Group2.AddRadioBtn(&m_Radio4);

	c.b = 255;
	c.a = 200;
	m_Cont.Init(m_pRenderer, c, 100, 150, 200, 300);
	m_Cont.InitScrollbars(m_pRenderer, m_ResPath + "IMG\\GUI\\GUI_SCBH_S4x3.png", m_ResPath + "IMG\\GUI\\GUI_SCBV_S4x3.png", 32, 32, 4, 3);
	m_Cont.Visibility() = false;
	m_Cont.AddControl(&m_Radio1);
	m_Cont.AddControl(&m_Radio2);
	m_Cont.AddControl(&m_Radio3);
	m_Cont.AddControl(&m_Radio4);
	m_Cont.AddControl(&m_Group1);
	m_Cont.AddControl(&m_Group2);
	m_Cont.CalculatePositions();


	return 0;
}


int CGame::AppInit()
{
	m_ResPath = CKT::getResourcePath();

	int code = SDLInit();
	if (code != 0)
	{
		return AppExit(code);
	}

	GameInit();

	CKT::logSDLError(std::cerr, "INFO->Init successfull.");
	return 0;
}
	
int CGame::AppExit(int code)
{
	cleanup(m_pRenderer, m_pWin);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	if (code > 0)
		_getch();

	return code;
}

int CGame::AppLoop()
{
	//A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
	Uint32 FrameTime = 0;
	Uint32 sumFrameTime = 0;
	int FrameCounter = 0;
	Uint32 GameStartTime = SDL_GetTicks();
	while (m_Run)
	{
		Uint32 TimeStart = SDL_GetTicks();

		// Handle input
		//e is an SDL_Event variable we've declared before entering the main loop
		Move();

		// Render Scene
		//First clear the renderer
		SDL_SetRenderDrawColor(m_pRenderer, 15, 10, 20, 0);
		SDL_RenderClear(m_pRenderer);

		Render(m_pRenderer);

		//Update the screen
		SDL_RenderPresent(m_pRenderer);
		//Take a quick break after all that hard work
		//SDL_Delay(50);

		// calculate FPS continusliy (fast changes by the displayed FPS) or (S1) ...
		//m_FPS = FrameCounter / ((SDL_GetTicks() - GameStartTime) / 1000.0f);

		FrameTime = SDL_GetTicks() - TimeStart;

		// TODO: check why it is running only at 30 fps self if the FRAME_TIME_FIX is higher
		//		 about 50% of the delays are correct the others are to long
		// see SDL-Wiki : 
		// SDL_Delay() : This function waits a specified number of milliseconds before returning.
		//				 It waits at least the specified time, but possibly longer due to OS scheduling.
		if (FrameTime < m_FrameTimeFixed && INI_DATA.MAX_FPS_Lock)
		{
			SDL_Delay(m_FrameTimeFixed - FrameTime);
			FrameTime = SDL_GetTicks() - TimeStart;
		}

		m_TimeFrame = FrameTime / 1000.0f;

		sumFrameTime += FrameTime;
		FrameCounter++;

		// (S1) ... calculate FPS every second (displayed FPS are not changing so quick) 
		if (sumFrameTime > 1000)
		{
			m_FPS = 1000.0f / ((float)sumFrameTime / (float)FrameCounter);
			FrameCounter = 0;
			sumFrameTime = 0;
		}

	}

	for each (CKT::GFX::GfxObject* item in m_Enemys)
	{
		delete item;
	}

	return 0;
}

