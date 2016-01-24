#pragma once

#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "Common.h"

namespace CKT
{
	namespace GFX
	{
		/**
		* Loads a BMP image into a texture on the rendering device
		* @param file : The BMP image file to load
		* @param ren : The renderer to load the texture onto
		* @return the loaded texture, or nullptr if something went wrong.
		*/
		SDL_Texture* loadTextureBmp(const std::string &file, SDL_Renderer *ren);

		/**
		* Loads an image into a texture on the rendering device
		* @param file The image file to load
		* @param ren The renderer to load the texture onto
		* @return the loaded texture, or nullptr if something went wrong.
		*/
		SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);

		/**
		* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
		* the texture's width and height
		* @param tex : The source texture we want to draw
		* @param ren : The renderer we want to draw to
		* @param x : The x coordinate to draw to
		* @param y : The y coordinate to draw to
		*/
		void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

		/**
		* Draw an SDL_Texture to an SDL_Renderer at position x, y, w, h
		* @param tex : The source texture we want to draw
		* @param ren : The renderer we want to draw to
		* @param x : The x coordinate to draw to
		* @param y : The y coordinate to draw to
		* @param w : The width of the destination rect
		* @param h : The height of the destination rect
		*/
		void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);

	}

}