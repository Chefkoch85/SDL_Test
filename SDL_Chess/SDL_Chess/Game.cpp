
#include <cstdio>
#include <conio.h>
#include <iomanip>

#include "Game.h"

#include <Cleanup.h>

#include <SDL_syswm.h>

#include <FontManager.h>

using namespace CKT;

int CGame::Move()
{
	SDL_Event e = { 0 };
	std::string subsys = "";
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			m_Run = false;
			break;

		case SDL_KEYDOWN:

			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				if (m_Paused)
				{
					if (!m_Timer.IsStarted())
						m_Timer.Start(1000);
				}

				if (m_Paused && m_Timer.IsFinishOnce())
					m_Run = false;

				break;

			case SDLK_m:
				m_Board.DumpField();
				break;
			}
			
			break;

		case SDL_KEYUP:
			
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				if (m_Paused && m_Board.IsVictory() == GAME::NO_PLAYER)
					m_SwitchMenu = 1;
				else if (!m_Paused)
					m_SwitchMenu = -1;

				m_Timer.Stop();

				break;

			case SDLK_r:
				if (m_Paused && m_SwitchMenu == 0)
				{
					m_Board.Clear();
					InitFigures(m_Board.PlayerUp());
				}

				break;
			}

			break;

		case SDL_MOUSEBUTTONDOWN:

			if (!m_Paused && e.button.button == SDL_BUTTON_LEFT)
			{
				m_Board.LeftMouseDown((float)e.motion.x, (float)e.motion.y);
			}
			else if (!m_Paused && e.button.button == SDL_BUTTON_RIGHT)
			{
				m_Board.RightMouseDown();
			}

			break;
			
		}

	} // while

	
	if (m_Paused || m_SwitchMenu != 0)
	{
		// switch menu off
		if (m_SwitchMenu > 0)
		{
			m_Menu.BackgroundColor().a -= 3;
			GUI::CGUIBase* item = m_Menu.GetControlByName("labLogo");
			item->SetScaleX(item->GetScaleX() - 2.9f * m_TimeFrame);

			if (m_Menu.BackgroundColor().a <= 10)
			{
				m_Paused = false;
				m_SwitchMenu = 0;
			}
		}
		// switch menu on
		else if (m_SwitchMenu < 0)
		{
			m_Menu.BackgroundColor().a += 3;
			GUI::CGUIBase* item = m_Menu.GetControlByName("labLogo");
			item->SetScaleX(item->GetScaleX() + 2.9f * m_TimeFrame);

			m_Paused = true;
			if (m_Menu.BackgroundColor().a >= 200)
			{
				m_SwitchMenu = 0;
			}
		}

		m_Menu.Update(&e);
	}
	
	if (m_Paused)
		return 0;

	m_GameTime += m_TimeFrame;

	if (m_Board.IsVictory() != GAME::NO_PLAYER)
		m_SwitchMenu = -1;

	m_Board.Update(m_TimeFrame);

	return 0;
}

int CGame::Render(CKT::PRENDERER pRen)
{
	m_Board.Render();

	SDL_Color color = { 150,255,20,255 };
	std::string str2 = "Time: ";
	std::stringstream ss;
	ss.precision(3);
	ss << std::fixed << str2 << m_GameTime;
	CKT::GFX::CFontManager::Instance()->renderText(ss.str(), color, pRen, 360, 5, 1);

	std::string str = "SDL Test Game - FPS: " + std::to_string(m_FPS);
	SDL_SetWindowTitle(m_pWin, str.c_str());

	if (m_Paused)
	{
		m_Menu.Render();
	}

	return 0;
}


void CKT::CGame::onMenuClickedCallback(void * pThis, CKT::GUI::CMenuItem & sender, GUI::CBtnEventArgs & args)
{
	CGame* self = static_cast<CGame*>(pThis);
	self->onMenuClicked(sender, args);
}

void CKT::CGame::onMenuClicked(GUI::CMenuItem & sender, GUI::CBtnEventArgs & args)
{
	std::cout << std::setw(30) << std::left << "callback \"onClick()\"" << " : ";
	std::cout << std::setw(15) << std::left << sender.Name() << " |ID: " << std::setw(3) << args.ID() << " |State: " << args.ClickState() << std::endl;

	if (sender.Name() == "mitQuit" && args.ClickState() == GUI::CBtnEventArgs::Up)
	{
		m_Run = false;
	}
	else if (sender.Name() == "mitResume" && args.ClickState() == GUI::CBtnEventArgs::Up)
	{
		if (m_Paused && m_Board.IsVictory() == GAME::NO_PLAYER)
			m_SwitchMenu = 1;
	}
	else if (sender.Name() == "mitSameGame" && args.ClickState() == GUI::CBtnEventArgs::Up)
	{
		m_Board.Clear();
		InitFigures(m_Board.PlayerUp());
	}
	else if (sender.Name() == "mitPlayerBlack" && args.ClickState() == GUI::CBtnEventArgs::Up)
	{
		m_Board.PlayerUp() = GAME::BLACK;
		m_Board.Clear();
		InitFigures(m_Board.PlayerUp());
	}
	else if (sender.Name() == "mitPlayerWhite" && args.ClickState() == GUI::CBtnEventArgs::Up)
	{
		m_Board.PlayerUp() = GAME::WHITE;
		m_Board.Clear();
		InitFigures(m_Board.PlayerUp());
	}
}

int CGame::SDLInit()
{
	// get INI-File data
	
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

	SCREEN.X = 700;
	SCREEN.Y = 32;
	SCREEN.W = 800;
	SCREEN.H = 600;

	// create a SDL window
	m_pWin = SDL_CreateWindow("SDL-TEST", SCREEN.X, SCREEN.Y, SCREEN.W, SCREEN.H, SDL_WINDOWEVENT_SHOWN);

	int flags = 0;
	//flags |= SDL_WINDOW_FULLSCREEN;

	SDL_SetWindowFullscreen(m_pWin, flags);

	if (m_pWin == nullptr)
	{
		CKT::logSDLError(std::cerr, "ERROR->CreateWindow()");
		return 4;
	}

	// create Renderer
	flags = SDL_RENDERER_ACCELERATED;
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
	m_Paused = true;

	// font creation
	CKT::GFX::CFontManager::Instance()->loadFont(m_ResPath + "FONT\\Chromia.otf", 20);

	// board
	m_Board.Init(m_pRenderer, m_ResPath + "IMG\\board.png", 0, 0, 8, 8, GAME::WHITE);
	m_Board.SetPos((SCREEN.W - m_Board.Width()) / 2, (SCREEN.H - m_Board.Height()) / 2);

	InitFigures(m_Board.PlayerUp());

	// Gui creation
	GuiInit();

	return 0;
}

int CKT::CGame::InitFigures(GAME::eWhere up)
{
	int sideWhite = 7, dirWhite = -1;
	int sideBlack = 0, dirBlack = 1;

	if (up == GAME::eWhere::WHITE)
	{
		sideWhite = 0;
		dirWhite = 1;
		sideBlack = 7;
		dirBlack = -1;
	}

	m_Board.InitFigure(m_ResPath + "IMG\\BLACK\\Pawn.png", 0, sideBlack + dirBlack, GAME::PAWN, GAME::BLACK);
	m_Board.InitFigure(m_ResPath + "IMG\\BLACK\\Pawn.png", 1, sideBlack + dirBlack, GAME::PAWN, GAME::BLACK);
	m_Board.InitFigure(m_ResPath + "IMG\\BLACK\\Pawn.png", 2, sideBlack + dirBlack, GAME::PAWN, GAME::BLACK);
	m_Board.InitFigure(m_ResPath + "IMG\\BLACK\\Pawn.png", 3, sideBlack + dirBlack, GAME::PAWN, GAME::BLACK);
	m_Board.InitFigure(m_ResPath + "IMG\\BLACK\\Pawn.png", 4, sideBlack + dirBlack, GAME::PAWN, GAME::BLACK);
	m_Board.InitFigure(m_ResPath + "IMG\\BLACK\\Pawn.png", 5, sideBlack + dirBlack, GAME::PAWN, GAME::BLACK);
	m_Board.InitFigure(m_ResPath + "IMG\\BLACK\\Pawn.png", 6, sideBlack + dirBlack, GAME::PAWN, GAME::BLACK);
	m_Board.InitFigure(m_ResPath + "IMG\\BLACK\\Pawn.png", 7, sideBlack + dirBlack, GAME::PAWN, GAME::BLACK);
	m_Board.InitFigure(m_ResPath + "IMG\\BLACK\\Tower.png", 0, sideBlack, GAME::TOWER, GAME::BLACK);
	m_Board.InitFigure(m_ResPath + "IMG\\BLACK\\Tower.png", 7, sideBlack, GAME::TOWER, GAME::BLACK);
	m_Board.InitFigure(m_ResPath + "IMG\\BLACK\\Horse.png", 1, sideBlack, GAME::HORSE, GAME::BLACK);
	m_Board.InitFigure(m_ResPath + "IMG\\BLACK\\Horse.png", 6, sideBlack, GAME::HORSE, GAME::BLACK);
	m_Board.InitFigure(m_ResPath + "IMG\\BLACK\\Bishop.png", 2, sideBlack, GAME::BISHOP, GAME::BLACK);
	m_Board.InitFigure(m_ResPath + "IMG\\BLACK\\Bishop.png", 5, sideBlack, GAME::BISHOP, GAME::BLACK);
	m_Board.InitFigure(m_ResPath + "IMG\\BLACK\\Queen.png", 3, sideBlack, GAME::QUEEN, GAME::BLACK);
	m_Board.InitFigure(m_ResPath + "IMG\\BLACK\\King.png", 4, sideBlack, GAME::KING, GAME::BLACK);

	m_Board.InitFigure(m_ResPath + "IMG\\WHITE\\Pawn.png", 0, sideWhite + dirWhite, GAME::PAWN, GAME::WHITE);
	m_Board.InitFigure(m_ResPath + "IMG\\WHITE\\Pawn.png", 1, sideWhite + dirWhite, GAME::PAWN, GAME::WHITE);
	m_Board.InitFigure(m_ResPath + "IMG\\WHITE\\Pawn.png", 2, sideWhite + dirWhite, GAME::PAWN, GAME::WHITE);
	m_Board.InitFigure(m_ResPath + "IMG\\WHITE\\Pawn.png", 3, sideWhite + dirWhite, GAME::PAWN, GAME::WHITE);
	m_Board.InitFigure(m_ResPath + "IMG\\WHITE\\Pawn.png", 4, sideWhite + dirWhite, GAME::PAWN, GAME::WHITE);
	m_Board.InitFigure(m_ResPath + "IMG\\WHITE\\Pawn.png", 5, sideWhite + dirWhite, GAME::PAWN, GAME::WHITE);
	m_Board.InitFigure(m_ResPath + "IMG\\WHITE\\Pawn.png", 6, sideWhite + dirWhite, GAME::PAWN, GAME::WHITE);
	m_Board.InitFigure(m_ResPath + "IMG\\WHITE\\Pawn.png", 7, sideWhite + dirWhite, GAME::PAWN, GAME::WHITE);
	m_Board.InitFigure(m_ResPath + "IMG\\WHITE\\Tower.png", 0, sideWhite, GAME::TOWER, GAME::WHITE);
	m_Board.InitFigure(m_ResPath + "IMG\\WHITE\\Tower.png", 7, sideWhite, GAME::TOWER, GAME::WHITE);
	m_Board.InitFigure(m_ResPath + "IMG\\WHITE\\Horse.png", 1, sideWhite, GAME::HORSE, GAME::WHITE);
	m_Board.InitFigure(m_ResPath + "IMG\\WHITE\\Horse.png", 6, sideWhite, GAME::HORSE, GAME::WHITE);
	m_Board.InitFigure(m_ResPath + "IMG\\WHITE\\Bishop.png", 2, sideWhite, GAME::BISHOP, GAME::WHITE);
	m_Board.InitFigure(m_ResPath + "IMG\\WHITE\\Bishop.png", 5, sideWhite, GAME::BISHOP, GAME::WHITE);
	m_Board.InitFigure(m_ResPath + "IMG\\WHITE\\Queen.png", 3, sideWhite, GAME::QUEEN, GAME::WHITE);
	m_Board.InitFigure(m_ResPath + "IMG\\WHITE\\King.png", 4, sideWhite, GAME::KING, GAME::WHITE);
	return 0;
}

int CKT::CGame::GuiInit()
{
	SDL_Color col = { 255,255,255,200 };
	m_Menu.Init(m_pRenderer, col, 0, 0, (float)SCREEN.W, (float)SCREEN.H);

	GUI::CLabel* lab = new GUI::CLabel();
	lab->Init(m_pRenderer, "Schach - Test", 0, 0, { 100,50,100,255 }, 1);
	lab->Name() = "labLogo";
	lab->SetScale(3.0f);
	lab->AncorPoint() = GUI::Center;

	m_Menu.AddControl(lab);

	SDL_Color c = { 120,120,120,255 };
	m_MenuBar = new GUI::CMenubar();
	m_MenuBar->Init(m_pRenderer, c, 0, 0, m_Menu.Width(), 30);
	m_MenuBar->Name() = "mebDropdownMenu";

	// Menu Game
	GUI::CMenuItem* item = new GUI::CMenuItem();
	item->Init(m_pRenderer, "Game", 0, 0, CColor(0xFF0000FF).ToSDLColor(), c, 1);
	item->Name() = "mitGame";
	item->TopItem() = true;

	GUI::CMenuItem* item2 = new GUI::CMenuItem();
	item2->Init(m_pRenderer, "New", 0, 0, CColor(0x00FF00FF).ToSDLColor(), c, 1);
	item2->Name() = "mitNew";

	GUI::CMenuItem* item3 = new GUI::CMenuItem();
	item3->Init(m_pRenderer, "Player Black Up", 0, 0, CColor(0x00FF00FF).ToSDLColor(), c, 1);
	item3->Name() = "mitPlayerBlack";
	item3->SetClickEvent(onMenuClickedCallback, this);

	GUI::CMenuItem* item4 = new GUI::CMenuItem();
	item4->Init(m_pRenderer, "Same Game", 0, 0, CColor(0x00FF00FF).ToSDLColor(), c, 1);
	item4->Name() = "mitSameGame";
	item4->SetClickEvent(onMenuClickedCallback, this);

	GUI::CMenuItem* item5 = new GUI::CMenuItem();
	item5->Init(m_pRenderer, "Player White Up", 0, 0, CColor(0x00FF00FF).ToSDLColor(), c, 1);
	item5->Name() = "mitPlayerWhite";
	item5->SetClickEvent(onMenuClickedCallback, this);

	GUI::CMenuItem* item6 = new GUI::CMenuItem();
	item6->Init(m_pRenderer, "Quit", 0, 0, CColor(0x00FF00FF).ToSDLColor(), c, 1);
	item6->Name() = "mitQuit";
	item6->SetClickEvent(onMenuClickedCallback, this);

	GUI::CMenuItem* item7 = new GUI::CMenuItem();
	item7->Init(m_pRenderer, "Resume", 0, 0, CColor(0x00FF00FF).ToSDLColor(), c, 1);
	item7->Name() = "mitResume";
	item7->SetClickEvent(onMenuClickedCallback, this);

	item2->Add(item4, true);
	item2->Add(new GUI::CSeperator(m_pRenderer, 4, CColor(0xFF0000FF), CColor(c)));
	item2->Add(item3, true);
	item2->Add(item5, true);

	item->Add(item7);
	item->Add(new GUI::CSeperator(m_pRenderer, 4, CColor(0xFF0000FF), CColor(c)));
	item->Add(item2);
	item->Add(new GUI::CSeperator(m_pRenderer, 4, CColor(0xFF0000FF), CColor(c)));
	item->Add(item6);
	
	m_MenuBar->Add(item);
	
	// Menu Help
	float newX = item->X() + item->Width();
	item = new GUI::CMenuItem();
	item->Init(m_pRenderer, "Help", 0, 0, CColor(0xFF0000FF).ToSDLColor(), c, 1);
	item->Name() = "mitHelp";
	item->TopItem() = true;

	item2 = new GUI::CMenuItem();
	item2->Init(m_pRenderer, "Info", 0, 0, CColor(0x00FF00FF).ToSDLColor(), c, 1);
	item2->Name() = "mitInfo";
	item2->SetClickEvent(onMenuClickedCallback, this);

	item3 = new GUI::CMenuItem();
	item3->Init(m_pRenderer, "Manual", 0, 0, CColor(0x00FF00FF).ToSDLColor(), c, 1);
	item3->Name() = "mitManual";
	item3->SetClickEvent(onMenuClickedCallback, this);

	item->Add(item3);
	item->Add(item2);

	m_MenuBar->Add(item);

	m_MenuBar->Height() = item->Height();

	m_Menu.AddControl(m_MenuBar);
	m_Menu.CalculatePositions();

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

	//CKT::logSDLError(std::cerr, "INFO->Init successfull.");
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
		SDL_SetRenderDrawColor(m_pRenderer, m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a);
		SDL_RenderClear(m_pRenderer);

		Render(m_pRenderer);

		//Update the screen
		SDL_RenderPresent(m_pRenderer);

		// calculate FPS continusliy (fast changes by the displayed FPS) or (S1) ...
		//m_FPS = FrameCounter / ((SDL_GetTicks() - GameStartTime) / 1000.0f);

		FrameTime = SDL_GetTicks() - TimeStart;

		// TODO: check why it is running only at 30 fps self if the FRAME_TIME_FIX is higher
		//		 about 50% of the delays are correct the others are to long
		// see SDL-Wiki : 
		// SDL_Delay() : This function waits a specified number of milliseconds before returning.
		//				 It waits at least the specified time, but possibly longer due to OS scheduling.
		if (FrameTime < m_FrameTimeFixed && false)
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
	
	return 0;
}

