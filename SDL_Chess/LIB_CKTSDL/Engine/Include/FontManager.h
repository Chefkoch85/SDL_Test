#pragma once

#include "Common.h"

#include "Util.h"

#include <SDL_ttf.h>

#include <map>

namespace CKT
{
	namespace GFX
	{
		typedef int FONT_ID;

		class CFontManager
		{
		private:
			struct SFontInfo
			{
				FONT_ID ID;
				int FontSize;
			};

			static CFontManager* m_Instance;
			std::map<std::string, SFontInfo> m_FileIDMap;
			std::map<FONT_ID, TTF_Font*> m_FontMap;
			std::map<FONT_ID, int> m_TexCounter;

			int m_AlphaMod = 255;
			SDL_BlendMode m_BlendMode = SDL_BlendMode::SDL_BLENDMODE_BLEND;

			CFontManager();
		public:

			DllExport static CFontManager* Instance();
			DllExport ~CFontManager();

			DllExport int& AlphaMod() { return m_AlphaMod; }
			DllExport SDL_BlendMode BlendMode() { return m_BlendMode; }

			DllExport TTF_Font* getFont(FONT_ID id);

			DllExport FONT_ID loadFont(std::string file, int fontSize);
			DllExport void releaseFont(FONT_ID id);

			DllExport void CKT::GFX::CFontManager::TextMetrics(FONT_ID id, const std::string & msg, int* w, int* h);

			DllExport int renderText(const std::string &message, SDL_Color color, SDL_Renderer *ren, SDL_Rect rDst, FONT_ID id = 1);
			DllExport int renderText(const std::string &message, SDL_Color color, SDL_Renderer *ren, int x, int y, FONT_ID id = 1, SDL_Rect* rClip = nullptr);
			DllExport int renderText(PTEXTURE pTex, SDL_Renderer *ren, SDL_Rect rDst, FONT_ID id = 1, SDL_Rect* rClip = nullptr);

			DllExport PTEXTURE TextToTexture(const std::string &message, SDL_Color color, SDL_Renderer *ren, FONT_ID id = 0);
		};

	}

}
