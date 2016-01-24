
#include "Game.h"

int main(int argc, char** argv)
{
	CKT::CGame game;
	int code = game.AppInit();
	if (code > 0)
		return game.AppExit(code);

	game.AppLoop();

	return game.AppExit(0);
}
