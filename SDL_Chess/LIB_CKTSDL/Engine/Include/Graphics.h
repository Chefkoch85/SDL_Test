#pragma once

#include "Common.h"
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Util.h"

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
		DllExport SDL_Texture* loadTextureBmp(const std::string &file, SDL_Renderer *ren);

		/**
		* Loads an image into a texture on the rendering device
		* @param file The image file to load
		* @param ren The renderer to load the texture onto
		* @return the loaded texture, or nullptr if something went wrong.
		*/
		DllExport SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);

		/**
		* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
		* the texture's width and height
		* @param tex : The source texture we want to draw
		* @param ren : The renderer we want to draw to
		* @param x : The x coordinate to draw to
		* @param y : The y coordinate to draw to
		*/
		DllExport void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect* clip = nullptr);

		/**
		* Draw an SDL_Texture to an SDL_Renderer at position x, y, w, h
		* @param tex : The source texture we want to draw
		* @param ren : The renderer we want to draw to
		* @param x : The x coordinate to draw to
		* @param y : The y coordinate to draw to
		* @param w : The width of the destination rect
		* @param h : The height of the destination rect
		*/
		DllExport void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);

		/**
		* Draw an SDL_Texture to an SDL_Renderer at some destination rect
		* taking a clip of the texture if desired
		* @param tex The source texture we want to draw
		* @param ren The renderer we want to draw to
		* @param dst The destination rectangle to render the texture to
		* @param clip The sub-section of the texture to draw (clipping rect)
		*		default of nullptr draws the entire texture
		*/
		DllExport void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip = nullptr);
		DllExport void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, SDL_Rect dst, double angle, SDL_Point* center, SDL_RendererFlip flip, SDL_Rect* clip = nullptr);


		/**
		* Render the message we want to display to a texture for drawing
		* @param message The message we want to display
		* @param fontFile The font we want to use to render the text
		* @param color The color we want the text to be
		* @param fontSize The size we want the font to be
		* @param renderer The renderer to load the texture in
		* @return An SDL_Texture containing the rendered message, or nullptr if something went wrong
		*/
		DllExport SDL_Texture* renderText(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize, SDL_Renderer *renderer);


		/**
		*
		*
		*/
		DllExport void DrawCircle(PRENDERER ren, float cX, float cY, float r, SDL_Color col);

		/**
		*
		*/
		DllExport void DrawRect(PRENDERER ren, float x, float y, float w, float h, SDL_Color col);


		/**
		*
		*/
		DllExport void FillRect(PRENDERER ren, float x, float y, float w, float h, SDL_Color col);
	}

}