#include "FontManager.h"

#include "Graphics.h"

using namespace CKT::GFX;

CFontManager* CFontManager::m_Instance = nullptr;

CFontManager::CFontManager()
{
}


CFontManager* CKT::GFX::CFontManager::Instance()
{
	if (m_Instance)
		return m_Instance;

	m_Instance = new CFontManager();
	return m_Instance;
}

CFontManager::~CFontManager()
{
	for each (std::pair<FONT_ID, TTF_Font*> item in m_FontMap)
	{
		TTF_CloseFont(item.second);
	}
	m_FontMap.clear();

	m_FileIDMap.clear();
}

TTF_Font* CFontManager::getFont(FONT_ID id)
{
	std::map<FONT_ID, TTF_Font*>::iterator it = m_FontMap.find(id);
	if (it != m_FontMap.end())
	{
		return it->second;
	}

	return nullptr;
}

FONT_ID CKT::GFX::CFontManager::loadFont(std::string file, int fontSize)
{
	std::map<std::string, SFontInfo>::iterator it = m_FileIDMap.find(file);
	if (it != m_FileIDMap.end())
	{
		int fh = it->second.FontSize;

		if(fh == fontSize)
			return it->second.ID;
	}

	//Open the font
	TTF_Font* font = TTF_OpenFont(file.c_str(), fontSize);
	if (font == nullptr)
	{
		logSDLError(std::cout, "ERROR->TTF_OpenFont()");
		return 0;
	}

	SFontInfo fi;
	fi.ID = m_FileIDMap.size() + 1;
	fi.FontSize = fontSize;
	m_FileIDMap.insert(std::pair<std::string, SFontInfo>(file, fi));
	m_FontMap.insert(std::pair<FONT_ID, TTF_Font*>(m_FontMap.size() + 1, font));
	
	return m_FontMap.size();
}

void CKT::GFX::CFontManager::releaseFont(FONT_ID id)
{
	std::map<FONT_ID, TTF_Font*>::iterator it = m_FontMap.find(id);
	FONT_ID IDToDelete = it->first;

	if (it != m_FontMap.end())
	{
		TTF_CloseFont(it->second);
		m_FontMap.erase(it->first);
	}

	std::map<std::string, SFontInfo>::iterator itFile = m_FileIDMap.begin();
	for (; itFile != m_FileIDMap.end(); it++)
	{
		if (itFile->second.ID == IDToDelete)
			m_FileIDMap.erase(itFile);
	}
}

void CKT::GFX::CFontManager::TextMetrics(FONT_ID id, const std::string & msg, int* w, int* h)
{
	TTF_SizeText(CKT::GFX::CFontManager::Instance()->getFont(id), msg.c_str(), w, h);
}

int CKT::GFX::CFontManager::renderText(const std::string & message, SDL_Color color, SDL_Renderer * ren, SDL_Rect rDst, FONT_ID id)
{
	PTEXTURE pTex = TextToTexture(message, color, ren, id);
	return renderText(pTex, ren, rDst, id, nullptr);
}

int CKT::GFX::CFontManager::renderText(const std::string & message, SDL_Color color, SDL_Renderer * ren, int x, int y, FONT_ID id, SDL_Rect * rClip)
{
	SDL_Rect rDst = { 0 };
	PTEXTURE pTex = TextToTexture(message, color, ren, id);
	rDst.x = x;
	rDst.y = y;
	SDL_QueryTexture(pTex, nullptr, nullptr, &rDst.w, &rDst.h);

	if (rClip)
	{
		rDst.w = rClip->w;
		rDst.h = rClip->h;
	}

	return renderText(pTex, ren, rDst, id, rClip);
}

int CKT::GFX::CFontManager::renderText(PTEXTURE pTex, SDL_Renderer* ren, SDL_Rect rDst, FONT_ID id, SDL_Rect* rClip)
{
	SDL_SetTextureBlendMode(pTex, m_BlendMode);
	SDL_SetTextureAlphaMod(pTex, m_AlphaMod);

	renderTexture(pTex, ren, rDst, rClip);

	SDL_DestroyTexture(pTex);
	return 0;
}

CKT::PTEXTURE CKT::GFX::CFontManager::TextToTexture(const std::string & message, SDL_Color color, SDL_Renderer * ren, FONT_ID id)
{
	TTF_Font* pFont = getFont(id);
	if (!pFont)
		return nullptr;
	//We need to first render to a surface as that's what TTF_RenderText
	//returns, then load that surface into a texture
	SDL_Surface* surf = TTF_RenderText_Blended(pFont, message.c_str(), color);
	if (surf == nullptr)
	{
		logSDLError(std::cout, "TTF_RenderText");
		return nullptr;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surf);
	if (texture == nullptr)
	{
		logSDLError(std::cout, "CreateTexture");
		return nullptr;
	}
	//Clean up the surface and font
	SDL_FreeSurface(surf);

	return texture;
}
