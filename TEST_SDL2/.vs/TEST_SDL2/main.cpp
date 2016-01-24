
#include <SDL.h>
#include <cstdio>
#include <conio.h>

#include "Cleanup.h"
#include "Common.h"
#include "Graphics.h"

typedef SDL_Window* PWINDOW;
typedef SDL_Surface* PSURFACE;
typedef SDL_Renderer* PRENDERER;
typedef SDL_Texture* PTEXTURE;

struct SPlayer
{
	float PosX;
	float PosY;
	float VelX;
	float VelY;
	int ModellWidth;
	int ModellHeight;
	PTEXTURE Modell;
};

struct  SBackground
{
	int TilesX;
	int TilesY;
	int TextureWidth;
	int TextureHeight;
	PTEXTURE Texture;
};


const static int SCR_W = 800;
const static int SCR_H = 600;



PWINDOW g_pWin = nullptr;
PRENDERER g_pRenderer = nullptr;
PTEXTURE g_pForeground = nullptr;
PTEXTURE g_pBackground = nullptr;


SBackground g_Back = { 0 };
SPlayer g_Player = { 0 };



int AppInit();
int AppExit(int code = 0);
int AppLoop();

int main(int argc, char** argv)
{
	int code = AppInit();
	if (code != 0)
	{
		return AppExit(code);
	}

	std::string resPath = CKT::getResourcePath();

	// Player modell creation
	// texture
	g_Player.Modell = CKT::GFX::loadTexture(resPath + "X-Wing_S.png", g_pRenderer);

	// size
	SDL_QueryTexture(g_Player.Modell, nullptr, nullptr, &g_Player.ModellWidth, &g_Player.ModellHeight);

	// resize the player modell
	g_Player.ModellWidth = g_Player.ModellWidth / 1;
	g_Player.ModellHeight = g_Player.ModellHeight / 1;
	
	// set start point (center of screen)
	g_Player.PosX = (SCR_W - g_Player.ModellWidth) / 2;
	g_Player.PosY = (SCR_H - g_Player.ModellHeight) / 2;

	// Background creation
	g_Back.Texture = CKT::GFX::loadTexture(resPath + "Back.png", g_pRenderer);

	SDL_QueryTexture(g_Back.Texture, nullptr, nullptr, &g_Back.TextureWidth, &g_Back.TextureHeight);
	g_Back.TilesX = SCR_W / g_Back.TextureWidth;
	g_Back.TilesY = SCR_H / g_Back.TextureHeight;


	AppLoop();

	cleanup(g_pForeground, g_pBackground, g_pRenderer, g_pWin);
	CKT::logSDLError(std::cerr, "INFO->App closed normal.");
	return AppExit(0);
}

int Move(bool* run)
{
	static bool movement = false;

	SDL_Event e = { 0 };
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			*run = false;
			break;

		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				*run = false;
				break;

			case SDLK_a:
				g_Player.VelX -= 0.3;
				movement = true;
				break;

			case SDLK_d:
				g_Player.VelX += 0.3;
				movement = true;
				break;

			}
			
			break;

		case SDL_KEYUP:
			movement = false;
			break;
		}

	}

	if (!movement && g_Player.VelX > 0)
	{
		g_Player.VelX -= 0.05;
		if (g_Player.VelX < 0)
			g_Player.VelX = 0;
	}

	if (!movement && g_Player.VelX < 0)
	{
		g_Player.VelX += 0.05;
		if (g_Player.VelX > 0)
			g_Player.VelX = 0;
	}

	if (g_Player.VelX > 5.0)
		g_Player.VelX = 5.0;

	if (g_Player.VelX < -5.0)
		g_Player.VelX = -5.0;

	std::cerr << g_Player.PosX << " : " << g_Player.VelX << std::endl;

	g_Player.PosX += g_Player.VelX;

	return 0;
}

int Render(PRENDERER pRen)
{
	//Draw the texture
	for (int i = 0; i < g_Back.TilesX * g_Back.TilesY; i++)
	{
		int x = i % g_Back.TilesX;
		int y = i / g_Back.TilesX;
		CKT::GFX::renderTexture(g_Back.Texture, g_pRenderer, x * g_Back.TextureWidth, y * g_Back.TextureHeight);
	}
		
	CKT::GFX::renderTexture(g_Player.Modell, g_pRenderer, g_Player.PosX, g_Player.PosY, g_Player.ModellWidth, g_Player.ModellHeight);

	return 0;
}

int AppInit()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		CKT::logSDLError(std::cerr, "ERROR->SDL_Init()");
		return 1;
	}

	if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		CKT::logSDLError(std::cerr, "ERROR->SDL_Init()");
		return 2;
	}

	g_pWin = SDL_CreateWindow("SDL-TEST", 50, 50, SCR_W, SCR_H, SDL_WINDOWEVENT_SHOWN);
	SDL_SetWindowFullscreen(g_pWin, 0);
	if (g_pWin == nullptr)
	{
		CKT::logSDLError(std::cerr, "ERROR->CreateWindow()");
		return 3;
	}

	g_pRenderer = SDL_CreateRenderer(g_pWin, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (g_pRenderer == nullptr)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		cleanup(g_pWin);
		return 4;
	}

	return 0;
}

int AppExit(int code)
{
	SDL_Quit();

	if (code > 0)
		_getch();

	return code;
}

int AppLoop()
{
	//A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
	bool bRun = true;
	while(bRun)
	{
		// Handle input
		//e is an SDL_Event variable we've declared before entering the main loop
		Move(&bRun);
		
		// Render Scene
		//First clear the renderer
		SDL_RenderClear(g_pRenderer);

		Render(g_pRenderer);

		//Update the screen
		SDL_RenderPresent(g_pRenderer);
		//Take a quick break after all that hard work
		//SDL_Delay(15);
	}

	return 0;
}