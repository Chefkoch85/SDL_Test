#pragma once

#include <string>
#include <iostream>
#include <SDL.h>

namespace CKT
{

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
	std::string getResourcePath(const std::string &subDir = "");

	/**
	* Log an SDL error with some error message to the output stream of our choice
	* @param os The output stream to write the message to
	* @param msg The error message to write, format will be msg error: SDL_GetError()
	*/
	void logSDLError(std::ostream &os, const std::string &msg = "");

}