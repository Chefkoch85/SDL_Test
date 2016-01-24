
#include "Graphics.h"

/**
* Loads a BMP image into a texture on the rendering device
* @param file The BMP image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* CKT::GFX::loadTextureBmp(const std::string &file, SDL_Renderer *ren)
{
	//Initialize to nullptr to avoid dangling pointer issues
	SDL_Texture *texture = nullptr;
	//Load the image
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	//If the loading went ok, convert to texture and return the texture
	if (loadedImage != nullptr)
	{
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		//Make sure converting went ok too
		if (texture == nullptr)
		{
			logSDLError(std::cout, "CreateTextureFromSurface()");
		}
	}
	else
	{
		logSDLError(std::cout, "LoadBMP()");
	}
	return texture;
}

SDL_Texture* CKT::GFX::loadTexture(const std::string &file, SDL_Renderer *ren)
{
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr)
	{
		logSDLError(std::cerr, "LoadTexture");
	}
	return texture;
}


/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
*/
void CKT::GFX::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect* clip) 
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;

	if (clip != nullptr)
	{
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else 
	{
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	}

	renderTexture(tex, ren, dst, clip);
}

/**
* Draw an SDL_Texture to an SDL_Renderer at some destination rect
* taking a clip of the texture if desired
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param dst The destination rectangle to render the texture to
* @param clip The sub-section of the texture to draw (clipping rect)
*		default of nullptr draws the entire texture
*/
void CKT::GFX::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip)
{
	SDL_RenderCopy(ren, tex, clip, &dst);
}

void CKT::GFX::renderTexture(SDL_Texture * tex, SDL_Renderer * ren, SDL_Rect dst, double angle, SDL_Point * center, SDL_RendererFlip flip, SDL_Rect * clip)
{
	SDL_RenderCopyEx(ren, tex, clip, &dst, angle, center, flip);
}

void CKT::GFX::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}


SDL_Texture* CKT::GFX::renderText(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize, SDL_Renderer *renderer)
{
	//Open the font
	TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == nullptr)
	{
		logSDLError(std::cout, "TTF_OpenFont");
		return nullptr;
	}
	//We need to first render to a surface as that's what TTF_RenderText
	//returns, then load that surface into a texture
	SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
	if (surf == nullptr)
	{
		TTF_CloseFont(font);
		logSDLError(std::cout, "TTF_RenderText");
		return nullptr;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr)
	{
		logSDLError(std::cout, "CreateTexture");
	}
	//Clean up the surface and font
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return texture;
}

void CKT::GFX::DrawCircle(PRENDERER ren, float cX, float cY, float r, SDL_Color col)
{
	float rSquared = powf(r, 2.0f);
	int xPivot = (int)(r * 0.70710678118f + 0.5f);
	SDL_SetRenderDrawColor(ren, col.r, col.g, col.b, col.a);
	for (int x = 0; x <= xPivot; x++)
	{
		int y = (int)(sqrt((rSquared - powf((float)x, 2.0f)) + 0.5f));
		SDL_RenderDrawPoint(ren, (int)cX + x, (int)cY + y);
		SDL_RenderDrawPoint(ren, (int)cX - x, (int)cY + y);
		SDL_RenderDrawPoint(ren, (int)cX + x, (int)cY - y);
		SDL_RenderDrawPoint(ren, (int)cX - x, (int)cY - y);

		SDL_RenderDrawPoint(ren, (int)cX + y, (int)cY + x);
		SDL_RenderDrawPoint(ren, (int)cX - y, (int)cY + x);
		SDL_RenderDrawPoint(ren, (int)cX + y, (int)cY - x);
		SDL_RenderDrawPoint(ren, (int)cX - y, (int)cY - x);
	}
}
