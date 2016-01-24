#pragma once

#include "Common.h"
#include <string>

namespace CKT
{
	typedef SDL_Renderer* PRENDERER;
	typedef SDL_Texture* PTEXTURE;
	/*
	* Get the resource path for resources located in res/subDir
	* It's assumed the project directory is structured like:
	* bin/
	*  the executable
	* res/
	*  Lesson1/
	*  Lesson2/
	*
	* Paths returned will be Lessons/res/subDir
	*/
	DllExport std::string getResourcePath(const std::string &subDir = "");

	/**
	* Log an SDL error with some error message to the output stream of our choice
	* @param os The output stream to write the message to
	* @param msg The error message to write, format will be msg error: SDL_GetError()
	*/
	DllExport  void logSDLError(std::ostream &os, const std::string &msg = "");

	namespace GUI
	{
		enum eOriantation
		{
			VER,
			HOR,
		};

	}

}
