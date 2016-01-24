#pragma once

#include <string>
#include <iostream>
#include <SDL.h>
#include "..\..\LIB_CKTSDl_intern.h"

namespace CKT
{
	struct SScreen
	{
		int X;
		int Y;
		int W;
		int H;
	};

	DllExport extern bool DEBUG_ON;
	DllExport extern const std::string DEBUG_IMG;
	//DllExport extern SScreen SCREEN;
}